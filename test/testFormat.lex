%{
int num_lines = 0, num_chars = 0;

%}


digit		[1-9]*[0-9]+
identifier	id[A-Z][a-z]*
mychar		["][a-zA-z]["]

%%

"int"		{ printf("INT"); }
"char"		{ printf("CHAR"); }
"return"	{ printf("RETURN"); }
"if"		{ printf("IF"); }
"while"		{ printf("WHILE"); }
"else"		{ printf("ELSE"); }
"break"		{ printf("BREAK"); }
"print"		{ printf("PRINT"); }
"read"		{ printf("READ"); }

{digit}		{ printf("NUM"); }
[-]{digit}	{ printf("NUM"); }
{identifier}+	{ printf("ID");}
{mychar}	{ printf("MC"); }

"="		{ printf("="); }	
"+"		{ printf("+"); }
"-"		{ printf("-"); }
"*"		{ printf("*"); }
"/"		{ printf("/"); }
"!"		{ printf("!"); }

"=="	{ printf("==");}
"!="	{ printf("!=");}
">"		{printf(">");}
"<"		{printf("<");}
">="	{printf(">=");}
"<="	{ printf("<=");}
"&&"	{ printf("&&");}
"||"	{ printf("||");}

";"		{ printf(";");}
","		{ printf(",");}
"["		{ printf("[");}
"]"		{ printf("]");}
"{"		{ printf("{");}
"}"		{ printf("}");}
"("		{ printf("(");}
")"		{ printf(")");}

"//"[^\n]* { printf("[COMMENT]: %s\n",yytext);}

[ \t]*		{ printf(" ");}
[\n]		{ printf("\n");yylineno++;}
.		{ printf("[UNDEFINED]");}

%%
main()
{
yylex();

}



