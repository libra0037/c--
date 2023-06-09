// LALR(1) automaton constructed by bison (GNU Bison) 3.0.4

/*
%left OR
%left XOR
%left AND
%nonassoc EQ
%nonassoc LT
%left PLUS MINUS
%left TIMES DIV MOD
%precedence FUNC_OP

%%

stmt_seq: %empty
		| stmt_seq IF if_stmt SEMI
		| stmt_seq WHILE exp stmt_seq SEMI
		| stmt_seq exp SEMI
		;

if_stmt	: exp stmt_seq
		| exp stmt_seq ELIF if_stmt
		;

exp		: rval
		| ID ASSIGN exp
		| factor LBRAC exp RBRAC ASSIGN exp
		;

rval	: factor
		| GETC
		| PUTC rval		%prec FUNC_OP
		| ALLOC rval	%prec FUNC_OP
		| FREE rval		%prec FUNC_OP
		| rval TIMES rval
		| rval DIV rval
		| rval MOD rval
		| rval PLUS rval
		| rval MINUS rval
		| rval LT rval
		| rval EQ rval
		| rval AND rval
		| rval XOR rval
		| rval OR rval
		;

factor	: INT
		| ID
		| LPARE exp RPARE
		| factor LBRAC exp RBRAC
		;

%%
*/

constexpr const char Prod[] = {2, -1, 0, nt_stmt_seq, 4, nt_stmt_seq, 5, nt_stmt_seq, 3, nt_stmt_seq, 2, nt_if_stmt, 4, nt_if_stmt, 1, nt_exp, 3, nt_exp, 6, nt_exp, 1, nt_rval, 1, nt_rval, 2, nt_rval, 2, nt_rval, 2, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 1, nt_factor, 1, nt_factor, 3, nt_factor, 4, nt_factor};

constexpr const char ac21[] = {ALLOC, 9, ELIF, 54, FREE, 10, GETC, 7, ID, 4, IF, 5, INT, 3, LPARE, 11, PUTC, 8, WHILE, 6, Default, 5};
constexpr const char ac1[] = {ALLOC, 9, ENDF, 2, FREE, 10, GETC, 7, ID, 4, IF, 5, INT, 3, LPARE, 11, PUTC, 8, WHILE, 6};
constexpr const char ac22[] = {ALLOC, 9, FREE, 10, GETC, 7, ID, 4, IF, 5, INT, 3, LPARE, 11, PUTC, 8, SEMI, 55, WHILE, 6};
constexpr const char ac5[] = {ALLOC, 9, FREE, 10, GETC, 7, ID, 4, INT, 3, LPARE, 11, PUTC, 8};
constexpr const char ac7[] = {ALLOC, 9, FREE, 10, GETC, 7, ID, 19, INT, 3, LPARE, 11, PUTC, 8};
constexpr const char ac9[] = {AND, 33, DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, OR, 34, PLUS, 26, TIMES, 28, XOR, 35, Default, 7};
constexpr const char ac32[] = {AND, 33, DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, XOR, 35, Default, 24};
constexpr const char ac33[] = {AND, 33, DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 23};
constexpr const char ac4[] = {ASSIGN, 15, Default, 26};
constexpr const char ac37[] = {ASSIGN, 60, Default, 28};
constexpr const char ac31[] = {DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 22};
constexpr const char ac30[] = {DIV, 29, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 21};
constexpr const char ac29[] = {DIV, 29, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 20};
constexpr const char ac24[] = {DIV, 29, MOD, 30, TIMES, 28, Default, 18};
constexpr const char ac25[] = {DIV, 29, MOD, 30, TIMES, 28, Default, 19};
constexpr const char ac10[] = {LBRAC, 36, Default, 10};
constexpr const char ac14[] = {LBRAC, 41, Default, 10};
constexpr const char ac34[] = {RBRAC, 57};
constexpr const char ac36[] = {RBRAC, 59};
constexpr const char ac17[] = {RPARE, 42};
constexpr const char ac8[] = {SEMI, 25};
constexpr const char ac11[] = {SEMI, 38};
constexpr const char ac2[] = {Default, 0};
constexpr const char ac0[] = {Default, 1};
constexpr const char ac20[] = {Default, 2};
constexpr const char ac35[] = {Default, 3};
constexpr const char ac18[] = {Default, 4};
constexpr const char ac38[] = {Default, 6};
constexpr const char ac19[] = {Default, 8};
constexpr const char ac40[] = {Default, 9};
constexpr const char ac6[] = {Default, 11};
constexpr const char ac13[] = {Default, 12};
constexpr const char ac15[] = {Default, 13};
constexpr const char ac16[] = {Default, 14};
constexpr const char ac26[] = {Default, 15};
constexpr const char ac27[] = {Default, 16};
constexpr const char ac28[] = {Default, 17};
constexpr const char ac3[] = {Default, 25};
constexpr const char ac12[] = {Default, 26};
constexpr const char ac23[] = {Default, 27};
constexpr const char ac39[] = {Default, 28};
constexpr const char *Action[] = {ac0, ac1, ac2, ac3, ac4, ac5, ac5, ac6, ac7, ac7, ac7, ac5, ac8, ac9, ac10, ac5, ac11, ac0, ac0, ac12, ac13, ac14, ac15, ac16, ac17, ac18, ac7, ac7, ac7, ac7, ac7, ac7, ac7, ac7, ac7, ac7, ac5, ac19, ac20, ac21, ac22, ac5, ac23, ac24, ac25, ac26, ac27, ac28, ac29, ac30, ac31, ac32, ac33, ac34, ac5, ac35, ac36, ac37, ac38, ac39, ac5, ac40};

