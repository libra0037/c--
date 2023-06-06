#include "parser.h"
#include <cctype>
#include <cstring>

// LALR(1) automaton constructed by bison (GNU Bison) 3.0.4
constexpr const char ac0[] = {Default, 0};
constexpr const char ac1[] = {Default, 1};
constexpr const char ac2[] = {Default, 2};
constexpr const char ac3[] = {Default, 3};
constexpr const char ac4[] = {Default, 4};
constexpr const char ac5[] = {Default, 8};
constexpr const char ac6[] = {Default, 9};
constexpr const char ac7[] = {Default, 14};
constexpr const char ac8[] = {Default, 15};
constexpr const char ac9[] = {Default, 23};
constexpr const char ac10[] = {Default, 24};
constexpr const char ac11[] = {Default, 25};
constexpr const char ac12[] = {Default, 26};
constexpr const char ac13[] = {Default, 27};
constexpr const char ac14[] = {SEMI, 26, Default, -1};
constexpr const char ac15[] = {LBRAC, 36, Default, 10};
constexpr const char ac16[] = {LBRAC, 40, Default, 10};
constexpr const char ac17[] = {LBRAC, 40, Default, 11};
constexpr const char ac18[] = {LBRAC, 40, Default, 12};
constexpr const char ac19[] = {LBRAC, 40, Default, 13};
constexpr const char ac20[] = {RBRAC, 57, Default, -1};
constexpr const char ac21[] = {RBRAC, 58, Default, -1};
constexpr const char ac22[] = {RPARE, 41, Default, -1};
constexpr const char ac23[] = {ASSIGN, 16, Default, 24};
constexpr const char ac24[] = {ASSIGN, 59, Default, 27};
constexpr const char ac25[] = {ELIF, 24, SEMI, 25, Default, -1};
constexpr const char ac26[] = {TIMES, 34, DIV, 35, Default, 16};
constexpr const char ac27[] = {TIMES, 34, DIV, 35, Default, 17};
constexpr const char ac28[] = {INT, 3, ID, 19, GETC, 7, LPARE, 11, Default, -1};
constexpr const char ac29[] = {PLUS, 32, MINUS, 33, TIMES, 34, DIV, 35, Default, 18};
constexpr const char ac30[] = {LT, 30, PLUS, 32, MINUS, 33, TIMES, 34, DIV, 35, Default, 19};
constexpr const char ac31[] = {LT, 30, EQ, 31, PLUS, 32, MINUS, 33, TIMES, 34, DIV, 35, Default, 20};
constexpr const char ac32[] = {INT, 3, ID, 4, GETC, 7, PUTC, 8, ALLOC, 9, FREE, 10, LPARE, 11, Default, -1};
constexpr const char ac33[] = {INT, 3, ID, 19, GETC, 7, PUTC, 8, ALLOC, 9, FREE, 10, LPARE, 11, Default, -1};
constexpr const char ac34[] = {AND, 27, LT, 30, EQ, 31, PLUS, 32, MINUS, 33, TIMES, 34, DIV, 35, Default, 21};
constexpr const char ac35[] = {AND, 27, XOR, 29, LT, 30, EQ, 31, PLUS, 32, MINUS, 33, TIMES, 34, DIV, 35, Default, 22};
constexpr const char ac36[] = {INT, 3, ID, 4, IF, 5, WHILE, 6, GETC, 7, PUTC, 8, ALLOC, 9, FREE, 10, LPARE, 11, Default, 5};
constexpr const char ac37[] = {INT, 3, ID, 4, IF, 5, WHILE, 6, GETC, 7, PUTC, 8, ALLOC, 9, FREE, 10, LPARE, 11, Default, 6};
constexpr const char ac38[] = {AND, 27, OR, 28, XOR, 29, LT, 30, EQ, 31, PLUS, 32, MINUS, 33, TIMES, 34, DIV, 35, Default, 7};
constexpr const char ac39[] = {ENDF, 2, INT, 3, ID, 4, IF, 5, WHILE, 6, GETC, 7, PUTC, 8, ALLOC, 9, FREE, 10, LPARE, 11, Default, -1};
constexpr const char ac40[] = {INT, 3, ID, 4, IF, 5, WHILE, 6, GETC, 7, PUTC, 8, ALLOC, 9, FREE, 10, LPARE, 11, SEMI, 54, Default, -1};
constexpr const char *Action[] = {ac4, ac39, ac0, ac9, ac23, ac32, ac32, ac11, ac28, ac28, ac28, ac32, ac25, ac14, ac38, ac15, ac32, ac4, ac4, ac10, ac17, ac18, ac19, ac22, ac32, ac1, ac3, ac33, ac33, ac33, ac33, ac33, ac33, ac33, ac33, ac33, ac32, ac5, ac36, ac40, ac32, ac12, ac4, ac31, ac16, ac35, ac34, ac29, ac30, ac26, ac27, ac7, ac8, ac20, ac2, ac21, ac37, ac24, ac13, ac32, ac6};

