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
    INTEGER *r = newINTEGER(7);
    freeINTEGER(deleteAVL(t, r));
    statisticsAVL(t, stdout);
    displayAVL(t, stdout);
    freeAVL(t);
    return 0;
}
