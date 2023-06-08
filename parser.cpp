#include "parser.h"
#include "lalr.h"
#include <cctype>
#include <cstring>
#include <algorithm>

constexpr const char char_type[96] = {Default, Default, Default, Default, Default, Default, AND, Default, LPARE, RPARE, TIMES, PLUS, Default, MINUS, Default, DIV, INT, INT, INT, INT, INT, INT, INT, INT, INT, INT, Default, SEMI, LT, ASSIGN, Default, Default, Default, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, LBRAC, Default, RBRAC, XOR, ID, Default, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, Default, OR, Default, Default, Default};
constexpr const std::pair<const char*, int> reserved_word[8] = {{"free", FREE}, {"putc", PUTC}, {"while", WHILE}, {"getc", GETC}, {"alloc", ALLOC}, {"", Default}, {"elif", ELIF}, {"if", IF}};
constexpr const char *token_name[25] = {"<End of File>", "<Integer>", "<Identifier>", "if", "elif", "while", "getc", "putc", "alloc", "free", "'='", "'<'", "'=='", "'+'", "'-'", "'*'", "'/'", "'&'", "'|'", "'^'", "'('", "')'", "'['", "']'", "';'"};
constexpr const char *binary_op[9] = {"mul", "sdiv", "add", "sub", "icmp slt", "icmp eq", "and", "xor", "or"};

Token Parser::scan()
{
	int type, val = -1;
	for(int t = 1; ;)
	{
		nowc = nxtc;
		if(nxtc != EOF)nxtc = getchar();
		now_line += (nowc == '\n');
		if(nowc == EOF) { type = ENDF; break; }
		t ^= (nowc == (t ? '#' : '\n'));
		if(t && !isspace(nowc))
		{
			type = unsigned(nowc - 32) < 96 ? char_type[nowc - 32] : Default;
			break;
		}
	}
	if(type == INT || type == ID)
	{
		int hash = ((nowc * 39) >> 4) & 7;
		std::string str{(char)nowc};
		while(isalnum(nxtc) || nxtc == '_')
		{
			nowc = nxtc, nxtc = getchar();
			str += (char)nowc;
		}
		if(str == reserved_word[hash].first)type = reserved_word[hash].second;
		else
		{
			if(!sym_tab.count(str))sym_tab[str] = type == INT ? const_num++ : id_num++;
			val = sym_tab[str];
		}
	}
	else if(type == ASSIGN)
	{
		if(nxtc == '=')
		{
			nowc = nxtc, nxtc = getchar();
			type = EQ;
		}
	}
	else if(type == Default)val = nowc;
	return {type, val};
}

