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
    rv->count = 1;
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

void setAVALbalance(AVAL *av, int lh, int rh) {
    assert(av != 0);
    av->leftHeight = lh;
    av->rightHeight = rh;
    av->height = lh > rh ? lh + 1: rh + 1;
    av->balance = lh - rh;
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
void rotateTo(AVL *, BSTNODE *, BSTNODE *);
int isRoot(AVL *, BSTNODE *);
void swapper(BSTNODE *, BSTNODE *);
int height(BSTNODE *);
BSTNODE *sibling(BSTNODE *);
BSTNODE *favoriteChild(BSTNODE *);
int linear(BSTNODE *c, BSTNODE *p, BSTNODE *gp);


struct AVL {
    BST *store;
    int size;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*free)(void *);
    void (*insertionFixup)(AVL *, BSTNODE *);
    void (*rotateTo)(AVL *, BSTNODE *, BSTNODE *);
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
    rv->rotateTo = rotateTo;
    rv->isRoot = isRoot;
    return rv;
}

void insertAVL(AVL *t, void *v) {
    assert(t != 0);
    AVAL *temp = newAVAL(v, t->display, t->compare, t->free);
    BSTNODE *n = findBST(t->store, temp);
    if (n == NULL) {
        // Tree does not contain value
        n = insertBST(t->store, temp);
        t->insertionFixup(t, n);
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

void *deleteAVL(AVL *t, void *v) {
    AVAL *temp = newAVAL(v, t->display, t->compare, t->free);
    BSTNODE *n = findBST(t->store, temp);
    void *rv = NULL;
    if (n == NULL) {
        // Value not found in tree
        printf("Value ");
        t->display(v, stdout);
        printf(" not found.\n");
    }
    else {
        if (getAVALcount(getBSTNODEvalue(n)) > 1) {
            decrementAVALcount(getBSTNODEvalue(n));
            rv = getBSTNODEvalue(n);
        }
        else {
            // TODO
        }
    }
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

void statisticsAVL(AVL *t, FILE *fp) {
    fprintf(fp, "Duplicates: %d\n", duplicatesAVL(t));
    statisticsBST(t->store, fp);
}

void displayAVL(AVL *t, FILE *fp) {
    assert(t != 0);
    if (t->size > 0) {
        displayBSTdecorated(t->store, fp);
    }
    else {
        fprintf(fp, "EMPTY\n");
    }
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
    while (!t->isRoot(t, n)) {
        if (sibling(n) && sibling(n) == favoriteChild(getBSTNODEparent(n))) {
            // Parent favors sibling
            BSTNODE *p = getBSTNODEparent(n);
            int lh = height(getBSTNODEleft(p));
            int rh = height(getBSTNODEright(p));
            setAVALbalance(getBSTNODEvalue(getBSTNODEparent(n)), lh, rh);
            break;
        }
        else if (favoriteChild(getBSTNODEparent(n)) == NULL) {
            // Parent is balanced
            BSTNODE *p = getBSTNODEparent(n);
            int lh = height(getBSTNODEleft(p));
            int rh = height(getBSTNODEright(p));
            setAVALbalance(getBSTNODEvalue(getBSTNODEparent(n)), lh, rh);
            n = p;
        }
        else {
            BSTNODE *y = favoriteChild(n);
            BSTNODE *p = getBSTNODEparent(n);
            if (y && !linear(y, n, p)) {
                t->rotateTo(t, y, n);
                t->rotateTo(t, y, p);
                // set balance of n
                int lh = height(getBSTNODEleft(n));
                int rh = height(getBSTNODEright(n));
                setAVALbalance(getBSTNODEvalue(n), lh, rh);
                // set balance of p
                lh = height(getBSTNODEleft(p));
                rh = height(getBSTNODEright(p));
                setAVALbalance(getBSTNODEvalue(p), lh, rh);
                // set balance of y
                lh = height(getBSTNODEleft(y));
                rh = height(getBSTNODEright(y));
                setAVALbalance(getBSTNODEvalue(y), lh, rh);
            }
            else {
                t->rotateTo(t, n, p);
                // set balance of p
                int lh = height(getBSTNODEleft(p));
                int rh = height(getBSTNODEright(p));
                setAVALbalance(getBSTNODEvalue(p), lh, rh);
                // set balance of n
                lh = height(getBSTNODEleft(n));
                rh = height(getBSTNODEright(n));
                setAVALbalance(getBSTNODEvalue(n), lh, rh);
            }
            break;
        }
    }
}

void rotateTo(AVL *t, BSTNODE *c, BSTNODE *p) {
    if (c == getBSTNODEleft(p)) {
        // c is left child of p, p becomes right child of c
        setBSTNODEparent(c, getBSTNODEparent(p));
        setBSTNODEright(c, p);
        setBSTNODEleft(p, 0);
        if (getBSTNODEparent(p) != NULL) {
            setBSTNODEleft(getBSTNODEparent(p), c);
        }
        setBSTNODEparent(p, c);
    }
    else {
        // c is right child of p, p becomes left child of c
        setBSTNODEparent(c, getBSTNODEparent(p));
        setBSTNODEleft(c, p);
        setBSTNODEright(p, 0);
        if (getBSTNODEparent(p) != NULL) {
            setBSTNODEright(getBSTNODEparent(p), c);
        }
        setBSTNODEparent(p, c);
    }
    if (t->isRoot(t, p)) setBSTroot(t->store, c);
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

BSTNODE *sibling(BSTNODE *c) {
    assert(c != 0);
    BSTNODE *parent = getBSTNODEparent(c);
    if (parent == NULL) return NULL;
    else if (getBSTNODEleft(parent) == c) return getBSTNODEright(parent);
    else return getBSTNODEleft(parent);
}

BSTNODE *favoriteChild(BSTNODE *p) {
    assert(p != 0);
    if (getAVALbalance(getBSTNODEvalue(p)) == 1) {
        // Left child is favorite
        return getBSTNODEleft(p);
    }
    else if (getAVALbalance(getBSTNODEvalue(p)) == -1) {
        // Right child is favorite
        return getBSTNODEright(p);
    }
    // Balance == 0, neither child is favored
    return NULL;
}

int linear(BSTNODE *c, BSTNODE *p, BSTNODE *gp) {
    int leftLinear = getBSTNODEleft(gp) == p && getBSTNODEleft(p) == c;
    int rightLinear = getBSTNODEright(gp) == p && getBSTNODEright(p) == c;
    return leftLinear || rightLinear;
}
