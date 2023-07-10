#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "morse_base.h"

MTree *root;

void make_tree(){
    root = calloc(1, sizeof(*root));
    //root->value = '/';//anything
    int i;
    for(i = 0; i < 26; ++i)
        insert('A'+i, table[ALPHA][i]);
    for(i = 0; i < 10; ++i)
        insert('0'+i, table[NUM][i]);
}
void delete_tree_aux(MTree *root){
    if(root){
        delete_tree_aux(root->dot);
        delete_tree_aux(root->bar);
        free(root);
    }
}
void delete_tree(){
    delete_tree_aux(root);
}

void insert_aux(MTree **tree, char ch, const char *s){
    if(*tree == NULL)
        *tree = calloc(1, sizeof(**tree));
    if(*s == '\0')
        (*tree)->value = ch;
    else if(*s == '.')
        insert_aux(&(*tree)->dot, ch, ++s);
    else if(*s == '-')
        insert_aux(&(*tree)->bar, ch, ++s);
}

void insert(char ch, const char *s){
    if(*s == '.')
        insert_aux(&root->dot, ch, ++s);
    else if(*s == '-')
        insert_aux(&root->bar, ch, ++s);
}