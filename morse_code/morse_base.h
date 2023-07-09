#ifndef MORSE_BASE
#define MORSE_BASE

static const char *alpha[] = {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z
};
static const char *num[] = {
    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9
};
static const char **table[] = { alpha, num };

typedef enum kind {
    ALPHA, NUM
} Kind;

typedef struct mtree {
    char value;
    struct mtree *dot;
    struct mtree *bar;
} MTree;

void make_tree(MTree *root);
void drop_tree_aux(MTree *root);
void drop_tree(MTree *root);
void insert_aux(MTree **tree, char ch, const char *s);
void insert(MTree *root, char ch, const char *s);


#endif