#include "parser.h"

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		if(!freopen(argv[1], "r", stdin))
		{
			fprintf(stderr, "Failed to open '%s'.\n", argv[1]);
			return -1;
		}
	}
	if(argc > 2)
	{
		if(!freopen(argv[2], "w", stdout))
		{
			fprintf(stderr, "Failed to create '%s'.\n", argv[2]);
			return -1;
		}
	}
	return Parser{}.parse();
}