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

int intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2) {
    int output_index = 0;
    for (int i = 0; i < lenArr1; i++) {
       install(array1[i]); 
    }
    for (int i = 0; i < lenArr2; i++) {
        if (lookup(array2[i]) != NULL) {
            output[output_index++] = array2[i]; 
        }
    }
    return output_index;
}

int min(int a, int b) {
    return (a < b) ? a : b;  
}

int main()
{
    int array1[100]; 
    int array2[100];
    int output[100];
    int array1Len;
    int array2Len; 

    printf("arr1 pts: "); 
    scanf("%d", &array1Len);
    array2len = array1len;
    for (int i = 0; i < min(array1Len, 100); i++) {
        scanf("%d", array1 + i); 
    }
    for (int i = 0; i < min(array2Len, 100); i++) {
        scanf("%d", array2 + i); 
    }
    

    int outputsize = intersection(output, array1, array1Len, array2, array2Len);
    for (int i = 0; i < outputsize; i++) {
        printf("%d ", output[i]); 
    }
    printf("\n");

    // Example of using a hash table
    return 0;
}
