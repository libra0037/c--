// LALR(1) automaton constructed by bison (GNU Bison) 3.0.4

/*
%token INT
%token ID
%token IF
%token ELIF
%token WHILE
%token AND
%token OR
%token XOR
%token GETC
%token PUTC
%token ALLOC
%token FREE
%token ASSIGN
%token LE
%token EQ
%token PLUS
%token MINUS
%token TIMES
%token DIV
%token LPARE
%token RPARE
%token LBRAC
%token RBRAC
%token SEMI

%left OR
%left XOR
%left AND
%left EQ
%left LE
%left PLUS MINUS
%left TIMES DIV

%%

stmt_seq: stmt_seq if_stmt SEMI
		| stmt_seq WHILE exp stmt_seq SEMI
		| stmt_seq exp SEMI
		| %empty
		;

if_stmt	: IF exp stmt_seq
		| if_stmt ELIF exp stmt_seq
		;

exp		: rval
		| ID ASSIGN exp
		| factor LBRAC exp RBRAC ASSIGN exp
		;

rval	: factor
		| PUTC factor
		| ALLOC factor
		| FREE factor
		| rval TIMES rval
		| rval DIV rval
		| rval PLUS rval
		| rval MINUS rval
		| rval LE rval
		| rval EQ rval
		| rval AND rval
		| rval XOR rval
		| rval OR rval
		;

factor	: INT
		| ID
		| GETC
		| LPARE exp RPARE
		| factor LBRAC exp RBRAC
		;

%%
*/

constexpr const char Prod[] = {2, 5, 3, nt_stmt_seq, 5, nt_stmt_seq, 3, nt_stmt_seq, 0, nt_stmt_seq, 3, nt_if_stmt, 4, nt_if_stmt, 1, nt_exp, 3, nt_exp, 6, nt_exp, 1, nt_rval, 2, nt_rval, 2, nt_rval, 2, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 3, nt_rval, 1, nt_factor, 1, nt_factor, 1, nt_factor, 3, nt_factor, 4, nt_factor};

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