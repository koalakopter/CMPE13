// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries


// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
#define BOOLEAN int
#define TRUE 1
#define FALSE 0

// **** Define global, module-level, or external variables here ****


//shameless copy from part1 for use with Timer1Handler

struct TimerResult {
    int event;
    uint8_t value;
};
struct TimerResult timerData;

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
    LEDS_INIT();
    ButtonsInit();
    //used to keep track if switch is up or down
    BOOLEAN up1;
    BOOLEAN up2;
    BOOLEAN up3;
    BOOLEAN up4;

    //loop foreverrr
    while (TRUE) {
        //check if switches are up or down
        if (SWITCH_STATE_SW1) {
            up1 = TRUE;
        }
        if (SWITCH_STATE_SW1) {
            up2 = TRUE;
        }
        if (SWITCH_STATE_SW1) {
            up3 = TRUE;
        }
        if (SWITCH_STATE_SW1) {
            up4 = TRUE;
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
    timerData.value = ButtonsCheckEvents();
    timerData.event = 1;
    // Clear the interrupt flag.
    INTClearFlag(INT_T1);


}