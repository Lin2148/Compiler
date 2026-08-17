#include <stdio.h>
#include <stdlib.h>
#include "cactus.tab.h"
#include "tree.h"

struct tree_node* build_emptylist() {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = NIL;
    return n;
}

struct tree_node* build_decllist(struct tree_node* list, struct tree_node* var) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = DLIST;
    n->left = list;
    n->right = var;
    return n;
}

struct tree_node* build_id(char* name) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = ID;
    n->name = name;
    return n;
}

struct tree_node* build_const(int val) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = CONST;
    n->val = val;
    return n;
}

struct tree_node* build_minus(struct tree_node* e) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = MINUS;
    n->unary = e;
    return n;
}

struct tree_node* build_add(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = ADD;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_sub(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = SUB;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_mul(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = MUL;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_div(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = DIV;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_mod(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = MOD;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_eq(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = EQ;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_ne(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = NE;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_gt(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = GT;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_ge(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = GE;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_lt(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = LT;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_le(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = LE;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_and(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = AND;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_or(struct tree_node* l, struct tree_node* r) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = OR;
    n->left = l;
    n->right = r;
    return n;
}

struct tree_node* build_not(struct tree_node* b) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = NOT;
    n->unary = b;
    return n;
}

struct tree_node* build_stmtlist(struct tree_node* list, struct tree_node* stmt) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = SLIST;
    n->left = list;
    n->right = stmt;
    return n;
}

struct tree_node* build_assign(char* id, struct tree_node* expr) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = ASSIGN;
    n->name = id;
    n->unary = expr;
    return n;
}

struct tree_node* build_ifthen(struct tree_node* bexpr, struct tree_node* stmt) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = IFTHEN;
    n->unary = bexpr;
    n->left = stmt;
    return n;
}

struct tree_node* build_ifthenelse(struct tree_node* bexpr, struct tree_node* tstmt, struct tree_node* estmt) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = IFTHENELSE;
    n->unary = bexpr;
    n->left = tstmt;
    n->right = estmt;
    return n;
}

struct tree_node* build_while(struct tree_node* bexpr, struct tree_node* stmt) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = WHILE;
    n->unary = bexpr;
    n->left = stmt;
    return n;
}

struct tree_node* build_read(char* id) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = READ;
    n->name = id;
    return n;
}

struct tree_node* build_write(struct tree_node* expr) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = WRITE;
    n->unary = expr;
    return n;
}

struct tree_node* build_exit() {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = EXIT;
    return n;
}

struct tree_node* build_program(struct tree_node* decl, struct tree_node* stmt) {
    struct tree_node* n = (struct tree_node*) malloc(sizeof(struct tree_node));
    n->type = PROGRAM;
    n->left = decl;
    n->right = stmt;
    return n;
}

void print_tree(struct tree_node* n) {
    switch(n->type) {
        case CONST: printf("%d", n->val); break;
        case ID: printf("%s", n->name); break;
        case MINUS: printf("(- "); print_tree(n->unary); printf(")"); break;
        case ADD: printf("(+ "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case SUB: printf("(- "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case MUL: printf("(* "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case DIV: printf("(/ "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case MOD: printf("(%% "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case EQ: printf("(== "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case NE: printf("(<> "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case GT: printf("(> "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case GE: printf("(>= "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case LT: printf("(< "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case LE: printf("(<= "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case AND: printf("(&& "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case OR: printf("(|| "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case NOT: printf("(! "); print_tree(n->unary); printf(")"); break;
        case ASSIGN: printf("(= "); printf("%s", n->name); printf(" "); print_tree(n->unary); printf(")"); break;
        case READ: printf("(read "); printf("%s", n->name); printf(")"); break;
        case WRITE: printf("(write "); print_tree(n->unary); printf(")"); break;
        case EXIT: printf("exit"); break;
        case NIL: printf("()"); break;
        case SLIST: printf("("); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        case IFTHEN: printf("(ifthen "); print_tree(n->unary); printf(" "); print_tree(n->left); printf(")"); break;
        case IFTHENELSE: printf("(ifthenelse "); print_tree(n->unary); printf(" "); print_tree(n->left); printf(" "); 
                 print_tree(n->right); printf(")"); break;
        case WHILE: printf("(while "); print_tree(n->unary); printf(" "); print_tree(n->left); printf(")"); break;
        case DLIST: printf("("); print_tree(n->left); printf(" (var "); print_tree(n->right); printf("))"); break;
        case PROGRAM: printf("(program "); print_tree(n->left); printf(" "); print_tree(n->right); printf(")"); break;
        default: fprintf(stderr, "semantic error\n"); break;
    }
}
