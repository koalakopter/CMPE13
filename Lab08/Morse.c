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
int MorseInit(void)
{
    //initialize buttons
    ButtonsInit();
    //create new Morse tree based upon above array
    Node *tree = TreeCreate(treeSize, morseChars);
    if(tree != NULL)
    {
        return SUCCESS;
    }
    else {
        return STANDARD_ERROR;
    }
}