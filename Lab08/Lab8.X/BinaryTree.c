//BinaryTree.C
#include "BinaryTree.h"
#include "Board.h"
#include <stdio.h>


//create a tree
int x; //keeps track of the array element

Node *TreeCreate(int level, const char *data) {
    //first, allocate space
    Node *new = malloc(sizeof (Node));
    //if the malloc fails, return null
    if (new == NULL) {
        return NULL;
    }        //else, store the variable
    else {
        new->data = data[x];
    }
    x++; //move up the array;
    //if not level 1, create a left and right child
    if(level > 1)
    {
        level--;
        new->leftChild = TreeCreate(level, data);
        new->rightChild = TreeCreate(level, data);
        level++;
    }
    //if at the top level, no left or right child
    else if(level == 1)
    {
        new->leftChild = NULL;
        new->rightChild = NULL;
    }
    return new;
}

//prints out a tree

void PrintTree(Node *node, int space) {

}