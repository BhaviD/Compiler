%{
    #include <iostream>
    #include <string>
    #include "AST.h"
    #include "parser.tab.h"
    using namespace std;
    extern int yylex();

    #define SAVE_STRING yylval.sval = new string(yytext, yyleng)
    int line_num = 1;
%}
%option noyywrap
%%
[ \t]                      { ; }
[\n]                       { ++line_num; }
;                          { return DELIMITER; }
[(){}\[\]\#,]              { return yytext[0]; }
include                    { SAVE_STRING; return INCLUDE; }
if                         { SAVE_STRING; return IF; }
else                       { SAVE_STRING; return ELSE; }
for                        { SAVE_STRING; return FOR; }
while                      { SAVE_STRING; return WHILE; }
void                       { SAVE_STRING; return VOID; }
int                        { SAVE_STRING; return INT; }
char                       { SAVE_STRING; return CHAR; }
unsigned\ long\ long       { SAVE_STRING; return LLU; }
long\ long                 { SAVE_STRING; return LL; }
unsigned                   { SAVE_STRING; return UNSIGNED; }
long                       { SAVE_STRING; return LONG; }
bool                       { SAVE_STRING; return BOOL; }
return                     { SAVE_STRING; return RETURN; }
string                     { SAVE_STRING; return STRING; }
print                      { SAVE_STRING; return PRINT; }
println                    { SAVE_STRING; return PRINTLN; }
input                      { SAVE_STRING; return INPUT; }
main                       { SAVE_STRING; return IDENTIFIER; }
define                     { SAVE_STRING; return DEFINE; }
break                      { SAVE_STRING; return BREAK; }
continue                   { SAVE_STRING; return CONTINUE; }
true                       { yylval.bval = true; return BOOL_LIT; }
false                      { yylval.bval = false; return BOOL_LIT; }

&&                         { return REFERENCE_OPR; }

and      |
or       |
!                          { SAVE_STRING; return LOGICAL_OPR; }

\<       |
>        |
==       |
\<=      |
>=       |
!=                         { SAVE_STRING; return RELATIONAL_OPR; }

\+       |
-        |
\*       |
\/       |
\%                         { SAVE_STRING; return ARITHMETIC_OPR; }

\<\<     |
>>       |
&        |
\|       |                 { SAVE_STRING; return BITWISE_OPR; }

=        | 
\+=      | 
-=       | 
\*=      | 
\/=      | 
\%=      | 
&=       | 
\|=      | 
\<\<=    | 
>>=                        { SAVE_STRING; return ASSIGNMENT_OPR; }

\"([^\\\|"]|\\.)*\"        { SAVE_STRING; return STRING_LIT; }
\'([^\\\|']|\\.)?\'        { yylval.cval = yytext[0]; return CHAR_LIT; }
[0-9]+\.[0-9]+             { yylval.fval = atof(yytext); return FLOAT_LIT;}
[0-9]+                     { yylval.ival = atoi(yytext); return INT_LIT;}
[_]*[a-zA-Z][_a-zA-Z0-9]*  { SAVE_STRING; return IDENTIFIER; }
.                          { SAVE_STRING; return NO_MATCH; }

