%{
#include "heading.h"
#include "tok.h"

using std::string;
int yyerror(char *s);
int yyerror();

%}


digit		[1-9]*[0-9]+
identifier	id[A-Z][a-z]*
mychar		["][a-zA-z]["]

%%

"int"		{ yylval.str = new std::string(yytext); return INT; }
"char"		{ yylval.str = new std::string(yytext); return CHAR; }
"return"	{ yylval.str = new std::string(yytext); return RETURN; }
"if"		{ yylval.str = new std::string(yytext); return IF; }
"while"		{ yylval.str = new std::string(yytext); return WHILE; }
"else"		{ yylval.str = new std::string(yytext); return ELSE; }
"break"		{ yylval.str = new std::string(yytext); return BREAK; }
"print"		{ yylval.str = new std::string(yytext); return PRINT; }
"read"		{ yylval.str = new std::string(yytext); return READ; }

{digit}		{ yylval.val = atoi(yytext); return NUM; }
[-]{digit}	{ yylval.val = atoi(yytext); return NUM; }
{identifier}+	{ yylval.str = new std::string(yytext); return ID;}
{mychar}	{ yylval.str = new std::string(yytext); return MYCHAR; }

"="		{ yylval.str = new std::string(yytext); return '='; }	
"+"		{ yylval.str = new std::string(yytext); return '+'; }
"-"		{ yylval.str = new std::string(yytext); return '-'; }
"*"		{ yylval.str = new std::string(yytext); return '*'; }
"/"		{ yylval.str = new std::string(yytext); return '/'; }
"!"		{ yylval.str = new std::string(yytext); return '!'; }

"=="	{ yylval.cond = 1; return EQ;}
"!="	{ yylval.cond = 2; return NEQ;}
">"		{ yylval.cond = 3; return GT;}
"<"		{ yylval.cond = 4; return LT;}
">="	{ yylval.cond = 5; return GET;}
"<="	{ yylval.cond = 6; return LET;}
"&&"	{ yylval.cond = 7; return AND;}
"||"	{ yylval.cond = 8; return OR;}

";"		{ yylval.str = new std::string(yytext); return ';';}
","		{ yylval.str = new std::string(yytext); return ',';}
"["		{ yylval.str = new std::string(yytext); return '[';}
"]"		{ yylval.str = new std::string(yytext); return ']';}
"{"		{ yylval.str = new std::string(yytext); return '{';}
"}"		{ yylval.str = new std::string(yytext); return '}';}
"("		{ yylval.str = new std::string(yytext); return '(';}
")"		{ yylval.str = new std::string(yytext); return ')';}

"//"[^\n]* { printf("[COMMENT]: %s\n",yytext);}

[ \t]*		{ }
[\n]		{ yylineno++;}
.		{ std::cerr << "SCANNER "; yyerror(); exit(1); }






