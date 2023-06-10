#include "parser.h"

int main(int argc, char **argv)
{
	if(argc > 1 && !freopen(argv[1], "r", stdin))
		return fprintf(stderr, "Failed to open '%s'.\n", argv[1]), -1;
	if(argc > 2 && !freopen(argv[2], "w", stdout))
		return fprintf(stderr, "Failed to create '%s'.\n", argv[2]), -1;
	return parse().err;
}