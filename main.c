#include "heading.h"

int yyparse();

int main(int argc, char **argv)
{
	if((argc > 1) && (freopen(argv[1], "r", stdin) == NULL)) 
		cerr << "frepoen()";

	yyparse();

	return 0;
}
