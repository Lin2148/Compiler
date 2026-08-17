/* C declarations */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "tree.h"
#include "codegen.h"
int yylex(void);
void yyerror(const char *msg);
extern int yylineno;
int t_flag = 0;



/* forward declare*/
struct tree_node* build_emptylist();
struct tree_node* build_decllist(struct tree_node* list, struct tree_node* var);
struct tree_node* build_id(char* name);
struct tree_node* build_const(int val);
struct tree_node* build_minus(struct tree_node* e);
struct tree_node* build_add(struct tree_node* l, struct tree_node* r);
struct tree_node* build_sub(struct tree_node* l, struct tree_node* r);
struct tree_node* build_mul(struct tree_node* l, struct tree_node* r);
struct tree_node* build_div(struct tree_node* l, struct tree_node* r);
struct tree_node* build_mod(struct tree_node* l, struct tree_node* r);
struct tree_node* build_eq(struct tree_node* l, struct tree_node* r);
struct tree_node* build_ne(struct tree_node* l, struct tree_node* r);
struct tree_node* build_gt(struct tree_node* l, struct tree_node* r);
struct tree_node* build_ge(struct tree_node* l, struct tree_node* r);
struct tree_node* build_lt(struct tree_node* l, struct tree_node* r);
struct tree_node* build_le(struct tree_node* l, struct tree_node* r);
struct tree_node* build_and(struct tree_node* l, struct tree_node* r);
struct tree_node* build_or(struct tree_node* l, struct tree_node* r);
struct tree_node* build_not(struct tree_node* b);
struct tree_node* build_stmtlist(struct tree_node* list, struct tree_node* stmt);
struct tree_node* build_assign(char* id, struct tree_node* expr);
struct tree_node* build_ifthen(struct tree_node* bexpr, struct tree_node* stmt);
struct tree_node* build_ifthenelse(struct tree_node* bexpr, struct tree_node* tstmt, struct tree_node* estmt);
struct tree_node* build_while(struct tree_node* bexpr, struct tree_node* stmt);
struct tree_node* build_read(char* id);
struct tree_node* build_write(struct tree_node* expr);
struct tree_node* build_exit();
struct tree_node* build_program(struct tree_node* decl, struct tree_node* stmt);
void print_tree(struct tree_node* n);
void yyerror(const char *msg);
%}




/* Bison declarations */
/* 開始nonterm*/
%start program
%union {
    int intval;
    char *id;
    struct tree_node* node;
    }

%token PROGRAM BEGIN_TOK END VAR SET IF THEN ELSE ENDIF 
%token WHILE DO ENDWHILE READ WRITE EXIT OR AND NOT 
%token <intval>CONST <id>ID
 

%token LT GT GE EQ NE LE
%token ADD SUB 
%token MINUS  /* 在這邊沒用到，但是呼叫build_minus會把node->type設成MINUS此處宣告才有巨集  */
%token MUL DIV MOD
%token ASSIGN LPAREN RPAREN

/* 綁訂到treenode屬性 */
%type <node> program declarations statements statement
%type <node> boolExpr boolTerm boolFactor relExpr
%type <node> arithExpr arithTerm arithFactor primExpr

/*  Grammer 左邊non-terminal 右邊production rule (ter(flex得到的)+ non-t) */
%%   
program: PROGRAM BEGIN_TOK declarations statements END {
        $$ = build_program($3, $4);
        
        if(t_flag) print_tree($$);
    }
    ;

declarations: declarations VAR ID {
        $$ = build_decllist($1, build_id($3));
    }
    | /* empty */ {
        $$ = build_emptylist();
    }
    ;

statements:
    statements statement {
        $$ = build_stmtlist($1, $2);
    }
    | /* empty */ {
        $$ = build_emptylist();
    }
    ;

statement:
    SET ID ASSIGN arithExpr {
        $$ = build_assign($2,$4);

    }
    | IF boolExpr THEN statements ENDIF {
        $$ = build_ifthen($2, $4);

    }
    | IF boolExpr THEN statements ELSE statements ENDIF {
        $$ = build_ifthenelse($2, $4, $6);

    }
    | WHILE boolExpr DO statements ENDWHILE {
        $$ = build_while($2, $4);
    }
    | READ ID {
        $$ = build_read($2);
    }
    | WRITE arithFactor {
        $$ = build_write($2);
    }
    | EXIT {
        $$ = build_exit();
    }
    ;

boolExpr:
    boolExpr OR boolTerm {
        $$ = build_or($1, $3);
    }
    | boolTerm {
        $$ = $1;
    }
    ;

boolTerm:
    boolTerm AND boolFactor {
        $$ = build_and($1, $3);
    }
    | boolFactor {
        $$ = $1;
    }
    ;

boolFactor:
    NOT boolFactor {
        $$ = build_not($2); 
    }
    | relExpr {
        $$ = $1;
    }
    ;

relExpr:
    arithExpr EQ arithExpr {
        $$ = build_eq($1, $3);
    }
    | arithExpr NE arithExpr {
        $$ = build_ne($1, $3);
    }
    | arithExpr LT arithExpr {
        $$ = build_lt($1, $3);
    }
    | arithExpr LE arithExpr {
        $$ = build_le($1, $3);
    }
    | arithExpr GT arithExpr {
        $$ = build_gt($1, $3);
    }
    | arithExpr GE arithExpr {
        $$ = build_ge($1, $3);
    }
    ;

arithExpr:
    arithExpr ADD  arithTerm {
        $$ = build_add($1, $3);
    }
    | arithExpr SUB  arithTerm {
        $$ = build_sub($1, $3);
    }
    | arithTerm {
        $$ = $1;
    }
    ;

arithTerm:
    arithTerm MUL arithFactor {
        $$ = build_mul($1, $3); 
    }
    | arithTerm DIV arithFactor {
        $$ = build_div($1, $3); 
    }
    | arithTerm MOD arithFactor {
        $$ = build_mod($1, $3); 
    }
    | arithFactor {
        $$ = $1;
    }
    ;

arithFactor:
    SUB arithFactor  {
        $$ = build_minus($2);
    }
    | primExpr {
        $$ = $1;
    }
    ;

primExpr:
    CONST {
        $$ = build_const($1);  
    }
    | ID {
        $$ = build_id($1);
    }
    | LPAREN arithExpr RPAREN {
        $$ = $2;
    }
    ;
%%

/*  Additional C code */
void yyerror(const char *msg) {
    fprintf(stderr, "Syntax error: line %d\n", yylineno);
}


int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-t") == 0) {
        t_flag = 1;
    }

    return yyparse();
}