#include <vector>
#include <unordered_map>
#include <functional>

enum Token_t
{
	ENDF,	// EOF
	INT,	// \d+
	ID,		// [a-zA-Z_]\w*
	IF,		// if
	ELIF,	// elif
	WHILE,	// while
	GETC,	// getc
	PUTC,	// putc
	ALLOC,	// alloc
	FREE,	// free
	ASSIGN,	// =
	LT,		// <
	EQ,		// ==
	PLUS,	// +
	MINUS,	// -
	TIMES,	// *
	DIV,	// /
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
	nt_factor,
	nt_rval,
	nt_exp,
	nt_if_stmt,
	nt_stmt_seq,
};

struct Token
{
	int type, val;
};

using tails_attr = std::pair<int, std::vector<std::pair<int, int*>>*>;
using code_generator = std::function<tails_attr(int&, int*)>;

struct Node
{
	Node() {}
	template<class T>
	Node(int s, int l, int g, T &&c)
		: state(s), line(l), gen(g), chg_list(std::move(c))
	{
	}
	int state, line, gen;
	std::vector<int> chg_list;
};

class Parser
{
public:
	int parse();
private:
	Token scan();
	void reduce(int rule);
private:
	int now_line;
	int nowc, nxtc;
	std::unordered_map<std::string, int> sym_tab;
	std::vector<Node> stk;
	std::vector<code_generator> gens;
};
