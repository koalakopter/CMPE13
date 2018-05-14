// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdio.h>

// User libraries
#include "Leds.h"
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
#define LEFT 0
#define RIGHT 1

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
    printf("Welcome to the Lab 6 Part 1 bounce_switch. I didn't feel like removing this");

    LEDS_INIT()
    LEDS_SET(0xCC);
    int i;
    for (i = 0; i < 10000000; i++);
    LEDS_SET(0xDD);
    for (i = 0; i < 10000000; i++);
    LEDS_SET(0);
    for (i = 0; i < 10000000; i++);
    LEDS_SET(0xFF);

    //test coderino
    //set everything to initial states
    /*int direction = LEFT;
    timerData.value = 0;
    timerData.event = 0;
    while (1) {
        if (timerData.event == 1) {
            if ((LATE == 0x1) && (direction == RIGHT)) {
                direction = LEFT;
            } else if ((LATE == 0x80) && (direction == LEFT)) {
                direction = RIGHT;
            } else if (direction == LEFT) {
                LEDS_SET(LATE << 1);
                timerData.event = 0;
            } else if (direction == RIGHT) {
                LEDS_SET(LATE >> 1);
                timerData.event = 0;
            }
        }
    }
     */
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. During each call it increments a counter (the
 * value member of a module-level TimerResult struct). This counter is then checked against the
 * binary values of the four switches on the I/O Shield (where SW1 has a value of 1, SW2 has a value
 * of 2, etc.). If the current counter is greater than this switch value, then the event member of a
 * module-level TimerResult struct is set to true and the value member is cleared.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag
    timerData.value++;
    if (timerData.value > SWITCH_STATES()) {
        timerData.event = 1;
        timerData.value = 0;
    }
    INTClearFlag(INT_T1);
}