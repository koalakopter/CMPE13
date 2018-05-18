#include "Buttons.h"
#include <xc.h>

#include <stdio.h>

#define AND &
#define OR |

#define TRUE 1
#define FALSE 0

//buttons init function

void ButtonsInit(void)
{
    //copied from the lab manual
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}



/* BUTTON_STATES() returns these:
    BUTTON_STATE_1 = 0x1,
    BUTTON_STATE_2 = 0x2,
    BUTTON_STATE_3 = 0x4,
    BUTTON_STATE_4 = 0x8
 */
//ButtonsCheckEvents function

//keeps track of the current buttons that are down or up
//also keeps value between function calls
static int oneD, twoD, threeD, fourD;

uint8_t ButtonsCheckEvents(void)
{
    /**
     * Provides a way to quickly get the status of all 4 pushbuttons in to 4-bits, where a bit is 1 if
     * the button is being pressed and 0 if it's not. The buttons are ordered such that bit 3 is button
     * 4 and bit 0 is button 1. */
    uint8_t state = BUTTON_STATES();
    uint8_t result = BUTTON_EVENT_NONE; //used to store the end result and is returned at the end of the function.

    //will be used for bitwise OR operations
    static uint8_t upDownCheck; //static so it can't be accessed outside of file

    upDownCheck = upDownCheck + 0; //I'm a stupid statement that makes errors go away


    //checks if current state and button_state_1 match
    if (state AND BUTTON_STATE_1) {
        //check if the button has been pressed before without being released
        if (oneD == FALSE) {

            //recognize that the button has now been pressed
            oneD = TRUE;
            //result now holds and stores button 1's down action
            result = result OR BUTTON_EVENT_1DOWN;
        }
    }//check if state and the button_state_1 don't match
    else if (!(state AND BUTTON_STATE_1)) {

        //check if the button has been pressed before without being released
        if (oneD == TRUE) {

            //recognize that the button has now been released
            oneD = FALSE;
            //change result to store the up state
            result = result OR BUTTON_EVENT_1UP;
        }
    }
    //its just copy paste from here on out
    //BUTTON 2 CODE
    if (state AND BUTTON_STATE_2) {
        //check if the button has been pressed before without being released
        if (twoD == FALSE) {

            //recognize that the button has now been pressed
            twoD = TRUE;
            //result now holds and stores button 2's down action
            result = result OR BUTTON_EVENT_2DOWN;
        }
    }//check if state and the button_state_2 don't match
    else if (!(state AND BUTTON_STATE_2)) {

       //check if the button has been pressed before without being released
        if (twoD == TRUE) {

            //recognize that the button has now been released
            twoD = FALSE;
            //change result to store the up state
            result = result OR BUTTON_EVENT_2UP;
        }
    }
    //BUTTON 3 CODE
    if (state AND BUTTON_STATE_3) {
        //check if the button has been pressed before without being released
        if (threeD == FALSE) {

            //recognize that the button has now been pressed
            threeD = TRUE;
            //result now holds and stores button 3's down action
            result = result OR BUTTON_EVENT_3DOWN;
        }
    }//check if state and the button_state_3 don't match
    else if (!(state AND BUTTON_STATE_3)) {

        //check if the button has been pressed before without being released
        if (threeD == TRUE) {

            //recognize that the button has now been released
            threeD = FALSE;
            //change result to store the up state
            result = result OR BUTTON_EVENT_3UP;
        }
    }
    //BUTTON 4 CODE
    if (state AND BUTTON_STATE_4) {
        //check if the button has been pressed before without being released
        if (fourD == FALSE) {

            //recognize that the button has now been pressed
            fourD = TRUE;
            //result now holds and stores button 4's down action
            result = result OR BUTTON_EVENT_4DOWN;
        }
    }//check if state and the button_state_4 don't match
    else if (!(state AND BUTTON_STATE_4)) {

        //check if the button has been pressed before without being released
        if (fourD == TRUE) {

            //recognize that the button has now been released
            fourD = FALSE;
            //change result to store the up state
            result = result OR BUTTON_EVENT_4UP;
        }
    }
    //will return BUTTON_EVENT_NONE if nothing changed
    return result;
}