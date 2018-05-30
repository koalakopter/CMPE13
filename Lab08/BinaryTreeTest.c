// Heap size 2048 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "BinaryTree.h"
#include "Morse.h"
#include "Buttons.h"

// **** Set any macros or preprocessor directives here ****


// **** Define any module-level, global, or external variables here ****


// **** Declare any function prototypes here ****

int main()
{
    BOARD_Init();

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    printf("\nTesting for Lab 8 and Julian's BinaryTree.C function");

    //creating some fun for the whole family
    //data
    char fletcher[] = {'a', 'b', 'd', 'e', 'c', 'f', 'g'};
    printf("\nPRINT TEST 1: SHOULD PRINT THIS TREE BUT ROTATED CCW: \n");
    printf("\n          a");
    printf("\n    b           c");
    printf("\nd       e     f       g");
    int gearing = 3;

    printf("\n\n\n"); //I've got a blank space, baby, and I'll write your name~

    Node *test = TreeCreate(gearing, fletcher); //create a tree
    PrintTree(test, 0);

    printf("\n\n\n"); //I've got a blank space, baby, and I'll write your name~
    
    //testing for getLeft and getRight
    Node *left;
    Node *right;

    left = GetLeftChild(test);
    right = GetRightChild(test);
    
    printf("\nTESTING GetLeftChild and GetRightChild functions\n");
    printf("got left child of first test tree: %c, expected: 'd'\n", left->data);
    printf("got right child of first test tree: %c, expected: 'g'\n", right->data);


    //test morse tree
    char morseChars[] = {NULL, 'E',
        'I', 'S', 'H', '5', '4', 'V', NULL, '3', 'U', 'F', NULL, NULL, NULL, NULL, '2',
        'A', 'R', 'L', NULL, NULL, NULL, NULL, NULL, 'W', 'P', NULL, NULL, 'J', NULL, '1',
        'T',
        'N', 'D', 'B', '6', NULL, 'X', NULL, NULL, 'K', 'C', NULL, NULL, 'Y', NULL, NULL,
        'M', 'G', 'Z', '7', NULL, 'Q', NULL, NULL, 'O', NULL, NULL, '8', NULL, '9', '0'};
    char benson[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', NULL, 'B', 'C', 'D', 'E', 'F'};
    gearing = 4;
    Node *morseTest = TreeCreate(gearing, benson);
    PrintTree(morseTest, 0);
    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/

    while (1);
}