constexpr const char go1[] = {nt_factor, 20};
constexpr const char go2[] = {nt_factor, 21};
constexpr const char go3[] = {nt_factor, 22};
constexpr const char go4[] = {nt_stmt_seq, 1};
constexpr const char go5[] = {nt_stmt_seq, 38};
constexpr const char go6[] = {nt_stmt_seq, 39};
constexpr const char go7[] = {nt_stmt_seq, 56};
constexpr const char go8[] = {nt_factor, 44, nt_rval, 43};
constexpr const char go9[] = {nt_factor, 44, nt_rval, 45};
constexpr const char go10[] = {nt_factor, 44, nt_rval, 46};
constexpr const char go11[] = {nt_factor, 44, nt_rval, 47};
constexpr const char go12[] = {nt_factor, 44, nt_rval, 48};
constexpr const char go13[] = {nt_factor, 44, nt_rval, 49};
constexpr const char go14[] = {nt_factor, 44, nt_rval, 50};
constexpr const char go15[] = {nt_factor, 44, nt_rval, 51};
constexpr const char go16[] = {nt_factor, 44, nt_rval, 52};
constexpr const char go17[] = {nt_factor, 15, nt_rval, 14, nt_exp, 17};
constexpr const char go18[] = {nt_factor, 15, nt_rval, 14, nt_exp, 18};
constexpr const char go19[] = {nt_factor, 15, nt_rval, 14, nt_exp, 23};
constexpr const char go20[] = {nt_factor, 15, nt_rval, 14, nt_exp, 37};
constexpr const char go21[] = {nt_factor, 15, nt_rval, 14, nt_exp, 42};
constexpr const char go22[] = {nt_factor, 15, nt_rval, 14, nt_exp, 53};
constexpr const char go23[] = {nt_factor, 15, nt_rval, 14, nt_exp, 55};
constexpr const char go24[] = {nt_factor, 15, nt_rval, 14, nt_exp, 60};
constexpr const char go25[] = {nt_factor, 15, nt_rval, 14, nt_exp, 13, nt_if_stmt, 12};
constexpr const char *Goto[] = {go4, go25, 0, 0, 0, go17, go18, 0, go1, go2, go3, go19, 0, 0, 0, 0, go20, go5, go6, 0, 0, 0, 0, 0, go21, 0, 0, go8, go9, go10, go11, go12, go13, go14, go15, go16, go22, 0, go25, go25, go23, 0, go7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, go25, 0, 0, go24, 0};

constexpr const char char_type[128] = {ENDF, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, Default, AND, Default, LPARE, RPARE, TIMES, PLUS, Default, MINUS, Default, DIV, INT, INT, INT, INT, INT, INT, INT, INT, INT, INT, Default, SEMI, LT, ASSIGN, Default, Default, Default, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, LBRAC, Default, RBRAC, XOR, ID, Default, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, ID, Default, OR, Default, Default, Default};
constexpr const std::pair<const char*, int> reserved_word[8] = {{"free", FREE}, {"putc", PUTC}, {"while", WHILE}, {"getc", GETC}, {"alloc", ALLOC}, {"", Default}, {"elif", ELIF}, {"if", IF}};
constexpr const char *token_name[25] = {"<End of File>", "<Integer>", "<Identifier>", "if", "elif", "while", "getc", "putc", "alloc", "free", "'='", "'<'", "'=='", "'+'", "'-'", "'*'", "'/'", "'&'", "'|'", "'^'", "'('", "')'", "'['", "']'", "';'"};
constexpr const char *binary_op[9] = {"mul", "sdiv", "add", "sub", "icmp slt", "icmp eq", "and", "xor", "or"};

