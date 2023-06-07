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
	int type, val = 0;
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
	if(type == ID)
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
			if(!sym_tab.count(str))sym_tab[str] = sym_tab.size();
			val = sym_tab[str];
		}
	}
	else if(type == INT)
	{
		val = nowc - '0';
		while(isdigit(nxtc))
		{
			nowc = nxtc, nxtc = getchar();
			val = val * 10 + nowc - '0';
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
	Node n1, n2, n3, n4, n6;
	int sym = -1, line = -1, gen = gens.size();
	std::vector<int> chg_list;
	switch(rule)
	{
	case 0: // program <- stmt_seq EOF
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		stk.pop(); // empty the stack
		id_num = sym_tab.size();
		regs = 1, labels = 1;
		f = gens.data();
		{
			puts("declare i32 @getchar() nounwind\n"
				 "declare i32 @putchar(i32) nounwind\n"
				 "declare i32 @malloc(i32) nounwind\n"
				 "declare void @free(i32) nounwind\n"
				 "define i32 @main() {\n"
				 "L0:\n"
				 "%r0 = add i32 0, 0");
			int block = 0, *reg_list = new int[id_num];
			memset(reg_list, 0, id_num * sizeof(int));
			f[n1.gen](block, reg_list);
			puts("ret i32 0\n}");
			delete[] reg_list;
		}
		return;
	case 1: // stmt_seq <- stmt_seq if_stmt SEMI
		stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_stmt_seq;
		line = n1.line;
		gens.push_back([gen1 = n1.gen, n2](int &block, int *reg_list)->tails_attr
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
				printf("%%r%d = phi i32", reg_list[id] = regs++);
				for(int k = 0; k < sz; k++)printf(" [%%r%d, %%L%d]%c", tab[k].second[id], tab[k].first,
												  k < sz - 1 ? ',' : '\n');
			}
			for(int k = 0; k < sz; k++)delete[] tab[k].second;
			delete tail.second;
			return {0, nullptr};
		});
		chg_list = std::move(n1.chg_list);
		chg_list.insert(chg_list.cend(), n2.chg_list.begin(), n2.chg_list.end());
		break;
	case 2: // stmt_seq <- stmt_seq WHILE exp stmt_seq SEMI
		stk.pop();
		n4 = std::move(stk.top()); stk.pop();
		n3 = std::move(stk.top()); stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_stmt_seq;
		line = n1.line;
		chg_list = std::move(n3.chg_list);
		chg_list.insert(chg_list.cend(), n4.chg_list.begin(), n4.chg_list.end());
		std::sort(chg_list.begin(), chg_list.end());
		chg_list.erase(std::unique(chg_list.begin(), chg_list.end()), chg_list.end());
		gens.push_back([chg_list, line2 = n2.line, gen1 = n1.gen, gen3 = n3.gen, gen4 = n4.gen](int &block, int *reg_list)->tails_attr
		{
			f[gen1](block, reg_list);
			const int sz = chg_list.size(), *id = chg_list.data();
			int l1 = labels++, l2 = labels++, l3 = labels++, l4 = labels++;
			int r1 = regs, r2 = regs + sz; regs += sz * 2;
			printf("br label %%L%d\nL%d: ; while-statement in line %d\n", l1, l1, line2);
			for(int i = 0; i < sz; i++)
			{
				printf("%%r%d = phi i32 [%%r%d, %%L%d], [%%r%d, %%L%d]\n",
					   r1 + i, reg_list[id[i]], block, r2 + i, l4);
				reg_list[id[i]] = r1 + i;
			}
			block = l1;
			int tail = f[gen3](block, reg_list).first;
			printf("%%r%d = icmp ne i32 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail, regs, l2, l3, l2); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			f[gen4](l2, br_list);
			printf("br label %%L%d\nL%d:\n", l4, l4);
			for(int i = 0; i < sz; i++)printf("%%r%d = add i32 %%r%d, 0\n", r2 + i, br_list[id[i]]);
			delete[] br_list;
			printf("br label %%L%d\n"
				   "L%d: ; end of while-statement in line %d\n",
				   l1, block = l3, line2);
			return {0, nullptr};
		});
		chg_list.insert(chg_list.cend(), n1.chg_list.begin(), n1.chg_list.end());
		break;
	case 3: // stmt_seq <- stmt_seq exp SEMI
		stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_stmt_seq;
		line = n1.line;
		gens.push_back([line2 = n2.line, gen1 = n1.gen, gen2 = n2.gen](int &block, int *reg_list)->tails_attr
		{
			f[gen1](block, reg_list);
			printf("; expression statement in line %d\n", line2);
			f[gen2](block, reg_list);
			return {0, nullptr};
		});
		chg_list = std::move(n1.chg_list);
		chg_list.insert(chg_list.cend(), n2.chg_list.begin(), n2.chg_list.end());
		break;
	case 4: // stmt_seq <- $epsilon
		sym = nt_stmt_seq;
		gen = 0;
		break;
	case 5: // if_stmt <- IF exp stmt_seq
		n3 = std::move(stk.top()); stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_if_stmt;
		line = n1.line;
		gens.push_back([line, gen2 = n2.gen, gen3 = n3.gen](int &block, int *reg_list)->tails_attr
		{
			printf("; if-statement in line %d\n", line);
			int tail = f[gen2](block, reg_list).first;
			auto tab = new std::vector<std::pair<int, int*>>;
			int l1 = labels++, l2 = labels++, l3 = labels++;
			printf("%%r%d = icmp ne i32 %%r%d, 0\n"
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
		chg_list = std::move(n2.chg_list);
		chg_list.insert(chg_list.cend(), n3.chg_list.begin(), n3.chg_list.end());
		break;
	case 6: // if_stmt <- if_stmt ELIF exp stmt_seq
		n4 = std::move(stk.top()); stk.pop();
		n3 = std::move(stk.top()); stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_if_stmt;
		line = n1.line;
		gens.push_back([line2 = n2.line, gen1 = n1.gen, gen3 = n3.gen, gen4 = n4.gen](int &block, int *reg_list)->tails_attr
		{
			tails_attr tail1 = f[gen1](block, reg_list);
			printf("; elif-statement in line %d\n", line2);
			int tail3 = f[gen3](block, reg_list).first;
			int l1 = labels++, l2 = labels++;
			printf("%%r%d = icmp ne i32 %%r%d, 0\n"
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
		chg_list = std::move(n1.chg_list);
		chg_list.insert(chg_list.cend(), n3.chg_list.begin(), n3.chg_list.end());
		chg_list.insert(chg_list.cend(), n4.chg_list.begin(), n4.chg_list.end());
		break;
	case 7: // exp <- rval
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_exp;
		line = n1.line;
		gen = n1.gen;
		chg_list = std::move(n1.chg_list);
		break;
	case 8: // exp <- ID ASSIGN exp
		n3 = std::move(stk.top()); stk.pop();
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_exp;
		line = n1.line;
		gens.push_back([id = n1.gen, gen = n3.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			return {reg_list[id] = tail, nullptr};
		});
		chg_list = std::move(n3.chg_list);
		chg_list.push_back(n1.gen);
		break;
	case 9: // exp <- factor LBRAC exp RBRAC ASSIGN exp
		n6 = std::move(stk.top()); stk.pop();
		stk.pop();
		stk.pop();
		n3 = std::move(stk.top()); stk.pop();
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_exp;
		line = n1.line;
		gens.push_back([gen1 = n1.gen, gen3 = n3.gen, gen6 = n6.gen](int &block, int *reg_list)->tails_attr
		{
			int tail6 = f[gen6](block, reg_list).first;
			int tail1 = f[gen1](block, reg_list).first;
			int tail3 = f[gen3](block, reg_list).first;
			int r1 = regs++, r2 = regs++, r3 = regs++;
			printf("%%r%d = mul i32 %%r%d, 4\n"
				   "%%r%d = add i32 %%r%d, %%r%d\n"
				   "%%r%d = inttoptr i32 %%r%d to ptr\n"
				   "store i32 %%r%d, ptr %%r%d\n", r1, tail3,
				   r2, tail1, r1,
				   r3, r2,
				   tail6, r3);
			return {tail6, nullptr};
		});
		chg_list = std::move(n1.chg_list);
		chg_list.insert(chg_list.cend(), n3.chg_list.begin(), n3.chg_list.end());
		chg_list.insert(chg_list.cend(), n6.chg_list.begin(), n6.chg_list.end());
		break;
	case 10: // rval <- factor
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		gen = n1.gen;
		chg_list = std::move(n1.chg_list);
		break;
	case 11: // rval <- PUTC factor
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		gens.push_back([gen = n2.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			printf("%%r%d = call i32 @putchar(i32 %%r%d)\n", regs, tail);
			return {regs++, nullptr};
		});
		chg_list = std::move(n2.chg_list);
		break;
	case 12: // rval <- ALLOC factor
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		gens.push_back([gen = n2.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			int r1 = regs++, r2 = regs++;
			printf("%%r%d = mul i32 %%r%d, 4\n"
				   "%%r%d = call i32 @malloc(i32 %%r%d)\n", r1, tail, r2, r1);
			return {r2, nullptr};
		});
		chg_list = std::move(n2.chg_list);
		break;
	case 13: // rval <- FREE factor
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		gens.push_back([gen = n2.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = f[gen](block, reg_list).first;
			printf("call void @free(i32 %%r%d)\n", tail);
			return {0, nullptr};
		});
		chg_list = std::move(n2.chg_list);
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
		n3 = std::move(stk.top()); stk.pop();
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		gens.push_back([rule, gen1 = n1.gen, gen3 = n3.gen](int &block, int *reg_list)->tails_attr
		{
			int tail1 = f[gen1](block, reg_list).first;
			int tail3 = f[gen3](block, reg_list).first;
			printf("%%r%d = %s i32 %%r%d, %%r%d\n", regs, binary_op[rule - 14], tail1, tail3);
			if(rule / 2 == 9)printf("%%r%d = zext i1 %%r%d to i32\n", regs + 1, regs), regs++;
			return {regs++, nullptr};
		});
		chg_list = std::move(n1.chg_list);
		chg_list.insert(chg_list.cend(), n3.chg_list.begin(), n3.chg_list.end());
		break;
	case 23: // factor <- INT
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gens.push_back([val = n1.gen](int&, int*)->tails_attr
		{
			printf("%%r%d = add i32 %d, 0\n", regs, val);
			return {regs++, nullptr};
		});
		break;
	case 24: // factor <- ID
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gens.push_back([id = n1.gen](int&, int *reg_list)->tails_attr
		{
			return {reg_list[id], nullptr};
		});
		break;
	case 25: // factor <- GETC
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gens.push_back([](int&, int*)->tails_attr
		{
			printf("%%r%d = call i32 @getchar()\n", regs);
			return {regs++, nullptr};
		});
		break;
	case 26: // factor <- LPARE exp RPARE
		stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gen = n2.gen;
		chg_list = std::move(n2.chg_list);
		break;
	case 27: // factor <- factor LBRAC exp RBRAC
		stk.pop();
		n3 = std::move(stk.top()); stk.pop();
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gens.push_back([gen1 = n1.gen, gen3 = n3.gen](int &block, int *reg_list)->tails_attr
		{
			int tail1 = f[gen1](block, reg_list).first;
			int tail3 = f[gen3](block, reg_list).first;
			int r1 = regs++, r2 = regs++, r3 = regs++, r4 = regs++;
			printf("%%r%d = mul i32 %%r%d, 4\n"
				   "%%r%d = add i32 %%r%d, %%r%d\n"
				   "%%r%d = inttoptr i32 %%r%d to ptr\n"
				   "%%r%d = load i32, ptr %%r%d\n", r1, tail3,
				   r2, tail1, r1,
				   r3, r2,
				   r4, r3);
			return {r4, nullptr};
		});
		chg_list = std::move(n1.chg_list);
		chg_list.insert(chg_list.cend(), n3.chg_list.begin(), n3.chg_list.end());
		break;
	}
	std::sort(chg_list.begin(), chg_list.end());
	chg_list.erase(std::unique(chg_list.begin(), chg_list.end()), chg_list.end());
	Node &top = stk.top();
	for(int i = 0; ; i += 2)
	{
		if(Goto[top.state][i] == sym)
		{
			stk.emplace(Goto[top.state][i + 1], line, gen, chg_list);
			break;
		}
	}
}

int Parser::parse()
{
	stk.emplace(0, 0, 0, std::vector<int>{});
	gens.push_back([](int&, int*)->tails_attr { return {0, nullptr}; });
	now_line = 1;
	nxtc = getchar();
	Token tk = scan();
	do
	{
		if(tk.type == Default)
		{
			fprintf(stderr, "Unknown token in line %d: %c\n", now_line, tk.val);
			return 1;
		}
		Node &top = stk.top();
		for(int i = 0; ; i += 2)
		{
			if(Action[top.state][i] == tk.type)
			{ // shift
				stk.emplace(Action[top.state][i + 1], now_line, tk.val, std::vector<int>{});
				tk = scan();
				break;
			}
			else if(Action[top.state][i] == Default)
			{
				if(Action[top.state][i + 1] == -1)
				{ // error
					fprintf(stderr, "Unexpected token in line %d: %s\n\texpected:", now_line, token_name[tk.type]);
					for(i = 0; Action[top.state][i] != Default; i += 2)fprintf(stderr, " %s", token_name[Action[top.state][i]]);
					fputc('\n', stderr);
					return 2;
				}
				reduce(Action[top.state][i + 1]);
				break;
			}
		}
	} while(stk.size());
	return 0;
}
