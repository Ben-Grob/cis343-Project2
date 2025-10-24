/* zoomjoystrong.l — Lexical analyzer for calculator */

%{
#include "zoomjoystrong.tab.h"   /* Contains token definitions from Bison */
#include <stdio.h>
#include <stdlib.h>
%}

/* Regular expressions */
DIGIT   [0-9]
NUMBER  {DIGIT}+(\.{DIGIT}+)?

/* keywords are case insensitive */
%option noyywrap
%option caseless

/* Identify Tokens */
%%
"end"             { return END; }
;               { return END_STATEMENT; }
\.               { return END_STATEMENT; }
"point"           { return POINT; }
"line"            { return LINE; }
"circle"          { return CIRCLE; }
"rectangle"       { return RECTANGLE; }
"set_color"       { return SET_COLOR; };
$.              { yylval.var = yytext[1]; return VARIABLE; }
"="             { return EQUALS; }
"\+"            { return PLUS; }
"-"             { return MINUS; }
"\*"            { return MULT; }
"/"             { return DIV; }
[ \t]+          ;      /* ignore spaces */
[ \n]+          ;      /* ignore new lines */

[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+          { yylval.fval = (float)atoi(yytext); return INT; }

\$[a-zA-Z]      { yylval.var = yytext[1]; return VARIABLE; }
.               { printf("Unknown character: %s\n", yytext); }



%%

/*** User code section (not sure what to add here)***/
/* int yywrap(void) { return 1; } */