constexpr const char go2[] = {nt_exp, 12, nt_factor, 14, nt_rval, 13};
constexpr const char go3[] = {nt_exp, 17, nt_factor, 14, nt_if_stmt, 16, nt_rval, 13};
constexpr const char go24[] = {nt_exp, 17, nt_factor, 14, nt_if_stmt, 58, nt_rval, 13};
constexpr const char go4[] = {nt_exp, 18, nt_factor, 14, nt_rval, 13};
constexpr const char go8[] = {nt_exp, 24, nt_factor, 14, nt_rval, 13};
constexpr const char go9[] = {nt_exp, 37, nt_factor, 14, nt_rval, 13};
constexpr const char go22[] = {nt_exp, 53, nt_factor, 14, nt_rval, 13};
constexpr const char go23[] = {nt_exp, 56, nt_factor, 14, nt_rval, 13};
constexpr const char go25[] = {nt_exp, 61, nt_factor, 14, nt_rval, 13};
constexpr const char go5[] = {nt_factor, 21, nt_rval, 20};
constexpr const char go6[] = {nt_factor, 21, nt_rval, 22};
constexpr const char go7[] = {nt_factor, 21, nt_rval, 23};
constexpr const char go12[] = {nt_factor, 21, nt_rval, 43};
constexpr const char go13[] = {nt_factor, 21, nt_rval, 44};
constexpr const char go14[] = {nt_factor, 21, nt_rval, 45};
constexpr const char go15[] = {nt_factor, 21, nt_rval, 46};
constexpr const char go16[] = {nt_factor, 21, nt_rval, 47};
constexpr const char go17[] = {nt_factor, 21, nt_rval, 48};
constexpr const char go18[] = {nt_factor, 21, nt_rval, 49};
constexpr const char go19[] = {nt_factor, 21, nt_rval, 50};
constexpr const char go20[] = {nt_factor, 21, nt_rval, 51};
constexpr const char go21[] = {nt_factor, 21, nt_rval, 52};
constexpr const char go1[] = {nt_stmt_seq, 1};
constexpr const char go10[] = {nt_stmt_seq, 39};
constexpr const char go11[] = {nt_stmt_seq, 40};

constexpr const char *Goto[] = {go1, go2, nullptr, nullptr, nullptr, go3, go4, nullptr, go5, go6, go7, go8, nullptr, nullptr, nullptr, go9, nullptr, go10, go11, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, go12, go13, go14, go15, go16, go17, go18, go19, go20, go21, go22, nullptr, nullptr, go2, go2, go23, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, go24, nullptr, nullptr, nullptr, nullptr, nullptr, go25, nullptr};