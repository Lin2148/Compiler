#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cactus.tab.h"
#include "tree.h"
#include "codegen.h"

//fd
static int allo_reg();
static void free_reg();
static void gen_decl(struct tree_node* n);
static void gen_stmt_list(struct tree_node* n);
static void gen_stmt(struct tree_node* n);
static int gen_expr(struct tree_node* n);
static void gen_bool(struct tree_node* n, int label_t, int label_f);
static int gen_label();

// reg operation
int reg_cnt = 0;
int result_reg, addr_reg;
int label = 0;

static int allo_reg(){
    if (reg_cnt > 9){
        fprintf(stderr,"out of reg, free first");
        return -1;
    }
    return reg_cnt++;
}

static void free_reg(){
    if(reg_cnt > 0){
        reg_cnt--;
    }
}

static int gen_label(){
    label++;
    return label;
}

void gen_mips(struct tree_node* root) {
    // 基本不會
    if (root == NULL || root->type != PROGRAM) return;

    // .data部分
    printf("\t%s\n",".data");
    //build_program把left 存成tree_node* decl
    gen_decl(root->left);

    //.text
    // 寫死main讓SPIM知道執行MIPS語言
    printf("\t.text\nmain:\n");
    //build_program把left 存成tree_node* stmt
    gen_stmt_list(root->right);

}

static void gen_decl(struct tree_node* n) {
    if (n == NULL || n->type == NIL) return;
    // 下面還有decl 繼續走
    if(n->type == DLIST){
        gen_decl(n->left);

        if (n->right->type == ID){
            printf("%s:\t.word 0\t\n", n->right->name);
        }
    }
}

static void gen_stmt_list(struct tree_node* n) {
    if (n == NULL || n->type == NIL) return;
    //下面還有stmt
    if (n->type == SLIST){
        gen_stmt_list(n->left);
        gen_stmt(n->right);
    } else {   
        fprintf(stderr, "Error: Expected SLIST node, but got type %d\n", n->type);
        exit(-1);
    }
}

static void gen_stmt(struct tree_node* n) {
    if (n == NULL || n->type == NIL) return;

    switch(n->type){
        case ASSIGN:
        {
            result_reg = gen_expr(n->unary);
            addr_reg = allo_reg();  // 拿一個reg存
            printf("\tla $t%d, %s\n", addr_reg, n->name);    
            printf("\tsw $t%d, 0($t%d)\n", result_reg, addr_reg); 
            free_reg();
            free_reg();
        break;
        }
        case IFTHEN:
        {
            int label_t = gen_label();
            int label_f = gen_label();
            // 0跳到end_label
            gen_bool(n->unary, label_t, label_f);

            //then
            printf("L%d:\n", label_t);
            gen_stmt_list(n->left);

            //jump then
            printf("L%d:\n", label_f);
        break;
        }
        case IFTHENELSE:
        {
            int label_t = gen_label();
            int label_f = gen_label();
            int end_l  = gen_label();
            gen_bool(n->unary, label_t, label_f);
            printf("L%d:\n", label_t);
            gen_stmt_list(n->left);
            printf("\tb L%d\n", end_l);


            printf("L%d:\n", label_f);
            gen_stmt_list(n->right);
            printf("L%d:\n", end_l);
        break;
        }
        case WHILE:
        {
            int label_start = gen_label(); 
            int label_t = gen_label();     
            int label_f = gen_label();    
            
            printf("L%d:\n", label_start);
            gen_bool(n->unary, label_t, label_f);
            printf("L%d:\n", label_t);
            gen_stmt_list(n->left);
            
            // jump back while start
            printf("\tb L%d\n", label_start);
            // out while
            printf("L%d:\n", label_f);
        break;
        }
        case READ:
        {
            addr_reg = allo_reg();
            // 5 for read
            printf("\tli $v0, 5\n");
            printf("\tsyscall\n");
            printf("\tla $t%d, %s\n",addr_reg, n->name);
            printf("\tsw $v0, 0($t%d)\n",addr_reg);
            free_reg();
        break;
        }
        case WRITE:
        {
            addr_reg = gen_expr(n->unary);
            printf("\tmove $a0, $t%d\n", addr_reg );
            // 1 for write
            printf("\tli $v0, 1\n");
            printf("\tsyscall\n");
            free_reg();
        break;
        }
        case EXIT:
        {
            // 10 for exit
            printf("\tli $v0, 10\n");
            printf("\tsyscall\n");
        break;
        }
        default:
        {
            fprintf(stderr,"wrong stmt ");  
        break;
        }
    }
}


