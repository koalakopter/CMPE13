//implementation of Morse.h functions
#include "Morse.h"
#include "BinaryTree.h"
#include "BOARD.h"
#include "Buttons.h"
#include "Oled.h"
#include <stdio.h>

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

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

int state;
//enum of all possible states

enum {
    WAITING = 0, DASH, DOT, INTER_LETTER
};

BOOLEAN isCreate;
int MorseInit(void)
{
    //initialize buttons and OLED
    ButtonsInit();
    OledInit();
    //create new Morse tree based upon above array
    Node *tree = TreeCreate(treeSize, morseChars);
    temp = tree; //will be used for decoding
    //print tree just for good measure
    //PrintTree(tree, treeSize);
    //set Case to waiting
    state = WAITING;

    isCreate = TRUE; //boolean to determine if Morse has been initialized
    if (tree != NULL) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

char MorseDecode(MorseChar in)
{
    //if not initialized, return NULL
    if (isCreate == NULL) {
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


uint8_t buttonEvent;
int timer; //100 hz timer
int currentEvent;
MorseEvent MorseCheckEvents(void)
{
    currentEvent = MORSE_EVENT_NONE;
    buttonEvent = ButtonsCheckEvents();
    
    //if morse init hasnt been called, return an error
    if(isCreate == FALSE)
    {
        return STANDARD_ERROR;
    }

    switch (state) {
    //case 1, waiting for input
    case WAITING:
        //if button4 is pressed, reset and start the 100hz timer
        if (buttonEvent & BUTTON_EVENT_4DOWN)
        {
            //go to next case (DOT))
            state = DOT;
            timer = 0;
        }
        //if nothing happens, return nothing
        break;
    //checks for DOT Press, or when the press is less than 0.5 sec but greater than 0.25 seconds
    //note at 100hz, 25 triggers for 0.25 seconds
    case DOT:
        //register a button being released
        if (buttonEvent & BUTTON_EVENT_4UP)
        {
            //check the time 
            if (timer >= MORSE_EVENT_LENGTH_DOWN_DOT && 
                     timer < MORSE_EVENT_LENGTH_DOWN_DASH)
            {
                //returns a dot
                state = INTER_LETTER;
                timer = 0; //reset the timer
                currentEvent = MORSE_EVENT_DOT;
            }
            else if(timer >= MORSE_EVENT_LENGTH_DOWN_DASH)
            {
                state = DASH;
                break;
            }
        }
    case DASH:
        
        timer = 0;
        state = INTER_LETTER;
        currentEvent = MORSE_EVENT_DASH; //returns a dash
        break;
        
    case INTER_LETTER:
        
        //if the value of timer is too big (>200), designate a new word
        if (timer >= MORSE_EVENT_LENGTH_UP_INTER_LETTER_TIMEOUT)
        {
            state = WAITING;
            currentEvent = MORSE_EVENT_INTER_WORD;
            break;
        }
        //check if button4 was pressed
        if (buttonEvent & BUTTON_EVENT_4DOWN)
        {
            //if timer times out past 100 ticks, designate a new letter
            if(timer >= MORSE_EVENT_LENGTH_UP_INTER_LETTER)
            {
                state = WAITING;
                currentEvent =  MORSE_EVENT_INTER_LETTER;
                break;
            }
            //if the interval was too short, its the same letter
            else if(timer < MORSE_EVENT_LENGTH_UP_INTER_LETTER)
            {
                state = DOT;
                timer = 0; //reset the timer and go back to dot
            }
        }
        break;
    }
    timer++; //increment dat timer
    return currentEvent; //returns the current Morse Event...
}