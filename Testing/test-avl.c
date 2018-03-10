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
    insertAVL(t, newINTEGER(7));
    statisticsAVL(t, stdout);
    displayAVL(t, stdout);
    freeAVL(t);
    return 0;
}
