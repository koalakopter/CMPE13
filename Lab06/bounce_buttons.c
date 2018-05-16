// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>


// User libraries
#include "Leds.h"
#include "Buttons.h"

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
#define BOOLEAN int
#define TRUE 1
#define FALSE 0

// **** Define global, module-level, or external variables here ****


//shameless copy from part1, for use with Timer1Handler

struct TimerResult {
    int event;
    uint8_t value;
    uint8_t switchCheck;
};
struct TimerResult boardData;

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_8, 0xFFFF);

    // Set up the timer interrupt with a priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    //turn on LED and Buttons

    printf("Julian's button extravaganza! Lab 6 Part 3\n");
    LEDS_INIT();
    ButtonsInit();
    //used to keep track if switch is up or down
    BOOLEAN up1;
    BOOLEAN up2;
    BOOLEAN up3;
    BOOLEAN up4;

    //the output of the LED's
    uint8_t output;
    //current state of LED's
    uint8_t current;

    //loop foreverrr
    while (TRUE) {
        if (boardData.event == TRUE) {
            //check if switches are up or down (UP = TRUE, DOWN = FALSE)
            if (SWITCH_STATE_SW1 & boardData.switchCheck) {
                up1 = TRUE;
            } else {
                up1 = FALSE;
            }
            if (SWITCH_STATE_SW2 & boardData.switchCheck) {
                up2 = TRUE;
            } else {
                up2 = FALSE;
            }
            if (SWITCH_STATE_SW3 & boardData.switchCheck) {
                up3 = TRUE;
            } else {
                up3 = FALSE;
            }
            if (SWITCH_STATE_SW4 & boardData.switchCheck) {
                up4 = TRUE;
            } else {
                up4 = FALSE;
            }

            //get the current status of the LED's
            current = LEDS_GET();


            //compare button down press to the current value of buttonData

            if (BUTTON_EVENT_1UP & boardData.value) {
                //check if switch is down or up
                if (up1 == TRUE) {
                    //light up LED with bitwise XOR
                    output = current ^ 0x03;
                    LEDS_SET(output);
                    puts("meme\n");
                }
            } else if (BUTTON_EVENT_1DOWN & boardData.value) {
                if (up1 == FALSE) {
                    //light up LED with bitwise XOR
                    output = current ^ 0x03;
                    LEDS_SET(output);
                    puts("not memee\n");
                }
            }
            //clears all values so it doesn't run the loop unnecessarily
            boardData.event == 0;
            boardData.value == 0;
        }
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It checks for button events and stores them in a
 * module-level variable.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    //updates the switch and button values
    boardData.value = ButtonsCheckEvents();
    boardData.switchCheck = SWITCH_STATES();

    //checks if something was actually changed
    boardData.event = TRUE;
    // Clear the interrupt flag.
    INTClearFlag(INT_T1);


}