static void gen_bool(struct tree_node* n, int label_t, int label_f) {
    if (n == NULL || n->type == NIL) return;

    switch (n->type) {
        case AND: 
        {
            int label_mid = gen_label(); // 產生中間的標籤
            // 左邊成立m 檢查右邊 否則f,  右邊成立t 否則f
            gen_bool(n->left, label_mid, label_f); 
            printf("L%d:\n", label_mid);
            gen_bool(n->right, label_t, label_f);
        break;
        }
        case OR: 
        {
            int label_mid = gen_label();
            gen_bool(n->left, label_t, label_mid);
            printf("L%d:\n", label_mid);
            gen_bool(n->right, label_t, label_f);
        break;
        }
        case NOT:
        {
            gen_bool(n->unary, label_f, label_t);
        break;
        }
        case EQ:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tbeq $t%d, $t%d, L%d\n", left_reg, right_reg, label_t);
            printf("\tb L%d\n", label_f);
            free_reg();
            free_reg();
        break;
        }
        case NE:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tbne $t%d, $t%d, L%d\n", left_reg, right_reg, label_t);
            printf("\tb L%d\n", label_f);
            free_reg();
            free_reg();
        break;
        }
        case LT:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tblt $t%d, $t%d, L%d\n", left_reg, right_reg, label_t);
            printf("\tb L%d\n", label_f);
            free_reg();
            free_reg();
        break;
        }
        case LE:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tble $t%d, $t%d, L%d\n", left_reg, right_reg, label_t);
            printf("\tb L%d\n", label_f);
            free_reg();
            free_reg();
        break;
        }
        case GT:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tbgt $t%d, $t%d, L%d\n",  left_reg, right_reg, label_t);
            printf("\tb L%d\n", label_f);
            free_reg();
            free_reg();
        break;
        }
        case GE:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tbge $t%d, $t%d, L%d\n", left_reg, right_reg, label_t);
            printf("\tb L%d\n", label_f);
            free_reg();
            free_reg();
        break;
        }
        default:
        {
            fprintf(stderr, "err bool\n");
            exit(1);
        }
    }
}

// 計算放入reg 回傳reg num   $1 = $2 op $3
static int gen_expr(struct tree_node* n){
    if (n == NULL || n->type == NIL) return -1;

    switch(n->type){
        case CONST:
        {
            result_reg = allo_reg();
            printf("\tli $t%d, %d\n", result_reg, n->val);
            return result_reg;
        break;
        }
        case ID:
        {
            result_reg = allo_reg();
            printf("\tla $t%d, %s\n", result_reg, n->name); 
            printf("\tlw $t%d, 0($t%d)\n", result_reg, result_reg); 
            return result_reg;
        break;
        }
        case ADD:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tadd $t%d, $t%d, $t%d\n", left_reg, left_reg, right_reg);
            free_reg();
            return left_reg;
        break;
        }
        case SUB:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tsub $t%d, $t%d, $t%d\n", left_reg, left_reg, right_reg);
            free_reg();
            return left_reg;
        break;
        }
        case MUL:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tmul $t%d, $t%d, $t%d\n", left_reg, left_reg, right_reg);
            free_reg();
            return left_reg;
        break;
        }
        case MOD:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\trem $t%d, $t%d, $t%d\n", left_reg, left_reg, right_reg);
            free_reg();
            return left_reg;
        break;
        }
        case DIV:
        {
            int left_reg = gen_expr(n->left);
            int right_reg = gen_expr(n->right);
            printf("\tdiv $t%d, $t%d, $t%d\n", left_reg, left_reg, right_reg);
            free_reg();
            return left_reg;
        break;
        }
        case MINUS:
        {
            int unary_reg = gen_expr(n->unary);
            printf("\tneg $t%d, $t%d\n", unary_reg, unary_reg);
            return unary_reg;
        break;
        }
        default:
        {
            fprintf(stderr,"wrong expr ");
            return -1;
        break;
        }
    }
}