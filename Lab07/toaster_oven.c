// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "Adc.h"
#include "BOARD.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdio.h>
#include <string.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
//drawing the oven
#define TOP_OVEN_ON 0x01
#define TOP_OVEN_OFF 0x02
#define BOT_OVEN_ON 0x03
#define BOT_OVEN_OFF 0x04

void print(void);

//arbitrary value for strings to print onto OLED
#define ARBITRARY_VALUE 30

#define TRUE 1
#define FALSE 0 


//struct that keeps track of everything about the oven

struct Oven {
    //keeps track of oven states: (a = bake, b = broil, c = toast)
    char ovenState;
    char cookingMode;

    int buttonPress;
    int input;

    //for time stuff
    float remTime;
    float initTime;
    //keeps track of temperature
    int temp;
};

struct Oven data;

// Configuration Bit settings

int main()
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. We configure it using a 1:256 prescalar, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR1 to F_PB / 256 / 2 yields a 0.5s timer.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, BOARD_GetPBClock() / 256 / 2);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescalar, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, BOARD_GetPBClock() / 256 / 5);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T3);
    INTSetVectorPriority(INT_TIMER_3_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_3_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T3, INT_ENABLED);

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Starting the toasty funtimes\n");
    LEDS_INIT();
    OledInit();
    ButtonsInit();
    AdcInit();

    //default mode is bake
    data.ovenState = 'a';
    uint8_t buttonEvents;

    while (1) {
        //everything will happen in here

        //get the current temperature with potentiometer
        if (AdcChanged() != FALSE) {

            data.temp = AdcRead();
            data.temp += 300;
        }
        print();

        //cycles between states of the oven by checking buttons
        buttonEvents = ButtonsCheckEvents();
        if (buttonEvents) {
            //checks if Button3 was pressed for less than 1 second
            if (buttonEvents & BUTTON_EVENT_3DOWN) {
                if (data.ovenState == 'a') {
                    data.ovenState = 'b';
                } else if (data.ovenState == 'b') {
                    data.ovenState = 'c';
                } else {
                    data.ovenState = 'a';
                }
            }
        }


    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
    while (1);
}

//print function in charge of printing the stuff to display
static char lineOne[ARBITRARY_VALUE];
static char lineTwo[ARBITRARY_VALUE];
static char lineThree[ARBITRARY_VALUE];
static char lineFour[ARBITRARY_VALUE];

static char displayOutput[150];

static int min;
static int sec;

void print(void)
{
    switch (data.ovenState) {

        //bake mode
    case('a'):
        sprintf(lineOne, "|%c%c%c%c%c|  MODE: Bake\n", TOP_OVEN_OFF, TOP_OVEN_OFF, TOP_OVEN_OFF,
                TOP_OVEN_OFF, TOP_OVEN_OFF);
        sprintf(lineTwo, "|     |  TIME: %d:%02d \n", min, sec);
        sprintf(lineThree, "|-----|  TEMP: %d°F\n", data.temp);
        sprintf(lineFour, "|%c%c%c%c%c|\n", BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF,
                BOT_OVEN_OFF);

        //print statements
        //but first, copy the strings into one big string!
        strcpy(displayOutput, lineOne);
        strcat(displayOutput, lineTwo);
        strcat(displayOutput, lineThree);
        strcat(displayOutput, lineFour);

        OledDrawString(displayOutput);
        OledUpdate();
        break;

        //broil mode    
    case('b'):
        sprintf(lineOne, "|%c%c%c%c%c|  MODE: Bake\n", TOP_OVEN_OFF, TOP_OVEN_OFF, TOP_OVEN_OFF,
                TOP_OVEN_OFF, TOP_OVEN_OFF);
        sprintf(lineTwo, "|     |  TIME: %d:%02d \n", min, sec);
        sprintf(lineThree, "|-----|  TEMP: 500°F\n");
        sprintf(lineFour, "|%c%c%c%c%c|\n", BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF,
                BOT_OVEN_OFF);

        //print statements
        //but first, copy the strings into one big string!
        strcpy(displayOutput, lineOne);
        strcat(displayOutput, lineTwo);
        strcat(displayOutput, lineThree);
        strcat(displayOutput, lineFour);

        OledDrawString(displayOutput);
        OledUpdate();
        break;

        //toast mode
    case('c'):
        sprintf(lineOne, "|%c%c%c%c%c|  MODE: Bake\n", TOP_OVEN_OFF, TOP_OVEN_OFF, TOP_OVEN_OFF,
                TOP_OVEN_OFF, TOP_OVEN_OFF);
        sprintf(lineTwo, "|     |  TIME: %d:%02d \n", min, sec);
        sprintf(lineThree, "|-----|\n");
        sprintf(lineFour, "|%c%c%c%c%c|\n", BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF,
                BOT_OVEN_OFF);

        //print statements
        //but first, copy the strings into one big string!
        strcpy(displayOutput, lineOne);
        strcat(displayOutput, lineTwo);
        strcat(displayOutput, lineThree);
        strcat(displayOutput, lineFour);

        OledDrawString(displayOutput);
        OledUpdate();
        break;

    }
}

void __ISR(_TIMER_1_VECTOR, ipl4auto) TimerInterrupt2Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 4;

}

void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

}

void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

}