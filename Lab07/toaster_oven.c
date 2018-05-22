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
#define BOOLEAN int
#define LONG_PRESS 5

//struct that keeps track of everything about the oven

typedef struct {
    //keeps track of the oven state machine, or the enum of what state the oven is currently in
    int ovenState;
    //keeps track of oven states: (a = bake, b = broil, c = toast)
    char cookingMode;

    //free running buttonPress counter in 5Hz timer
    int buttonPress;
    //keeps track of current time when button is depressed
    int input;

    //for time stuff
    int remTime; //Emilia > Rem btw
    int initTime;
    //keeps track of temperature
    int temp;
} Oven;

Oven data;

enum {
    RESET, START, COUNTDOWN, PENDING_SELECTOR_CHANGE, PENDING_RESET
};
static BOOLEAN selector = FALSE;
static uint8_t buttonEvents;

//keeps track of minutes and seconds
static int min;
static int sec;
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
    data.cookingMode = 'a';
    data.ovenState = RESET;

    //default temp is 300F
    data.temp = 300;
    //data.buttonPress = 0;




    while (1) {
        //everything will happen in here
        switch (data.ovenState) {

        case RESET:
            //get the current temperature with potentiometer if the potentiometer was moved

            data.ovenState = START;
            print();
            break;

        case START:
            //edits the potentiometer
            if (AdcChanged() != FALSE) {
                if (selector == TRUE) {
                    data.temp = AdcRead();
                    data.temp = data.temp >> 2; //shift to the right by two bits so we get the top 8
                    data.temp += 300;
                    print();

                } else if (selector == FALSE) {
                    data.initTime = AdcRead();
                    data.initTime = data.initTime >> 2;

                    //set the seconds and minutes
                    sec = data.initTime % 60;
                    min = data.initTime / 60;
                    print();
                }
            }
            //cycles between states of the oven by checking buttons
            if (buttonEvents != 0) {
                //record the current state/number in the timer
                if (buttonEvents & BUTTON_EVENT_3DOWN) {

                    data.input = data.buttonPress;
                    //change state to change whether to change time/temp or oven cooking mode
                    data.ovenState = PENDING_SELECTOR_CHANGE;
                    //set button state to none
                    buttonEvents = BUTTON_EVENT_NONE;
                }
                //start the countdown if button 4 is pressed
                if (buttonEvents & BUTTON_EVENT_4DOWN)
                {
                    data.ovenState = COUNTDOWN;
                    buttonEvents = BUTTON_EVENT_NONE;
                    break;
                }
            }
            break;

        case PENDING_SELECTOR_CHANGE:
            //can't leave this until a thing happens
            while (TRUE) {
                //checks if Button3 was pressed less than one second, swap cooking mode
                if (((data.buttonPress - data.input) < LONG_PRESS) && (buttonEvents & BUTTON_EVENT_3UP)) {
                    //change from bake to broil
                    if (data.cookingMode == 'a') {
                        data.cookingMode = 'b';
                        //broil to toast
                    } else if (data.cookingMode == 'b') {
                        data.cookingMode = 'c';
                        //force potentiometer to edit time
                        selector = FALSE;
                        //toast back to bake
                    } else {
                        data.cookingMode = 'a';
                    }
                    //leave the while loop
                    break;
                }//if pressed greater than 1 sec
                else if (((data.buttonPress - data.input) >= LONG_PRESS)) {
                    if (selector == TRUE) {
                        selector = FALSE;
                    } else {
                        if (data.cookingMode == 'a') {
                            //only allows you to change to temp if in bake mode
                            selector = TRUE;
                        }
                    }
                    //leave the while loop
                    break;
                }
            }
            data.ovenState = START;
            print();
            break;
            //countdown state: aka its cookin
        case COUNTDOWN:
            //set the countdown to the initial time from the potentiometer
            data.remTime = data.initTime * 2;
            

            while (TRUE) {
                //gotta divide by two since remTime is double initTime
                sec = (data.remTime / 2) % 60;
                min = (data.remTime / 2) / 60;
                
                //if ran out of time, break the loops
                if(data.remTime <= 0)
                {
                    data.ovenState = RESET;
                    break;
                }
                
                //stay in countdown case until time runs out or reset
                data.ovenState = COUNTDOWN;
                //update the OLED
                print();
            }
            break;
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


//boolean for switching between temperature and time on "bake" mode

void print(void)
{
    switch (data.cookingMode) {

        //bake mode
    case('a'):
        sprintf(lineOne, "|%c%c%c%c%c|  MODE: Bake \n", TOP_OVEN_OFF, TOP_OVEN_OFF, TOP_OVEN_OFF,
                TOP_OVEN_OFF, TOP_OVEN_OFF);
        //if selector is true, switch temperature
        if (selector == TRUE) {
            //176 is the ASCII code for the degree symbol
            sprintf(lineTwo, "|     |  TIME: %d:%02d \n", min, sec);
            sprintf(lineThree, "|-----| >TEMP: %d%cF \n", data.temp, 248);
            //if selector is false, switch time
        } else {
            sprintf(lineTwo, "|     | >TIME: %d:%02d \n", min, sec);
            sprintf(lineThree, "|-----|  TEMP: %d%cF \n", data.temp, 248);
        }
        sprintf(lineFour, "|%c%c%c%c%c|\n", BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF,
                BOT_OVEN_OFF);

        //print statements
        //but first, copy the strings into one big string!
        strcpy(displayOutput, lineOne);
        strcat(displayOutput, lineTwo);
        strcat(displayOutput, lineThree);
        strcat(displayOutput, lineFour);

        //reset the display
        OledSetDisplayNormal();
        OledDrawString(displayOutput);
        OledUpdate();
        break;

        //broil mode    
    case('b'):
        sprintf(lineOne, "|%c%c%c%c%c|  MODE: Broil \n", TOP_OVEN_OFF, TOP_OVEN_OFF, TOP_OVEN_OFF,
                TOP_OVEN_OFF, TOP_OVEN_OFF);
        sprintf(lineTwo, "|     |  TIME: %d:%02d \n", min, sec);
        sprintf(lineThree, "|-----|  TEMP: 500%cF \n", 248);
        sprintf(lineFour, "|%c%c%c%c%c|\n", BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF,
                BOT_OVEN_OFF);

        //print statements
        //but first, copy the strings into one big string!
        strcpy(displayOutput, lineOne);
        strcat(displayOutput, lineTwo);
        strcat(displayOutput, lineThree);
        strcat(displayOutput, lineFour);

        //reset the display
        OledSetDisplayNormal();
        OledDrawString(displayOutput);
        OledUpdate();
        break;

        //toast mode
    case('c'):
        sprintf(lineOne, "|%c%c%c%c%c|  MODE: Toast \n", TOP_OVEN_OFF, TOP_OVEN_OFF, TOP_OVEN_OFF,
                TOP_OVEN_OFF, TOP_OVEN_OFF);
        sprintf(lineTwo, "|     |  TIME: %d:%02d \n", min, sec);
        sprintf(lineThree, "|-----|              \n");
        sprintf(lineFour, "|%c%c%c%c%c|\n", BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF, BOT_OVEN_OFF,
                BOT_OVEN_OFF);

        //print statements
        //but first, copy the strings into one big string!
        strcpy(displayOutput, lineOne);
        strcat(displayOutput, lineTwo);
        strcat(displayOutput, lineThree);
        strcat(displayOutput, lineFour);

        //reset the display
        OledSetDisplayNormal();
        OledDrawString(displayOutput);
        OledUpdate();
        break;

    }
}

//2hz timer

void __ISR(_TIMER_1_VECTOR, ipl4auto) TimerInterrupt2Hz(void)
{
    //count down the timer by 1
    data.remTime = data.remTime - 1;
    // Clear the interrupt flag.
    IFS0CLR = 1 << 4;

}

//5hz timer

void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    //increment the timer
    data.buttonPress += 1;
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

}

//100hz timer

void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    buttonEvents = ButtonsCheckEvents();
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

}