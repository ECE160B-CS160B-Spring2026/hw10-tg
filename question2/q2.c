#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 1000
#define MAXWORD 1000

char buf[BUFSIZE];
int bufp = 0;

typedef struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
} tnode;

// ----------- function prototypes -------------
int getword(char *word, int lim);
int getch(void);
void ungetch(int c);
tnode* addNode(tnode *node, char *string);
tnode *talloc();
void printTree(tnode *node);
void treeToArray(tnode *node, int *index, tnode *array[]);
void sortThatArray(tnode *array[], int n);
void printThatArray(tnode *array[], int index);
// ---------------------------------------------

int main() {
    char word[MAXWORD];
    tnode *root = NULL;
    tnode *array[MAXWORD];
    int index = 0;

    while(getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addNode(root, word);
        }
    }

    treeToArray(root, &index, array);

    sortThatArray(array, index);
    printThatArray(array, index);
}

void printThatArray(tnode *array[], int index) {
    for(int i = 0; i < index; i++) {
        printf("%s, %d\n", array[i]->word, array[i]->count);
    }
}


// bubble sort yay
void sortThatArray(tnode *array[], int n) {
    tnode *temp;

    for (int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(array[j]->count < array[j + 1]->count) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}



tnode* talloc() {
    return (tnode*)(malloc(sizeof(tnode)));
}

tnode* addNode(tnode *node, char *string) {
    int condition;
    
    if (node == NULL) {
        node = talloc();
        node->word = strdup(string);
        node->count = 1;
        node->left = node->right = NULL;
    } else if ( (condition = strcmp(node->word, string)) == 0 ) {
        node->count++;
    } else if (condition < 0) {
        node->left = addNode(node->left, string);
    } else if (condition > 0) {
        node->right = addNode(node->right, string);
    }

    return node;
}

void printTree(tnode *node) {
    if (node != NULL) {
        printTree(node->left);
        printf("%d, %s\n", node->count, node->word);
        printTree(node->right);
    }
}

void treeToArray(tnode *node, int *index, tnode *array[]) {
    if (node == NULL || *index > MAXWORD) {
        return;
    }

    treeToArray(node->left, index, array);
    array[*index] = node;
    (*index)++;
    treeToArray(node->right, index, array);
}



// ------------------------------------------------
// getword:get next word or character from input
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) {
        ;
    }

    if (c != EOF) {
        *w++ = c;
    }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

int getch(void) { // get a (possibly pushed back) character
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { // push character back on input
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many caracters\n");
    } else {
        buf[bufp++] = c;
    }
}
