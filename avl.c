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
    int count;
    int balance;
    int leftHeight;
    int rightHeight;
    int height;
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
    assert(rv != 0);
    rv->value = v;
    rv->count = 0;
    rv->balance = 0;
    rv->leftHeight = 0;
    rv->rightHeight = 0;
    rv->height = 1;
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

int getAVALcount(AVAL *av) {
    assert(av != 0);
    return av->count;
}

void incrementAVALcount(AVAL *av) {
    assert(av != 0);
    av->count++;
}

void decrementAVALcount(AVAL *av) {
    assert(av != 0);
    av->count--;
}

int getAVALbalance(AVAL *av) {
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
    int count = getAVALcount((AVAL *)v);
    if (count > 1) fprintf(fp, "[%d]", count);
}

int compareAVAL(void *v, void *w) {
    return (((AVAL *)v)->compare(getAVALvalue(v), getAVALvalue(w)));
}

void freeAVAL(void *v) {
    ((AVAL *)v)->free(getAVALvalue(v));
    free(v);
}


/********** Private AVL method prototypes **********/
void insertionFixup(AVL *, BSTNODE *);
int isRoot(AVL *, BSTNODE *);
void swapper(BSTNODE *, BSTNODE *);


struct AVL {
    BST *store;
    int size;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
    void (*insertionFixup)(AVL *, BSTNODE *);
    int (*isRoot)(AVL *, BSTNODE *);
};

AVL *newAVL(
        void (*d)(void *, FILE *),
        int (*c)(void *, void *),
        void (*f)(void *)) {
    AVL *rv = malloc(sizeof(AVL));
    assert(rv != 0);
    rv->store = newBST(adisplay, compareAVAL, swapper, freeAVAL);
    rv->size = 0;
    rv->display = d;
    rv->compare = c;
    rv->free = f;
    rv->insertionFixup = insertionFixup;
    rv->isRoot = isRoot;
    return rv;
}

void insertAVL(AVL *t, void *v) {
    assert(t != 0);
    AVAL *temp = newAVAL(v, t->display, t->compare, t->free);
    BSTNODE *n = findBST(t->store, temp);
    if (n == NULL) {
        // Tree does not contain value
        insertBST(t->store, temp);
        incrementAVALcount(temp);
    }
    else {
        // Tree already contains the value
        incrementAVALcount(getBSTNODEvalue(n));
        freeAVAL(temp);
    }
    t->size++;
}

int findAVLcount(AVL *t, void *v) {
    assert(t != 0);
    AVAL *temp = newAVAL(v, t->display, t->compare, t->free);
    BSTNODE *n = findBST(t->store, temp);
    freeAVAL(temp);
    return n == NULL ? 0 : getAVALcount(getBSTNODEvalue(n));
}

void *findAVL(AVL *t, void *v) {
    assert(t != 0);
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


/*************************** Private methods ***************************/

void insertionFixup(AVL *t, BSTNODE *n) {
    while (1) {
        if (t->isRoot(t, n)) break;
    }
}

int isRoot(AVL *t, BSTNODE *n) {
    assert(t != 0);
    return n == getBSTroot(t->store) ? 1 : 0;
}

void swapper(BSTNODE *a, BSTNODE *b) {
    AVAL *ta = getBSTNODEvalue(a);
    AVAL *tb = getBSTNODEvalue(b);
    void *vtemp = ta->value;
    ta->value = tb->value;
    tb->value = vtemp;
    int ctemp = ta->count;
    ta->count = tb->count;
    tb->count = ctemp;
}

int height(BSTNODE *n) {
    if (n == NULL) return 0;
    int leftHeight = height(getBSTNODEleft(n));
    int rightHeight = height(getBSTNODEright(n));
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

BSTNODE *sibling(BSTNODE *n) {
    assert(n != 0);
    BSTNODE *parent = getBSTNODEparent(n);
    if (parent == NULL) return NULL;
    else if (getBSTNODEleft(parent) == n) return getBSTNODEright(parent);
    else return getBSTNODEleft(parent);
}
