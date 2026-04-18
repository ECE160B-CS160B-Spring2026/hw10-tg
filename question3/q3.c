#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_LEN(x) sizeof((x)) / sizeof((x[0]))

// K&R Pg. 144-145

struct nlist {              // table entry:
    struct nlist *next;     // next entry in chain
    int val; 
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table

// hash: form hash value for string
unsigned hash(int a)
{
    return a % HASHSIZE; 
}

// lookup:look for s in hashtab
struct nlist *lookup(int a)
{
    struct nlist *np;

    // loop through linked list
    for (np = hashtab[hash(a)]; np != NULL; np = np->next)
        if (np->val == a)
            return np; 
    return NULL;       // not found
}


// install:put (name, defn) in hashtab
struct nlist *install(int val)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(val)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL)
            return NULL;
        np->val = val;
        hashval = hash(val);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    

    return np;
}

void intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2) {
    int output_index = 0;
    for (int i = 0; i < lenArr1; i++) {
       install(array1[i]); 
    }
    for (int i = 0; i < lenArr2; i++) {
        if (lookup(array2[i]) != NULL) {
            output[output_index++] = array2[i]; 
        }
    }
}

int main()
{
    int array1[] = {10, 13, 15, 1, 4, 9, 8, 6, 7, 2, 19}; 
    int array2[] = {14, 15, 1, 4, 9, 2, 5, 19};
    int output[5];

    intersection(output, array1, ARRAY_LEN(array1), array2, ARRAY_LEN(array2));
    for (int i = 0; i < 5; i++) 
        printf("%d\n", output[i]); 

    // Example of using a hash table
    return 0;
}
