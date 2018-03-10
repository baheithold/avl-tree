/*
 *  File:   avl.c
 *  Author: Brett Heithold
 *  Decription:
 */


#include "avl.h"
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct aval {
    void *value;
    int frequency;
    int balance;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
} AVAL;

AVAL *newAVAL(
        void *v,
        void (*d)(void *, FILE *),
        int (*c)(void *, void *),
        void (*f)(void *)) {
    AVAL *rv = malloc(sizeof(AVAL));
    rv->value = v;
    rv->frequency = 0;
    rv->balance = 0;
    rv->display = d;
    rv->compare = c;
    rv->free = f;
    return rv;
}

void *getAVALvalue(AVAL *av) {
    assert(av != 0);
    return av->value;
}

void setAVALvalue(AVAL *av, void *v) {
    av->value = v;
}

int frequencyAVAL(AVAL *av) {
    assert(av != 0);
    return av->frequency;
}

void incrementFrequencyAVAL(AVAL *av) {
    assert(av != 0);
    av->frequency++;
}

void decrementFrequencyAVAL(AVAL *av) {
    assert(av != 0);
    av->frequency--;
}

int balanceAVAL(AVAL *av) {
    assert(av != 0);
    return av->balance;
}

void setAVALbalance(AVAL *av, int b) {
    assert(av != 0);
    av->balance = b;
}


struct AVL {
    BST *store;
    int size;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
};

AVL *newAVL(
        void (*d)(void *, FILE *),
        int (*c)(void *, void *),
        void (*f)(void *)) {
    AVL *rv = malloc(sizeof(AVL));
    rv->store = newBST(d, c, 0, f);
    rv->size = 0;
    rv->display = d;
    rv->compare = c;
    rv->free = f;
    return rv;
}

int sizeAVL(AVL *t) {
    assert(t != 0);
    return t->size;
}

int duplicatesAVL(AVL *t) {
    assert(t != 0);
    return t->size - sizeBST(t->store);
}
