#include "parser.h"
#include "lalr.h"
#include <cctype>
#include <cstring>
#include <algorithm>

constexpr const char char_type[96] = {Default, Default, Default, Default, Default, MOD, AND, Default, LPARE, RPARE, TIMES, PLUS, Default, MINUS, Default, DIV, INT, INT, INT, INT, INT, INT, INT, INT, INT, INT, Default, SEMI, LT, ASSIGN, Default, Default, Default, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, LBRAC, Default, RBRAC, XOR, ID, Default, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, Default, OR, Default, Default, Default};
constexpr const std::pair<const char*, int> reserved_word[8] = {{"free", FREE}, {"putc", PUTC}, {"while", WHILE}, {"getc", GETC}, {"alloc", ALLOC}, {"", Default}, {"elif", ELIF}, {"if", IF}};
constexpr const char *token_name[26] = {"<End of File>", "<Integer>", "<Identifier>", "if", "elif", "while", "getc", "putc", "alloc", "free", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'=='", "'&'", "'|'", "'^'", "'('", "')'", "'['", "']'", "';'"};
constexpr const char *binary_op[10] = {"mul", "sdiv", "srem", "add", "sub", "icmp slt", "icmp eq", "and", "xor", "or"};

Token Parser::scan()
{
	int type, id = -1;
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
			id = sym_tab[str];
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
	else if(type == Default)id = nowc;
	return {type, id};
}

void merge(std::vector<int> &a, std::vector<int> &b)
{
	if(b.empty())return;
	a.insert(a.cend(), b.begin(), b.end());
	std::sort(a.begin(), a.end());
	a.erase(std::unique(a.begin(), a.end()), a.end());
	b.clear();
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
		puts("declare i64 @getchar() nounwind\n"
			 "declare i64 @putchar(i64) nounwind\n"
			 "declare i64 @malloc(i64) nounwind\n"
			 "declare void @free(i64) nounwind\n"
			 "define i32 @main() {\n"
			 "L0:");
		for(auto &it : sym_tab)if(isdigit(it.first.front()))
			printf("%%r%d = add i64 %s, 0\n", it.second, it.first.c_str());
		{
			int block = 0, *reg_list = new int[id_num];
			memset(reg_list, 0, id_num * sizeof(int));
			f[n2.gen](block, reg_list);
			delete[] reg_list;
		}
		puts("ret i32 0\n}");
		return stk.clear(); // accept
	case 1: // stmt_seq <- $epsilon
		_ASSERT(Goto[n1.state][0] == nt_stmt_seq);
		stk.emplace_back(Goto[n1.state][1], now_line, 0);
		return;
	case 2: // stmt_seq <- stmt_seq IF if_stmt SEMI
		gens.push_back([line2 = n3.line, gen1 = n4.gen, gen3 = n2.gen](int &block, int *reg_list)
		{
			f[gen1](block, reg_list);
			printf("; if-statement in line %d\n", line2);
			f[gen3](block, reg_list);
			printf("; end of if-statement in line %d\n", line2);
			return 0;
		});
		break;
	case 3: // stmt_seq <- stmt_seq WHILE exp stmt_seq SEMI
		merge(n2.chg_list, n3.chg_list);
		gens.push_back([chg_list = n2.chg_list, line2 = n4.line, gen1 = n5.gen, gen3 = n3.gen, gen4 = n2.gen](int &block, int *reg_list)
		{
			f[gen1](block, reg_list);
			const int sz = chg_list.size(), *id = chg_list.data();
			int l1 = labels++, l2 = labels++, l3 = labels++, l4 = labels++;
			int r1 = regs, r2 = regs + sz; regs += sz * 2;
			printf("; while-statement in line %d\n", line2);
			printf("br label %%L%d\nL%d:\n", l1, l1);
			for(int i = 0; i < sz; i++)
			{
				printf("%%r%d = phi i64 [%%r%d, %%L%d], [%%r%d, %%L%d]\n",
					   r1 + i, reg_list[id[i]], block, r2 + i, l4);
				reg_list[id[i]] = r1 + i;
			}
			block = l1;
			int tail = f[gen3](block, reg_list);
			printf("%%r%d = icmp ne i64 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail, regs, l2, l3, l2); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			f[gen4](l2, br_list);
			printf("br label %%L%d\nL%d:\n", l4, l4);
			for(int i = 0; i < sz; i++)printf("%%r%d = add i64 %%r%d, 0\n", r2 + i, br_list[id[i]]);
			delete[] br_list;
			printf("br label %%L%d\nL%d:\n", l1, block = l3);
			printf("; end of while-statement in line %d\n", line2);
			return 0;
		});
		break;
	case 4: // stmt_seq <- stmt_seq exp SEMI
		gens.push_back([line2 = n2.line, gen1 = n3.gen, gen2 = n2.gen](int &block, int *reg_list)
		{
			f[gen1](block, reg_list);
			printf("; expression statement in line %d\n", line2);
			f[gen2](block, reg_list);
			return 0;
		});
		break;
	case 5: // if_stmt <- exp stmt_seq
		merge(n2.chg_list, n1.chg_list);
		gens.push_back([chg_list = n2.chg_list, gen1 = n2.gen, gen2 = n1.gen](int &block, int *reg_list)
		{
			int l1 = labels++, l2 = labels++;
			int tail = f[gen1](block, reg_list);
			printf("%%r%d = icmp ne i64 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail, regs, l1, l2, l1); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			f[gen2](l1, br_list);
			printf("br label %%L%d\nL%d:\n", l2, l2);
			for(int id : chg_list)
			{
				printf("%%r%d = phi i64 [%%r%d, %%L%d], [%%r%d, %%L%d]\n",
					   regs, br_list[id], l1, reg_list[id], block);
				reg_list[id] = regs++;
			}
			delete[] br_list;
			block = l2;
			return 0;
		});
		break;
	case 6: // if_stmt <- exp stmt_seq ELIF if_stmt
		merge(n3.chg_list, n1.chg_list);
		merge(n4.chg_list, n3.chg_list);
		gens.push_back([chg_list = n4.chg_list, line3 = n2.line, gen1 = n4.gen, gen2 = n3.gen, gen4 = n1.gen](int &block, int *reg_list)
		{
			int l1 = labels++, l2 = labels++, l3 = labels++;
			int tail = f[gen1](block, reg_list);
			printf("%%r%d = icmp ne i64 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail, regs, l1, l2, l1); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			f[gen2](l1, br_list);
			printf("br label %%L%d\nL%d:\n", l3, l2);
			printf("; elif-statement in line %d\n", line3);
			f[gen4](l2, reg_list);
			printf("br label %%L%d\nL%d:\n", l3, block = l3);
			for(int id : chg_list)
			{
				printf("%%r%d = phi i64 [%%r%d, %%L%d], [%%r%d, %%L%d]\n",
					   regs, br_list[id], l1, reg_list[id], l2);
				reg_list[id] = regs++;
			}
			delete[] br_list;
			return 0;
		});
		break;
	case 7: // exp <- rval
		gen = n1.gen;
		break;
	case 8: // exp <- ID ASSIGN exp
		gens.push_back([id = n3.gen, gen = n1.gen](int &block, int *reg_list)
		{
			return reg_list[id] = f[gen](block, reg_list);
		});
		n3.chg_list.push_back(n3.gen);
		break;
	case 9: // exp <- factor LBRAC exp RBRAC ASSIGN exp
		gens.push_back([gen1 = n6.gen, gen3 = n4.gen, gen6 = n1.gen](int &block, int *reg_list)
		{
			int tail6 = f[gen6](block, reg_list);
			int tail1 = f[gen1](block, reg_list);
			int tail3 = f[gen3](block, reg_list);
			int r1 = regs++, r2 = regs++, r3 = regs++;
			printf("%%r%d = mul i64 %%r%d, 8\n"
				   "%%r%d = add i64 %%r%d, %%r%d\n"
				   "%%r%d = inttoptr i64 %%r%d to ptr\n"
				   "store i64 %%r%d, ptr %%r%d\n", r1, tail3,
				   r2, tail1, r1,
				   r3, r2,
				   tail6, r3);
			return tail6;
		});
		break;
	case 10: // rval <- factor
		gen = n1.gen;
		break;
	case 11: // rval <- GETC
		gens.push_back([](int&, int*)
		{
			printf("%%r%d = call i64 @getchar()\n", regs);
			return regs++;
		});
		break;
	case 12: // rval <- PUTC rval
		gens.push_back([gen = n1.gen](int &block, int *reg_list)
		{
			int tail = f[gen](block, reg_list);
			printf("%%r%d = call i64 @putchar(i64 %%r%d)\n", regs, tail);
			return regs++;
		});
		break;
	case 13: // rval <- ALLOC rval
		gens.push_back([gen = n1.gen](int &block, int *reg_list)
		{
			int tail = f[gen](block, reg_list);
			int r1 = regs++, r2 = regs++;
			printf("%%r%d = mul i64 %%r%d, 8\n"
				   "%%r%d = call i64 @malloc(i64 %%r%d)\n", r1, tail, r2, r1);
			return r2;
		});
		break;
	case 14: // rval <- FREE rval
		gens.push_back([gen = n1.gen](int &block, int *reg_list)
		{
			int tail = f[gen](block, reg_list);
			printf("call void @free(i64 %%r%d)\n", tail);
			return 0;
		});
		break;
	case 15: // rval <- rval TIMES rval
	case 16: // rval <- rval DIV rval
	case 17: // rval <- rval MOD rval
	case 18: // rval <- rval PLUS rval
	case 19: // rval <- rval MINUS rval
	case 20: // rval <- rval LT rval
	case 21: // rval <- rval EQ rval
	case 22: // rval <- rval AND rval
	case 23: // rval <- rval XOR rval
	case 24: // rval <- rval OR rval
		gens.push_back([rule, gen1 = n3.gen, gen3 = n1.gen](int &block, int *reg_list)
		{
			int tail1 = f[gen1](block, reg_list);
			int tail3 = f[gen3](block, reg_list);
			printf("%%r%d = %s i64 %%r%d, %%r%d\n", regs, binary_op[rule - 15], tail1, tail3);
			if(rule / 2 == 10)printf("%%r%d = zext i1 %%r%d to i64\n", regs + 1, regs), regs++;
			return regs++;
		});
		break;
	case 25: // factor <- INT
		gens.push_back([reg = n1.gen](int&, int*){return reg; });
		break;
	case 26: // factor <- ID
		gens.push_back([id = n1.gen](int&, int *reg_list){return reg_list[id]; });
		break;
	case 27: // factor <- LPARE exp RPARE
		gen = n2.gen;
		break;
	case 28: // factor <- factor LBRAC exp RBRAC
		gens.push_back([gen1 = n4.gen, gen3 = n2.gen](int &block, int *reg_list)
		{
			int tail1 = f[gen1](block, reg_list);
			int tail3 = f[gen3](block, reg_list);
			int r1 = regs++, r2 = regs++, r3 = regs++, r4 = regs++;
			printf("%%r%d = mul i64 %%r%d, 8\n"
				   "%%r%d = add i64 %%r%d, %%r%d\n"
				   "%%r%d = inttoptr i64 %%r%d to ptr\n"
				   "%%r%d = load i64, ptr %%r%d\n", r1, tail3,
				   r2, tail1, r1,
				   r3, r2,
				   r4, r3);
			return r4;
		});
		break;
	}
	_ASSERT(Prod[rule * 2] > 0);
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
	for(int i = top + 1; i < stk.size(); i++)merge(n0.chg_list, p[i].chg_list);
	_ASSERT(top + 1 > 6);
	stk.erase(stk.begin() + top + 1, stk.end());
}

int Parser::parse()
{
	now_line = 1;
	const_num = 1, id_num = 0;
	sym_tab["0"] = 0;
	for(int i = -5; i <= 0; i++)stk.emplace_back(i, -1, -1);
	gens.push_back([](int&, int*) { return 0; });
	nxtc = getchar();
	Token tk = scan();
	do
	{
		if(tk.type == Default)
		{
			fprintf(stderr, "Unknown token in line %d: %c\n", now_line, tk.id);
			return 1;
		}
		auto st = Action[stk.back().state];
		for(int i = 0; ; i += 2)
		{
			if(st[i] == tk.type)
			{ // shift
				stk.emplace_back(st[i + 1], now_line, tk.id);
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