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
    }//else, store the variable
    else {
        new->data = data[x];
    }
    x++; //move up the array;
    //if not level 1, create a left and right child
    if (level > 1) {
        level--;
        new->leftChild = TreeCreate(level, data);
        new->rightChild = TreeCreate(level, data);
        level++;
    }        //if at the top level, no left or right child
    else if (level == 1) {
        new->leftChild = NULL;
        new->rightChild = NULL;
    }
    return new;
}

//go down the left side of the tree starting from the root that is passed in

Node *GetLeftChild(Node *root) {
    //progress down the tree until there is no more left child
    while (root->leftChild != NULL) {
        root = root->leftChild;
    }
    //check for nulls
    if (root->data == NULL) {
        return NULL;
    }
    return root;
}

//go down the right side of the tree starting from the root that is passed in

Node *GetRightChild(Node *root) {
    //progress down the tree until there is no more right child
    while (root->rightChild != NULL) {
        root = root->rightChild;
    }
    //check for nulls
    if (root->data == NULL) {
        return NULL;
    }
    return root;
}

//prints out a tree
//LEVEL_SPACES = 4
int blank = 0; //extra spaces?

void PrintTree(Node *node, int space) {
    //return NULL if root is NULL
    if (node = NULL) {
        return NULL;
    }
    space += LEVEL_SPACES; //increment space
    //recurse right child
    if (node->rightChild != NULL) {
        PrintTree(node->rightChild, space);
    }
    //print spaces and data
    printf("\n %*s", space, "");
    printf("%c", node->data);
    //recurse left child
    if (node->leftChild != NULL) {
        PrintTree(node->leftChild, space);
    }
    return;


}