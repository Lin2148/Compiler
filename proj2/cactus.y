/* C declarations */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
//#include "tree.h"
int yylex(void);
void yyerror(const char *msg);
extern int yylineno;
int p_flag = 0;
%}



/* Bison declarations */
%start program
%union {
    int intval;
    char *id;
    }

%token Program Begin End Var Set If Then Else EndIf 
%token While Do EndWhile Read Write Exit Or And Not 
%token IntConst Identifier
 

%token LT GT GE EQ NE LE
%token PLUS MINUS
%token MULT DIV MOD
%token ASSIGN LPAREN RPAREN

/*  Grammer */
%%   
program: Program Begin declarations statements End {
        if(p_flag) printf("program -> Program Begin declarations statements End\n");
    }
    ;

declarations: declarations Var Identifier {
        if(p_flag) printf("declarations -> declarations Var Identifier\n");
    }
    | /* empty */ {
        if(p_flag) printf("declarations -> <empty>\n");
    }
    ;

statements:
    statements statement {
        if(p_flag) printf("statements -> statements statement\n");
    }
    | /* empty */ {
        if(p_flag) printf("statements -> <empty>\n");
    }
    ;

statement:
    Set Identifier ASSIGN arithExpr {
        if(p_flag) printf("statement -> Set Identifier = arithExpr\n");
    }
    | If boolExpr Then statements EndIf {
        if(p_flag) printf("statement -> If boolExpr Then statements EndIf\n");
    }
    | If boolExpr Then statements Else statements EndIf {
        if(p_flag) printf("statement -> If boolExpr Then statements Else statements EndIf\n");
    }
    | While boolExpr Do statements EndWhile {
        if(p_flag) printf("statement -> While boolExpr Do statements EndWhile\n");
    }
    | Read Identifier {
        if(p_flag) printf("statement -> Read Identifier\n");
    }
    | Write arithExpr {
        if(p_flag) printf("statement -> Write arithExpr\n");
    }
    | Exit {
        if(p_flag) printf("statement -> Exit\n");
    }
    ;

boolExpr:
    boolExpr Or boolTerm {
        if(p_flag) printf("boolExpr -> boolExpr Or boolTerm\n");
    }
    | boolTerm {
        if(p_flag) printf("boolExpr -> boolTerm\n");
    }
    ;

boolTerm:
    boolTerm And boolFactor {
        if(p_flag) printf("boolTerm -> boolTerm And boolFactor\n");
    }
    | boolFactor {
       if(p_flag)  printf("boolTerm -> boolFactor\n");
    }
    ;

boolFactor:
    Not boolFactor {
        if(p_flag) printf("boolFactor -> Not boolFactor\n");
    }
    | relExpr {
        if(p_flag) printf("boolFactor -> relExpr\n");
    }
    ;

relExpr:
    arithExpr EQ arithExpr {
        if(p_flag) printf("relExpr -> arithExpr == arithExpr\n");
    }
    | arithExpr NE arithExpr {
        if(p_flag) printf("relExpr -> arithExpr <> arithExpr\n");
    }
    | arithExpr LT arithExpr {
        if(p_flag) printf("relExpr -> arithExpr < arithExpr\n");
    }
    | arithExpr LE arithExpr {
        if(p_flag) printf("relExpr -> arithExpr <= arithExpr\n");
    }
    | arithExpr GT arithExpr {
        if(p_flag) printf("relExpr -> arithExpr > arithExpr\n");
    }
    | arithExpr GE arithExpr {
        if(p_flag) printf("relExpr -> arithExpr >= arithExpr\n");
    }
    ;

arithExpr:
    arithExpr PLUS  arithTerm {
        if(p_flag) printf("arithExpr -> arithExpr + arithTerm\n");
    }
    | arithExpr MINUS  arithTerm {
        if(p_flag) printf("arithExpr -> arithExpr - arithTerm\n");
    }
    | arithTerm {
        if(p_flag) printf("arithExpr -> arithTerm\n");
    }
    ;

arithTerm:
    arithTerm MULT arithFactor {
        if(p_flag) printf("arithTerm -> arithTerm * arithFactor\n");
    }
    | arithTerm DIV arithFactor {
        if(p_flag) printf("arithTerm -> arithTerm / arithFactor\n");
    }
    | arithTerm MOD arithFactor {
        if(p_flag) printf("arithTerm -> arithTerm %% arithFactor\n");
    }
    | arithFactor {
        if(p_flag) printf("arithTerm -> arithFactor\n");
    }
    ;

arithFactor:
    MINUS arithFactor  {
        if(p_flag) printf("arithFactor -> - arithFactor\n");
    }
    | primExpr {
        if(p_flag) printf("arithFactor -> primExpr\n");
    }
    ;

primExpr:
    IntConst {
        if(p_flag) printf("primExpr -> IntConst\n");
    }
    | Identifier {
        if(p_flag) printf("primExpr -> Identifier\n");
    }
    | LPAREN arithExpr RPAREN {
        if(p_flag) printf("primExpr -> ( arithExpr )\n");
    }
    ;
%%

/*  Additional C code */
void yyerror(const char *msg) {
    fprintf(stderr, "Syntax error: line %d\n", yylineno);
}


int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-p") == 0) {
        p_flag = 1;
    }

    return yyparse();
}