%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
LETTER [A-Z]|[a-z]

%%

"forward"|"fw"        { return KW_FORWARD; }
"backward"|"bw"       { return KW_BACKWARD; }
"position"|"pos"      { return KW_POSITION; }
"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"print"               { return KW_PRINT; }
"right"|"rt"          { return KW_RIGHT; }
"left"|"lt"           { return KW_LEFT; }
"heading"|"hd"        { return KW_HEADING; }
"color"               { return KW_COLOR; }

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
{LETTER}*             { yylval.value = strtod(yytext, NULL); return NAME; }

[\n\t\r ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
