#include "parser.h"

int main(int argc, char **argv)
{
	if(argc > 1)freopen(argv[1], "r", stdin);
	if(argc > 2)freopen(argv[2], "w", stdout);
	return Parser{}.parse();
}