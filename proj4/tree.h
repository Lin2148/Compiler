#ifndef TREE_H
#define TREE_H
#define NIL 300
#define DLIST 301
#define SLIST 302
#define IFTHEN 303
#define IFTHENELSE 304

struct tree_node
{
    int type;
    char* name;
    int val;
    struct tree_node* left;
    struct tree_node* right;
    struct tree_node* unary;
};
#endif