void Parser::reduce(int rule)
{
	static int id_num, regs, labels;
	static const code_generator *f;
	int top = stk.size();
	Node *p = stk.data(), &n6 = p[top - 6], &n5 = p[top - 5], &n4 = p[top - 4], &n3 = p[top - 3], &n2 = p[top - 2], &n1 = p[top - 1];
	int gen = gens.size();
	switch(rule)
	{
	case 0: // program <- stmt_seq EOF
		id_num = this->id_num;
		regs = const_num, labels = 1;
		f = gens.data();
		{
			puts("declare i64 @getchar() nounwind\n"
				 "declare i64 @putchar(i64) nounwind\n"
				 "declare i64 @malloc(i64) nounwind\n"
				 "declare void @free(i64) nounwind\n"
				 "define i32 @main() {\n"
				 "L0:");
			for(auto &it : sym_tab)if(isdigit(it.first.front()))
				printf("%%r%d = add i64 %s, 0\n", it.second, it.first.c_str());
			int block = 0, *reg_list = new int[id_num];
			memset(reg_list, 0, id_num * sizeof(int));
			f[n2.gen](block, reg_list);
			delete[] reg_list;
			puts("ret i32 0\n}");
		}
		return stk.clear(); // accept
	case 1: // stmt_seq <- stmt_seq if_stmt SEMI
		gens.push_back([gen1 = n3.gen, n2](int &block, int *reg_list)->tails_attr
		{
			f[gen1](block, reg_list);
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			tails_attr tail = f[n2.gen](block, br_list);
			tail.second->push_back({block, br_list});
			printf("br label %%L%d\nL%d: ; end of if-statement in line %d\n",
				   tail.first, block = tail.first, n2.line);
			int sz = tail.second->size();
			auto tab = tail.second->data();
			for(int id : n2.chg_list)
			{
				printf("%%r%d = phi i64", reg_list[id] = regs++);
				for(int k = 0; k < sz; k++)printf(" [%%r%d, %%L%d]%c", tab[k].second[id], tab[k].first,
												  k < sz - 1 ? ',' : '\n');
			}
			for(int k = 0; k < sz; k++)delete[] tab[k].second;
			delete tail.second;
			return {0, nullptr};
		});
		break;
	case 2: // stmt_seq <- stmt_seq WHILE exp stmt_seq SEMI
		if(n3.chg_list.size())
		{
			n2.chg_list.insert(n2.chg_list.cend(), n3.chg_list.begin(), n3.chg_list.end());
			n3.chg_list.clear();
			std::sort(n2.chg_list.begin(), n2.chg_list.end());
			n2.chg_list.erase(std::unique(n2.chg_list.begin(), n2.chg_list.end()), n2.chg_list.end());
		}
		gens.push_back([chg_list = n2.chg_list, line2 = n4.line, gen1 = n5.gen, gen3 = n3.gen, gen4 = n2.gen](int &block, int *reg_list)->tails_attr
		{
			f[gen1](block, reg_list);
			const int sz = chg_list.size(), *id = chg_list.data();
			int l1 = labels++, l2 = labels++, l3 = labels++, l4 = labels++;
			int r1 = regs, r2 = regs + sz; regs += sz * 2;
			printf("br label %%L%d\nL%d: ; while-statement in line %d\n", l1, l1, line2);
			for(int i = 0; i < sz; i++)
			{
				printf("%%r%d = phi i64 [%%r%d, %%L%d], [%%r%d, %%L%d]\n",
					   r1 + i, reg_list[id[i]], block, r2 + i, l4);
				reg_list[id[i]] = r1 + i;
			}
			block = l1;
			int tail = f[gen3](block, reg_list).first;
			printf("%%r%d = icmp ne i64 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail, regs, l2, l3, l2); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			f[gen4](l2, br_list);
			printf("br label %%L%d\nL%d:\n", l4, l4);
			for(int i = 0; i < sz; i++)printf("%%r%d = add i64 %%r%d, 0\n", r2 + i, br_list[id[i]]);
			delete[] br_list;
			printf("br label %%L%d\n"
				   "L%d: ; end of while-statement in line %d\n",
				   l1, block = l3, line2);
			return {0, nullptr};
		});
		break;
	case 3: // stmt_seq <- stmt_seq exp SEMI
		gens.push_back([line2 = n2.line, gen1 = n3.gen, gen2 = n2.gen](int &block, int *reg_list)->tails_attr
		{
			f[gen1](block, reg_list);
			printf("; expression statement in line %d\n", line2);
			f[gen2](block, reg_list);
			return {0, nullptr};
		});
		break;
	case 4: // stmt_seq <- $epsilon
		_ASSERT(Goto[n1.state][0] == nt_stmt_seq);
		stk.emplace_back(Goto[n1.state][1], now_line, 0);
		return;
	case 5: // if_stmt <- IF exp stmt_seq
		gens.push_back([line = n3.line, gen2 = n2.gen, gen3 = n1.gen](int &block, int *reg_list)->tails_attr
		{
			printf("; if-statement in line %d\n", line);
			int tail = f[gen2](block, reg_list).first;
			auto tab = new std::vector<std::pair<int, int*>>;
			int l1 = labels++, l2 = labels++, l3 = labels++;
			printf("%%r%d = icmp ne i64 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail,
				   regs, l1, l2, l1); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			f[gen3](l1, br_list);
			tab->push_back({l1, br_list});
			printf("br label %%L%d\nL%d:\n", l3, block = l2);
			return {l3, tab};
		});
		break;
	case 6: // if_stmt <- if_stmt ELIF exp stmt_seq
		gens.push_back([line2 = n3.line, gen1 = n4.gen, gen3 = n2.gen, gen4 = n1.gen](int &block, int *reg_list)->tails_attr
		{
			tails_attr tail1 = f[gen1](block, reg_list);
			printf("; elif-statement in line %d\n", line2);
			int tail3 = f[gen3](block, reg_list).first;
			int l1 = labels++, l2 = labels++;
			printf("%%r%d = icmp ne i64 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail3,
				   regs, l1, l2, l1); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			f[gen4](l1, br_list);
			tail1.second->push_back({l1, br_list});
			printf("br label %%L%d\nL%d:\n", tail1.first, block = l2);
			return tail1;
		});
		break;
	case 7: // exp <- rval
		gen = n1.gen;
		break;
	case 8: // exp <- ID ASSIGN exp
		gens.push_back([id = n3.gen, gen = n1.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			return {reg_list[id] = tail, nullptr};
		});
		n3.chg_list.push_back(n3.gen);
		break;
	case 9: // exp <- factor LBRAC exp RBRAC ASSIGN exp
		gens.push_back([gen1 = n6.gen, gen3 = n4.gen, gen6 = n1.gen](int &block, int *reg_list)->tails_attr
		{
			int tail6 = f[gen6](block, reg_list).first;
			int tail1 = f[gen1](block, reg_list).first;
			int tail3 = f[gen3](block, reg_list).first;
			int r1 = regs++, r2 = regs++, r3 = regs++;
			printf("%%r%d = mul i64 %%r%d, 8\n"
				   "%%r%d = add i64 %%r%d, %%r%d\n"
				   "%%r%d = inttoptr i64 %%r%d to ptr\n"
				   "store i64 %%r%d, ptr %%r%d\n", r1, tail3,
				   r2, tail1, r1,
				   r3, r2,
				   tail6, r3);
			return {tail6, nullptr};
		});
		break;
	case 10: // rval <- factor
		gen = n1.gen;
		break;
	case 11: // rval <- PUTC factor
		gens.push_back([gen = n1.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			printf("%%r%d = call i64 @putchar(i64 %%r%d)\n", regs, tail);
			return {regs++, nullptr};
		});
		break;
	case 12: // rval <- ALLOC factor
		gens.push_back([gen = n1.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			int r1 = regs++, r2 = regs++;
			printf("%%r%d = mul i64 %%r%d, 8\n"
				   "%%r%d = call i64 @malloc(i64 %%r%d)\n", r1, tail, r2, r1);
			return {r2, nullptr};
		});
		break;
	case 13: // rval <- FREE factor
		gens.push_back([gen = n1.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			printf("call void @free(i64 %%r%d)\n", tail);
			return {0, nullptr};
		});
		break;
	case 14: // rval <- rval TIMES rval
	case 15: // rval <- rval DIV rval
	case 16: // rval <- rval PLUS rval
	case 17: // rval <- rval MINUS rval
	case 18: // rval <- rval LT rval
	case 19: // rval <- rval EQ rval
	case 20: // rval <- rval AND rval
	case 21: // rval <- rval XOR rval
	case 22: // rval <- rval OR rval
		gens.push_back([rule, gen1 = n3.gen, gen3 = n1.gen](int &block, int *reg_list)->tails_attr
		{
			int tail1 = f[gen1](block, reg_list).first;
			int tail3 = f[gen3](block, reg_list).first;
			printf("%%r%d = %s i64 %%r%d, %%r%d\n", regs, binary_op[rule - 14], tail1, tail3);
			if(rule / 2 == 9)printf("%%r%d = zext i1 %%r%d to i64\n", regs + 1, regs), regs++;
			return {regs++, nullptr};
		});
		break;
	case 23: // factor <- INT
		gens.push_back([reg = n1.gen](int&, int*)->tails_attr
		{
			return {reg, nullptr};
		});
		break;
	case 24: // factor <- ID
		gens.push_back([id = n1.gen](int&, int *reg_list)->tails_attr
		{
			return {reg_list[id], nullptr};
		});
		break;
	case 25: // factor <- GETC
		gens.push_back([](int&, int*)->tails_attr
		{
			printf("%%r%d = call i64 @getchar()\n", regs);
			return {regs++, nullptr};
		});
		break;
	case 26: // factor <- LPARE exp RPARE
		gen = n2.gen;
		break;
	case 27: // factor <- factor LBRAC exp RBRAC
		gens.push_back([gen1 = n4.gen, gen3 = n2.gen](int &block, int *reg_list)->tails_attr
		{
			int tail1 = f[gen1](block, reg_list).first;
			int tail3 = f[gen3](block, reg_list).first;
			int r1 = regs++, r2 = regs++, r3 = regs++, r4 = regs++;
			printf("%%r%d = mul i64 %%r%d, 8\n"
				   "%%r%d = add i64 %%r%d, %%r%d\n"
				   "%%r%d = inttoptr i64 %%r%d to ptr\n"
				   "%%r%d = load i64, ptr %%r%d\n", r1, tail3,
				   r2, tail1, r1,
				   r3, r2,
				   r4, r3);
			return {r4, nullptr};
		});
		break;
	}
	top -= Prod[rule * 2];
	Node &n0 = p[top];
	auto st = Goto[p[top - 1].state];
	for(int i = 0; ; i += 2)
	{
		if(st[i] == Prod[rule * 2 + 1])
		{
			n0.state = st[i + 1];
			n0.gen = gen;
			break;
		}
	}
	for(int i = top + 1; i < stk.size(); i++)
		n0.chg_list.insert(n0.chg_list.cend(), p[i].chg_list.begin(), p[i].chg_list.end());
	std::sort(n0.chg_list.begin(), n0.chg_list.end());
	n0.chg_list.erase(std::unique(n0.chg_list.begin(), n0.chg_list.end()), n0.chg_list.end());
	stk.resize(top + 1);
}

int Parser::parse()
{
	now_line = 1;
	const_num = 1, id_num = 0;
	sym_tab["0"] = 0;
	for(int i = -5; i <= 0; i++)stk.emplace_back(i, -1, -1);
	gens.push_back([](int&, int*)->tails_attr { return {0, nullptr}; });
	nxtc = getchar();
	Token tk = scan();
	do
	{
		if(tk.type == Default)
		{
			fprintf(stderr, "Unknown token in line %d: %c\n", now_line, tk.val);
			return 1;
		}
		auto st = Action[stk.back().state];
		for(int i = 0; ; i += 2)
		{
			if(st[i] == tk.type)
			{ // shift
				stk.emplace_back(st[i + 1], now_line, tk.val);
				tk = scan();
				break;
			}
			else if(st[i] == Default)
			{
				if(st[i + 1] == -1)
				{ // error
					fprintf(stderr, "Unexpected token in line %d: %s\n\texpected:", now_line, token_name[tk.type]);
					for(i = 0; st[i] != Default; i += 2)fprintf(stderr, " %s", token_name[st[i]]);
					fputc('\n', stderr);
					return 2;
				}
				reduce(st[i + 1]);
				break;
			}
		}
	} while(stk.size());
	return 0;
}