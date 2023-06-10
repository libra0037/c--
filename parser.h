#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

enum Token_t
{
	ENDF,	// EOF
	INT,	// [0-9]\w*
	ID,		// [a-zA-Z_]\w*
	IF,		// if
	ELIF,	// elif
	WHILE,	// while
	GETC,	// getc
	PUTC,	// putc
	ALLOC,	// alloc
	FREE,	// free
	ASSIGN,	// =
	PLUS,	// +
	MINUS,	// -
	TIMES,	// *
	DIV,	// /
	MOD,	// %
	LT,		// <
	EQ,		// ==
	AND,	// &
	OR,		// |
	XOR,	// ^
	LPARE,	// (
	RPARE,	// )
	LBRAC,	// [
	RBRAC,	// ]
	SEMI,	// ;
	Default = -1,
};

enum Nonterminal_t
{
	nt_stmt_seq,
	nt_if_stmt,
	nt_exp,
	nt_rval,
	nt_factor,
};

struct Token
{
	int type, id;
};

using code_generator = std::function<int(int&, int*)>;

struct Node
{
	Node(int s, int l, int g): state(s), line(l), gen(g) {}
	int state, line, gen;
	std::vector<int> chg_list;
};

class parse
{
public:
	parse();
	int err;
private:
	Token scan();
	void reduce(int rule);
private:
	int now_line;
	int nowc, nxtc;
	int const_num, id_num;
	std::unordered_map<std::string, int> sym_tab;
	std::vector<Node> stk;
	std::vector<code_generator> gens;
};