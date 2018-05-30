// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "BOARD.h"
#include "Morse.h"
#include "BinaryTree.h"
#include "Buttons.h"
#include "Oled.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <string.h>

// User libraries


// **** Set any macros or preprocessor directives here ****
// Specify a bit mask for setting/clearing the pin corresponding to BTN4. Should only be used when
// unit testing the Morse event checker.
#define BUTTON4_STATE_FLAG (1 << 7)
#define BOOLEAN int

#define TRUE 1
#define FALSE 0

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
static int morseEvent; //keeps track of the current morseEvent via the 100hz timer

char output1[20]; //output for line1
char output2[20]; //output for line2
char finalOutput[40];
//its 20 since thats the max amount of chars on the OLED per line

char toWrite; //character pending to be written to OLED


// **** Declare any function prototypes here ****


void OledClearTopLine(void); //clears the top line
void OledPutTopLine(char input); //adds character to the top line
void OledPutBottomLine(char input); //adds character to the bottom line

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
    //printf("\nWelcome to Lab8, Julian's Morse Marathon!\n");

    OledInit(); //start the OLED


    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     *****************************************************************************/

    while (1);
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) TimerInterrupt100Hz(void)
{
    //calls to MorseCheckEvents
    morseEvent = MorseCheckEvents();
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //******** Put your code here *************//

}
BOOLEAN firstChar; //checks if the first character has been written or not...

void OledClearTopLine(void)
{
    char blankSpace[16] = "";
    OledDrawString(blankSpace);
    OledUpdate();
    firstChar = FALSE;
}

void OledPutTopLine(char input)
{
    //if you put in a dot...
    if (input == MORSE_CHAR_DOT) {
        toWrite = MORSE_CHAR_DOT;
    }       
    //...a dash
    else if (input == MORSE_CHAR_DASH) {
        toWrite = MORSE_CHAR_DASH;
    }        
    //or a space
    else {
        toWrite = MORSE_CHAR_END_OF_CHAR;
    }
}


//print function!

void Print(void)
{
    OledClear(0);
    //checks if this is the first character being printed because strcpy & strcat are funky
    if (firstChar == FALSE) {
        strcpy(output1, toWrite);
    } else {
        strcat(output1, toWrite);
    }
    
    strcpy(finalOutput, output1);
    strcat(finalOutput, output2);
    OledDrawString(finalOutput);
    OledUpdate();


}