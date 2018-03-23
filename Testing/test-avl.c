/*
 *  File:   test-avl.c
 *  Author: Brett Heithold
 *  Description:
 */


#include "../avl.h"
#include "../integer.h"
#include <stdio.h>


int main(void) {
    AVL *t = newAVL(displayINTEGER, compareINTEGER, freeINTEGER);
    insertAVL(t, newINTEGER(7));
    insertAVL(t, newINTEGER(4));
    insertAVL(t, newINTEGER(3));
    insertAVL(t, newINTEGER(2));
    insertAVL(t, newINTEGER(6));
    insertAVL(t, newINTEGER(8));
    insertAVL(t, newINTEGER(1));
    INTEGER *r = newINTEGER(7);
    r = deleteAVL(t, r);
    freeINTEGER(r);
    statisticsAVL(t, stdout);
    displayAVL(t, stdout);
    freeAVL(t);
    return 0;
}
