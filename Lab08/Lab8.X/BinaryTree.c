//BinaryTree.C
#include "BinaryTree.h"
#include "Board.h"
#include <stdio.h>
#include <math.h>


//create a tree
Node *TreeCreate(int level, const char *data)
{
    Node *new; //create a temporary node to put stuff into
    double power; //variable to perform the POW function
    //allocate space for this temp thing
    new = malloc(sizeof (Node));
    if (new == NULL)
    {
        return NULL;
    }
    //if at the bottom level, no left or right child
    if (level == 1) {       
        //set right and left child to NULL, since at bottom
        new->rightChild = NULL;
        new->leftChild = NULL;
        //put in data pointer
        new->data = *data;
        return new;
    }
    //if not level 1 (the bottom), create a left and right child
    else if (new != NULL) {
        //put the data from temp into a pointer
        new->data = *data;
        
        new->leftChild = TreeCreate(level - 1, data + 1); 
        
        //performs the operation 2^n, to find the data point to print into temp
        power = pow(2, level-1);
        new->rightChild = TreeCreate( level - 1, data + (int)power); 
        return new;
    }
    return NULL;
}

//go down the left side of the tree starting from the root that is passed in

Node *GetLeftChild(Node *root)
{
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

Node *GetRightChild(Node *root)
{
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

void PrintTree(Node *node, int space)
{
    //return NULL if root is NULL
    if (node == NULL) {
        return;
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
