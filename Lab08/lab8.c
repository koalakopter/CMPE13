// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "Ascii.h"
#include "BOARD.h"
#include "Morse.h"
#include "BinaryTree.h"
#include "Buttons.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <string.h>

// User libraries


// **** Set any macros or preprocessor directives here ****
// Specify a bit mask for setting/clearing the pin corresponding to BTN4. Should only be used when
// unit testing the Morse event checker.
#define BUTTON4_STATE_FLAG (1 << 7)


// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
static int morseEvent; //keeps track of the current morseEvent via the 100hz timer

char output1[20]; //output for line1
char output2[21]; //output for line2 (+1 for newline)
char finalOutput[40];
//its 20 since thats the max amount of chars on the OLED per line

char toWrite; //character pending to be written to OLED
int arrayPos1, arrayPos2; //keeps track of where you are in the string array


// **** Declare any function prototypes here ****


void OledClearTopLine(void); //clears the top line
void OledPutTopLine(char input); //adds character to the top line
void OledPutBotLine(char input); //adds character to the bottom line
void Print(void);

int invalid; //checks for invalid dash/dot combos

//first character is a new line to make a new line... kinda jank

int main()
{
    BOARD_Init();



    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    OledInit(); //start the OLED
    ButtonsInit();
    MorseInit();

    //adds a newline to the beginning of the second line of output
    output2[0] = '\n';
    arrayPos2 = 1; //ArRaYS StARt aT ONe
    
    //everything happens here!
    printf("\nHEAVEN OR HELL\n");
    while (TRUE) {
        //does stuff according to what MorseCheckEvents returns
        switch (morseEvent) {

            //the "do nothing case"
        case MORSE_EVENT_NONE:
            //yeah just do nothing 
            //printf("hi domo");
            break;

            //if a dot is received, print that dot
        case MORSE_EVENT_DOT:
            //adds a dot!
            printf("meme");
            OledPutTopLine(MORSE_CHAR_DOT);
            morseEvent = MORSE_EVENT_NONE; //go back to default state
            invalid = MorseDecode(MORSE_CHAR_DOT);

            //makes a hash(tag) if the character is not a real valid point in the binary tree
            if (invalid == STANDARD_ERROR) {
                MorseDecode(MORSE_CHAR_DECODE_RESET);
                OledPutBotLine(MORSE_CHAR_END_OF_CHAR);
            }
            break;

        case MORSE_EVENT_DASH:
            //adds a dot!
            printf("yeah");
            OledPutTopLine(MORSE_CHAR_DASH);
            morseEvent = MORSE_EVENT_NONE; //go back to default state

            //makes a hash(tag) if the character is not a real valid point in the binary tree
            if (invalid == STANDARD_ERROR) {
                MorseDecode(MORSE_CHAR_DECODE_RESET);
                OledPutBotLine(MORSE_CHAR_END_OF_CHAR);
            }
            break;
            //designate a new word
        case MORSE_EVENT_INTER_WORD:
            morseEvent = MORSE_EVENT_NONE; //go back to default state
            
            //clear the top line
            OledClearTopLine();
            
            OledPutBotLine(MORSE_CHAR_END_OF_CHAR);
            MorseDecode(MORSE_CHAR_END_OF_CHAR);
            break;

            //same character, not a new letter    
        case MORSE_EVENT_INTER_LETTER:
            morseEvent = MORSE_EVENT_NONE; //go back to default state
            
            //clear the top line
            OledClearTopLine();
            
            OledPutBotLine(MORSE_CHAR_END_OF_CHAR);
            MorseDecode(MORSE_CHAR_END_OF_CHAR);
            break;
        }
    }



    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     *****************************************************************************/

    while (1);
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //******** Put your code here *************//
    //calls to MorseCheckEvents
    morseEvent = MorseCheckEvents();
}

void OledClearTopLine(void)
{
    //char blankSpace[20]; //20 spaces...
    sprintf(output1, "                    ");
    OledDrawString(output1);
    OledUpdate();
    arrayPos1 = 0;
}

//adds a character to top line

void OledPutTopLine(char input)
{
    //if you put in a dot...
    if (input == MORSE_CHAR_DOT) {
        toWrite = MORSE_CHAR_DOT;
    }//...a dash
    else if (input == MORSE_CHAR_DASH) {
        toWrite = MORSE_CHAR_DASH;
    }//or a space
    else {
        toWrite = MORSE_CHAR_END_OF_CHAR;
    }

    output1[arrayPos1] = toWrite; //puts the char returned by PutTop into the output array
    arrayPos1 += 1;
    Print();
}

//does the same thing as the above function, but puts it in the bottom line instead

void OledPutBotLine(char input)
{

    //if you put in a dot...
    if (input == MORSE_CHAR_DOT) {
        toWrite = MORSE_CHAR_DOT;
    }//...a dash
    else if (input == MORSE_CHAR_DASH) {
        toWrite = MORSE_CHAR_DASH;
    }//or a space
    else {
        toWrite = MORSE_CHAR_END_OF_CHAR;
    }

    output2[arrayPos2] = toWrite; //puts the char returned by PutTop into the output array
    arrayPos2 += 1;
    Print();
}


//helper print function

void Print(void)
{
    OledClear(0); //clear the display first
    OledSetDisplayNormal();


    strcpy(finalOutput, output1); //combine lines 1 and 2 into a single string
    strcat(finalOutput, output2);

    OledDrawString(finalOutput);
    OledUpdate();
}