Token Parser::scan()
{
	int t = 1, val = 0;
	do
	{
		nowc = nxtc;
		if(nxtc != EOF)nxtc = getchar();
		now_line += (nowc == '\n');
		if(nowc == EOF)t = 0;
		else if(t == 2)t -= (nowc == '\n');
		else
		{
			if(nowc == '#')t = 2;
			else if(!isspace(nowc))t = 0;
		}
	} while(t);
	int type;
	if(nowc == EOF)type = ENDF;
	else type = unsigned(nowc) < 128 ? char_type[nowc] : Default;
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
			if(!sym_tab.count(str))sym_tab[str] = id_num++;
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
	else if(type == ASSIGN && nxtc == '=')
	{
		nowc = nxtc, nxtc = getchar();
		type = EQ;
	}
	else if(type == Default)val = nowc;
	return {type, val};
}

void Parser::reduce(int rule)
{
	Node n1, n2, n3, n4, n6;
	int sym = -1;
	int line = -1;
	std::set<int> chg_list;
	code_generator *gen = nullptr;
	switch(rule)
	{
	case 0: // program <- stmt_seq EOF
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		stk.pop(); // empty the stack
		output_code = [this, gen = n1.gen]()
		{
			puts("declare i32 @getchar() nounwind\n"
				 "declare i32 @putchar(i32) nounwind\n"
				 "declare i32 @malloc(i32) nounwind\n"
				 "declare void @free(i32) nounwind\n"
				 "define i32 @main() {\n"
				 "L0:\n"
				 "%r0 = add i32 0, 0");
			regs = 1, labels = 1;
			int block = 0, *reg_list = new int[id_num];
			memset(reg_list, 0, id_num * sizeof(int));
			(*gen)(block, reg_list); delete gen;
			puts("ret i32 0\n}");
			delete reg_list;
		};
		return;
	case 1: // stmt_seq <- stmt_seq if_stmt SEMI
		stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_stmt_seq;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		chg_list.insert(n2.chg_list.begin(), n2.chg_list.end());
		gen = new code_generator([this, gen1 = n1.gen, n2](int &block, int *reg_list)->tails_attr
		{
			(*gen1)(block, reg_list); delete gen1;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			tails_attr tail = (*n2.gen)(block, br_list); delete n2.gen;
			tail.second->insert({block, br_list});
			printf("br label %%L%d\nL%d: ; end of if-statement in line %d\n",
				   tail.first, block = tail.first, n2.line);
			for(int id : n2.chg_list)
			{
				printf("%%r%d = phi i32", reg_list[id] = regs++);
				int k = 0, sz = tail.second->size();
				for(auto lab : *tail.second)printf(" [%%r%d, %%L%d]%c", lab.second[id], lab.first,
												   ",\n"[++k == sz]);
			}
			for(auto lab : *tail.second)delete lab.second;
			delete tail.second;
			return {0, nullptr};
		});
		break;
	case 2: // stmt_seq <- stmt_seq WHILE exp stmt_seq SEMI
		stk.pop();
		n4 = std::move(stk.top()); stk.pop();
		n3 = std::move(stk.top()); stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_stmt_seq;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		chg_list.insert(n3.chg_list.begin(), n3.chg_list.end());
		chg_list.insert(n4.chg_list.begin(), n4.chg_list.end());
		gen = new code_generator([this, line2 = n2.line, gen1 = n1.gen, n3, n4](int &block, int *reg_list)->tails_attr
		{
			(*gen1)(block, reg_list); delete gen1;
			std::set<int> ids;
			ids.insert(n3.chg_list.begin(), n3.chg_list.end());
			ids.insert(n4.chg_list.begin(), n4.chg_list.end());
			int l1 = labels++, l2 = labels++, l3 = labels++, l4 = labels++;
			int i = 0, r1 = regs, r2 = regs + ids.size(); regs += ids.size() * 2;
			printf("br label %%L%d\nL%d: ; while-statement in line %d\n", l1, l1, line2);
			for(int id : ids)
			{
				printf("%%r%d = phi i32 [%%r%d, %%L%d], [%%r%d, %%L%d]\n",
					   r1 + i, reg_list[id], block, r2 + i, l4);
				reg_list[id] = r1 + i;
				i++;
			}
			block = l1;
			int tail = (*n3.gen)(block, reg_list).first; delete n3.gen;
			printf("%%r%d = icmp ne i32 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail, regs, l2, l3, l2); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			(*n4.gen)(l2, br_list); delete n4.gen;
			printf("br label %%L%d\nL%d:\n", l4, l4);
			i = 0;
			for(int id : ids)
			{
				printf("%%r%d = add i32 %%r%d, 0\n", r2 + i, br_list[id]);
				i++;
			}
			delete br_list;
			printf("br label %%L%d\n"
				   "L%d: ; end of while-statement in line %d\n",
				   l1, block = l3, line2);
			return {0, nullptr};
		});
		break;
	case 3: // stmt_seq <- stmt_seq exp SEMI
		stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_stmt_seq;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		chg_list.insert(n2.chg_list.begin(), n2.chg_list.end());
		gen = new code_generator([line2 = n2.line, gen1 = n1.gen, gen2 = n2.gen](int &block, int *reg_list)->tails_attr
		{
			(*gen1)(block, reg_list); delete gen1;
			printf("; expression statement in line %d\n", line2);
			(*gen2)(block, reg_list); delete gen2;
			return {0, nullptr};
		});
		break;
	case 4: // stmt_seq <- $epsilon
		sym = nt_stmt_seq;
		line = 0;
		gen = new code_generator([](int&, int*)->tails_attr { return {0, nullptr}; });
		break;
	case 5: // if_stmt <- IF exp stmt_seq
		n3 = std::move(stk.top()); stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_if_stmt;
		line = n1.line;
		chg_list = std::move(n2.chg_list);
		chg_list.insert(n3.chg_list.begin(), n3.chg_list.end());
		gen = new code_generator([this, line, gen2 = n2.gen, gen3 = n3.gen](int &block, int *reg_list)->tails_attr
		{
			printf("; if-statement in line %d\n", line);
			int tail = (*gen2)(block, reg_list).first; delete gen2;
			auto tab = new std::set<std::pair<int, int*>>;
			int l1 = labels++, l2 = labels++, l3 = labels++;
			printf("%%r%d = icmp ne i32 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail,
				   regs, l1, l2, l1); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			(*gen3)(l1, br_list); delete gen3;
			tab->insert({l1, br_list});
			printf("br label %%L%d\nL%d:\n", l3, block = l2);
			return {l3, tab};
		});
		break;
	case 6: // if_stmt <- if_stmt ELIF exp stmt_seq
		n4 = std::move(stk.top()); stk.pop();
		n3 = std::move(stk.top()); stk.pop();
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_if_stmt;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		chg_list.insert(n3.chg_list.begin(), n3.chg_list.end());
		chg_list.insert(n4.chg_list.begin(), n4.chg_list.end());
		gen = new code_generator([this, line2 = n2.line, gen1 = n1.gen, gen3 = n3.gen, gen4 = n4.gen](int &block, int *reg_list)->tails_attr
		{
			tails_attr tail1 = (*gen1)(block, reg_list); delete gen1;
			printf("; elif-statement in line %d\n", line2);
			int tail3 = (*gen3)(block, reg_list).first; delete gen3;
			int l1 = labels++, l2 = labels++;
			printf("%%r%d = icmp ne i32 %%r%d, 0\n"
				   "br i1 %%r%d, label %%L%d, label %%L%d\n"
				   "L%d:\n", regs, tail3,
				   regs, l1, l2, l1); regs++;
			int *br_list = new int[id_num];
			memcpy(br_list, reg_list, id_num * sizeof(int));
			(*gen4)(l1, br_list); delete gen4;
			tail1.second->insert({l1, br_list});
			printf("br label %%L%d\nL%d:\n", tail1.first, block = l2);
			return tail1;
		});
		break;
	case 7: // exp <- rval
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_exp;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		gen = n1.gen;
		break;
	case 8: // exp <- ID ASSIGN exp
		n3 = std::move(stk.top()); stk.pop();
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_exp;
		line = n1.line;
		chg_list = std::move(n3.chg_list);
		chg_list.insert((int)(ptrdiff_t)n1.gen);
		gen = new code_generator([id = (int)(ptrdiff_t)n1.gen, gen = n3.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = (*gen)(block, reg_list).first; delete gen;
			return {reg_list[id] = tail, nullptr};
		});
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
		chg_list = std::move(n1.chg_list);
		chg_list.insert(n3.chg_list.begin(), n3.chg_list.end());
		chg_list.insert(n6.chg_list.begin(), n6.chg_list.end());
		gen = new code_generator([this, gen1 = n1.gen, gen3 = n3.gen, gen6 = n6.gen](int &block, int *reg_list)->tails_attr
		{
			int tail6 = (*gen6)(block, reg_list).first; delete gen6;
			int tail1 = (*gen1)(block, reg_list).first; delete gen1;
			int tail3 = (*gen3)(block, reg_list).first; delete gen3;
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
		break;
	case 10: // rval <- factor
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		gen = n1.gen;
		break;
	case 11: // rval <- PUTC factor
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		chg_list = std::move(n2.chg_list);
		gen = new code_generator([this, gen = n2.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = (*gen)(block, reg_list).first; delete gen;
			printf("%%r%d = call i32 @putchar(i32 %%r%d)\n", regs, tail);
			return {regs++, nullptr};
		});
		break;
	case 12: // rval <- ALLOC factor
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		chg_list = std::move(n2.chg_list);
		gen = new code_generator([this, gen = n2.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = (*gen)(block, reg_list).first; delete gen;
			int r1 = regs++, r2 = regs++;
			printf("%%r%d = mul i32 %%r%d, 4\n"
				   "%%r%d = call i32 @malloc(i32 %%r%d)\n", r1, tail, r2, r1);
			return {r2, nullptr};
		});
		break;
	case 13: // rval <- FREE factor
		n2 = std::move(stk.top()); stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		chg_list = std::move(n2.chg_list);
		gen = new code_generator([this, gen = n2.gen](int &block, int *reg_list)->tails_attr
		{
			int tail = (*gen)(block, reg_list).first; delete gen;
			printf("call void @free(i32 %%r%d)\n", tail);
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
		n3 = std::move(stk.top()); stk.pop();
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_rval;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		chg_list.insert(n3.chg_list.begin(), n3.chg_list.end());
		gen = new code_generator([this, rule, gen1 = n1.gen, gen3 = n3.gen](int &block, int *reg_list)->tails_attr
		{
			int tail1 = (*gen1)(block, reg_list).first; delete gen1;
			int tail3 = (*gen3)(block, reg_list).first; delete gen3;
			printf("%%r%d = %s i32 %%r%d, %%r%d\n", regs, binary_op[rule - 14], tail1, tail3);
			if(rule / 2 == 9)printf("%%r%d = zext i1 %%r%d to i32\n", regs + 1, regs), regs++;
			return {regs++, nullptr};
		});
		break;
	case 23: // factor <- INT
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gen = new code_generator([this, val = (int)(ptrdiff_t)n1.gen](int&, int*)->tails_attr
		{
			printf("%%r%d = add i32 %d, 0\n", regs, val);
			return {regs++, nullptr};
		});
		break;
	case 24: // factor <- ID
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gen = new code_generator([id = (int)(ptrdiff_t)n1.gen](int&, int *reg_list)->tails_attr
		{
			return {reg_list[id], nullptr};
		});
		break;
	case 25: // factor <- GETC
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		gen = new code_generator([this](int&, int*)->tails_attr
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
		chg_list = std::move(n2.chg_list);
		gen = n2.gen;
		break;
	case 27: // factor <- factor LBRAC exp RBRAC
		stk.pop();
		n3 = std::move(stk.top()); stk.pop();
		stk.pop();
		n1 = std::move(stk.top()); stk.pop();
		sym = nt_factor;
		line = n1.line;
		chg_list = std::move(n1.chg_list);
		chg_list.insert(n3.chg_list.begin(), n3.chg_list.end());
		gen = new code_generator([this, gen1 = n1.gen, gen3 = n3.gen](int &block, int *reg_list)->tails_attr
		{
			int tail1 = (*gen1)(block, reg_list).first; delete gen1;
			int tail3 = (*gen3)(block, reg_list).first; delete gen3;
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
		break;
	}
	Node &top = stk.top();
	for(int i = 0; ; i += 2)
	{
		if(Goto[top.state][i] == sym)
		{
			stk.emplace(Goto[top.state][i + 1], line, chg_list, gen);
			break;
		}
	}
}

int Parser::parse()
{
	stk.emplace(0, 0, std::set<int>(), nullptr);
	now_line = 1;
	nxtc = getchar();
	id_num = 0;
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
				stk.emplace(Action[top.state][i + 1], now_line, std::set<int>(),
					(code_generator*)(ptrdiff_t)tk.val);
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
	output_code();
	return 0;
}
