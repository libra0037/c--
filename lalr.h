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
constexpr const char _Table[] = {ALLOC, 9, ELIF, 54, FREE, 10, GETC, 7, ID, 4, IF, 5, INT, 3, LPARE, 11, PUTC, 8, WHILE, 6, Default, 5, ALLOC, 9, ENDF, 2, FREE, 10, GETC, 7, ID, 4, IF, 5, INT, 3, LPARE, 11, PUTC, 8, WHILE, 6, Default, -1, ALLOC, 9, FREE, 10, GETC, 7, ID, 4, IF, 5, INT, 3, LPARE, 11, PUTC, 8, SEMI, 55, WHILE, 6, Default, -1, ALLOC, 9, FREE, 10, GETC, 7, ID, 4, INT, 3, LPARE, 11, PUTC, 8, Default, -1, ALLOC, 9, FREE, 10, GETC, 7, ID, 19, INT, 3, LPARE, 11, PUTC, 8, Default, -1, AND, 33, DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, OR, 34, PLUS, 26, TIMES, 28, XOR, 35, Default, 7, AND, 33, DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, XOR, 35, Default, 24, AND, 33, DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 23, ASSIGN, 15, Default, 26, ASSIGN, 60, Default, 28, DIV, 29, EQ, 32, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 22, DIV, 29, LT, 31, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 21, DIV, 29, MINUS, 27, MOD, 30, PLUS, 26, TIMES, 28, Default, 20, DIV, 29, MOD, 30, TIMES, 28, Default, 18, DIV, 29, MOD, 30, TIMES, 28, Default, 19, LBRAC, 36, Default, 10, LBRAC, 41, Default, 10, RBRAC, 57, Default, -1, RBRAC, 59, Default, -1, RPARE, 42, Default, -1, SEMI, 25, Default, -1, SEMI, 38, Default, -1, Default, 0, Default, 1, Default, 2, Default, 3, Default, 4, Default, 6, Default, 8, Default, 9, Default, 11, Default, 12, Default, 13, Default, 14, Default, 15, Default, 16, Default, 17, Default, 25, Default, 26, Default, 27, Default, 28, nt_exp, 12, nt_factor, 14, nt_rval, 13, nt_exp, 17, nt_factor, 14, nt_if_stmt, 16, nt_rval, 13, nt_exp, 17, nt_factor, 14, nt_if_stmt, 58, nt_rval, 13, nt_exp, 18, nt_factor, 14, nt_rval, 13, nt_exp, 24, nt_factor, 14, nt_rval, 13, nt_exp, 37, nt_factor, 14, nt_rval, 13, nt_exp, 53, nt_factor, 14, nt_rval, 13, nt_exp, 56, nt_factor, 14, nt_rval, 13, nt_exp, 61, nt_factor, 14, nt_rval, 13, nt_factor, 21, nt_rval, 20, nt_factor, 21, nt_rval, 22, nt_factor, 21, nt_rval, 23, nt_factor, 21, nt_rval, 43, nt_factor, 21, nt_rval, 44, nt_factor, 21, nt_rval, 45, nt_factor, 21, nt_rval, 46, nt_factor, 21, nt_rval, 47, nt_factor, 21, nt_rval, 48, nt_factor, 21, nt_rval, 49, nt_factor, 21, nt_rval, 50, nt_factor, 21, nt_rval, 51, nt_factor, 21, nt_rval, 52, nt_stmt_seq, 1, nt_stmt_seq, 39, nt_stmt_seq, 40};
constexpr const char *Action[] = {_Table + 254, _Table + 22, _Table + 252, _Table + 282, _Table + 158, _Table + 66, _Table + 66, _Table + 268, _Table + 82, _Table + 82, _Table + 82, _Table + 66, _Table + 244, _Table + 98, _Table + 224, _Table + 66, _Table + 248, _Table + 254, _Table + 254, _Table + 284, _Table + 270, _Table + 228, _Table + 272, _Table + 274, _Table + 240, _Table + 260, _Table + 82, _Table + 82, _Table + 82, _Table + 82, _Table + 82, _Table + 82, _Table + 82, _Table + 82, _Table + 82, _Table + 82, _Table + 66, _Table + 264, _Table + 256, _Table + 0, _Table + 44, _Table + 66, _Table + 286, _Table + 208, _Table + 216, _Table + 276, _Table + 278, _Table + 280, _Table + 196, _Table + 182, _Table + 166, _Table + 120, _Table + 140, _Table + 232, _Table + 66, _Table + 258, _Table + 236, _Table + 162, _Table + 262, _Table + 288, _Table + 66, _Table + 266};
constexpr const char *Goto[] = {_Table + 400, _Table + 290, nullptr, nullptr, nullptr, _Table + 296, _Table + 312, nullptr, _Table + 348, _Table + 352, _Table + 356, _Table + 318, nullptr, nullptr, nullptr, _Table + 324, nullptr, _Table + 402, _Table + 404, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, _Table + 360, _Table + 364, _Table + 368, _Table + 372, _Table + 376, _Table + 380, _Table + 384, _Table + 388, _Table + 392, _Table + 396, _Table + 330, nullptr, nullptr, _Table + 290, _Table + 290, _Table + 336, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, _Table + 304, nullptr, nullptr, nullptr, nullptr, nullptr, _Table + 342, nullptr};