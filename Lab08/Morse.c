//implementation of Morse.h functions
#include "Morse.h"
#include "BOARD.h"
#include <stdio.h>

//array for the morse characters, each line is  a tree with 4 levels, E and T are the 5th level
char morseChars[] = {NULL, 'E', 
                    'I', 'S', 'H', '5', '4', 'V', NULL, '3', 'U', 'F', NULL, NULL, NULL, NULL, '2',
                    'A', 'R', 'L', NULL, NULL, NULL, NULL, NULL, 'W', 'P', NULL, NULL, 'J', NULL, '1',
                    'T', 
                    'N', 'D', 'B', '6', NULL, 'X', NULL, NULL, 'K', 'C', NULL, NULL, 'Y', NULL, NULL,
                    'M', 'G', 'Z', '7', NULL, 'Q', NULL, NULL, 'O', NULL, '8', NULL, NULL, '9', '0'};


int MorseInit(void)
{
    
}