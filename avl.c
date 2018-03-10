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

void adisplay(void *v, FILE *fp) {
    // TODO: Add balance decoration!
    assert(v != 0);
    ((AVAL *) v)->display(getAVALvalue((AVAL *)v), fp);
    int freq = frequencyAVAL((AVAL *)v);
    if (freq > 1) fprintf(fp, "[%d]", freq);
}

int compareAVAL(void *v, void *w) {
    return (((AVAL *)v)->compare(getAVALvalue(v), getAVALvalue(w)));
}

void freeAVAL(void *v) {
    ((AVAL *)v)->free(getAVALvalue(v));
    free(v);
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
    rv->store = newBST(adisplay, compareAVAL, 0, freeAVAL);
    rv->size = 0;
    rv->display = d;
    rv->compare = c;
    rv->free = f;
    return rv;
}

int findAVLcount(AVL *t, void *v) {
    AVAL *temp = newAVAL(v, t->display, t->compare, t->free);
    BSTNODE *n = findBST(t->store, temp);
    freeAVAL(temp);
    return n == NULL ? 0 : frequencyAVAL(getBSTNODEvalue(n));
}

void *findAVL(AVL *t, void *v) {
    AVAL *temp = newAVAL(v, t->display, t->compare, t->free);
    BSTNODE *n = findBST(t->store, temp);
    freeAVAL(temp);
    return n == NULL ? NULL : v;
}

int sizeAVL(AVL *t) {
    assert(t != 0);
    return t->size;
}

int duplicatesAVL(AVL *t) {
    assert(t != 0);
    return t->size - sizeBST(t->store);
}

void statisticsAVL(AVL *t, FILE *fp) {
    fprintf(fp, "Duplicates: %d\n", duplicatesAVL(t));
    statisticsBST(t->store, fp);
}

void displayAVL(AVL *t, FILE *fp) {
    assert(t != 0);
    displayBSTdecorated(t->store, fp);
}

void displayAVLdebug(AVL *t, FILE *fp) {
    assert(t != 0);
    displayBST(t->store, fp);
}

void freeAVL(AVL *t) {
    assert(t != 0);
    freeBST(t->store);
    free(t);
}
