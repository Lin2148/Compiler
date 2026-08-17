%{
// Copy this part into copile C code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // for strcmp
int line_number = 1;
int s_flag = 0;
%}

%option noyywrap

%%
"//".*                      { /* Ignore */ } // Category 6 comments 
[ \t\r]+    { /* Ignore whitespace */ }
\n           { line_number++; } // Count new lines
"And"        { if (s_flag) printf("Keyword: And\n"); }  // Category 2  18 keywords
"Begin"      { if (s_flag) printf("Keyword: Begin\n"); }
"Do"         { if (s_flag) printf("Keyword: Do\n"); }
"Else"       { if (s_flag) printf("Keyword: Else\n"); }
"End"        { if (s_flag) printf("Keyword: End\n"); }
"EndIf"      { if (s_flag) printf("Keyword: EndIf\n"); }
"EndWhile"   { if (s_flag) printf("Keyword: EndWhile\n"); }
"Exit"       { if (s_flag) printf("Keyword: Exit\n"); }
"If"         { if (s_flag) printf("Keyword: If\n"); }
"Set"        { if (s_flag) printf("Keyword: Set\n"); }
"Not"        { if (s_flag) printf("Keyword: Not\n"); }
"Or"         { if (s_flag) printf("Keyword: Or\n"); }
"Program"    { if (s_flag) printf("Keyword: Program\n"); }
"Read"       { if (s_flag) printf("Keyword: Read\n"); }
"Then"       { if (s_flag) printf("Keyword: Then\n"); }
"Var"        { if (s_flag) printf("Keyword: Var\n"); }
"While"      { if (s_flag) printf("Keyword: While\n"); }
"Write"      { if (s_flag) printf("Keyword: Write\n"); }

[_a-zA-Z][_a-zA-Z0-9]*      { if (s_flag) printf("Identifier: %s\n", yytext);} // Category 1 all Identifiers

[0-9]+                      { if (s_flag) printf("Integer Constant: %s\n", yytext); } // Category 3 Integer Constant


"+"                         { if (s_flag) printf("Operator: +\n"); } // Category 4 Operator
"*"                         { if (s_flag) printf("Operator: *\n"); }
"-"                         { if (s_flag) printf("Operator: -\n"); }
"/"                         { if (s_flag) printf("Operator: /\n"); }
"%"                         { if (s_flag) printf("Operator: %%\n"); }
"="                         { if (s_flag) printf("Operator: =\n"); }
"=="                        { if (s_flag) printf("Operator: ==\n"); }
"<>"                        { if (s_flag) printf("Operator: <>\n"); }
">"                         { if (s_flag) printf("Operator: >\n"); }
">="                        { if (s_flag) printf("Operator: >=\n"); }
"<"                         { if (s_flag) printf("Operator: <\n"); }
"<="                        { if (s_flag) printf("Operator: <=\n"); }
"("                         { if (s_flag) printf("Operator: (\n"); }
")"                         { if (s_flag) printf("Operator: )\n"); }

.    { fprintf(stderr, "Lexical error: line %d: unknown character %c\n", line_number, yytext[0]); } // Category 7 other

%%



int main(int argc, char *argv[]) {
    // Check if the "-s" option is provided
    if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        s_flag = 1;
    }

    yylex();
    return 0;
}


