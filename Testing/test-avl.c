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
    freeAVL(t);
    return 0;
}
