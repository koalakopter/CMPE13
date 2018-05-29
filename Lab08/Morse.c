//implementation of Morse.h functions
#include "Morse.h"
#include "BinaryTree.h"
#include "BOARD.h"
#include "Buttons.h"
#include <stdio.h>

//array for the morse characters, each line is  a tree with 4 levels, E and T are the 5th level
char morseChars[] = {NULL, 'E',
    'I', 'S', 'H', '5', '4', 'V', NULL, '3', 'U', 'F', NULL, NULL, NULL, NULL, '2',
    'A', 'R', 'L', NULL, NULL, NULL, NULL, NULL, 'W', 'P', NULL, NULL, 'J', NULL, '1',
    'T',
    'N', 'D', 'B', '6', NULL, 'X', NULL, NULL, 'K', 'C', NULL, NULL, 'Y', NULL, NULL,
    'M', 'G', 'Z', '7', NULL, 'Q', NULL, NULL, 'O', NULL, NULL, '8', NULL, '9', '0'};

int treeSize = 6;
Node *tree;
Node *temp;

int MorseInit(void)
{
    //initialize buttons
    ButtonsInit();
    //create new Morse tree based upon above array
    Node *tree = TreeCreate(treeSize, morseChars);
    temp = tree; //will be used for decoding
    if (tree != NULL) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

char MorseDecode(MorseChar in)
{
    //if not initialized, return NULL
    if (tree == NULL) {
        return STANDARD_ERROR;
    }
    if (in == MORSE_CHAR_DASH) {
        //move to the right of the tree if dash
        tree = tree->rightChild;
        return SUCCESS;
    } else if (in == MORSE_CHAR_DOT) {
        //move left if dot
        tree = tree->leftChild;
        return SUCCESS;
    } else if (in == MORSE_CHAR_END_OF_CHAR) {
        return tree->data; // return data if end of input
    } else if (in == MORSE_CHAR_DECODE_RESET) {
        tree = temp; // set tree back to head of tree to read next char
        return SUCCESS;
    }
    return in;
}

MorseEvent MorseCheckEvents(void)
{
    return 1;
}