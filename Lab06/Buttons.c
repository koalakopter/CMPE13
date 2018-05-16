#include "Buttons.h"
#include <xc.h>

#include <stdio.h>

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

uint8_t current;

uint8_t ButtonsCheckEvents(void)
{
    /**
     * Provides a way to quickly get the status of all 4 pushbuttons in to 4-bits, where a bit is 1 if
     * the button is being pressed and 0 if it's not. The buttons are ordered such that bit 3 is button
     * 4 and bit 0 is button 1. */
    uint8_t state = BUTTON_STATES();
    uint8_t result = 0; //used to store the end result and is returned at the end of the function.
    //will be used for bitwise OR operations

    current = current + 0; //I'm a stupid statement that makes errros go away

    //if nothing changed return nothing
    if (state == current) {
        return BUTTON_EVENT_NONE;
    }

    //checks if current state and button_state_1 match
    if (state & BUTTON_STATE_1) {
        //if current does not have the bits for button_state_1 activated, turn those bits on
        if (!(current & BUTTON_STATE_1)) {

            //toggle appropriate bits
            current = current | BUTTON_STATE_1;
            //result now holds and stores button 1's down action
            result = result | BUTTON_EVENT_1DOWN;
        }
    }        //check if state and the button_state_1 don't match
    else if (!(state & BUTTON_STATE_1)) {

        //if they current and state1 match, that means button was released
        if (current & BUTTON_STATE_1) {

            //invert the bits of state1 then AND it with current
            current = current & (~BUTTON_STATE_1);
            //change result to store the up state
            result = result | BUTTON_EVENT_1UP;
        }
    }
    //its just copy paste from here on out
    //BUTTON 2 CODE
    if (state & BUTTON_STATE_2) {
        //if current does not have the bits for button_state_2 activated, turn those bits on
        if (!(current & BUTTON_STATE_2)) {

            //toggle appropriate bits
            current = current | BUTTON_STATE_2;
            //result now holds and stores button 2's down action
            result = result | BUTTON_EVENT_2DOWN;
        }
    }        //check if state and the button_state_2 don't match
    else if (!(state & BUTTON_STATE_2)) {

        //if they current and state2 match, that means button was released
        if (current & BUTTON_STATE_2) {

            //invert the bits of state2 then AND it with current
            current = current & (~BUTTON_STATE_2);
            //change result to store the up state
            result = result | BUTTON_EVENT_2UP;
        }
    }
    //BUTTON 3 CODE
    if (state & BUTTON_STATE_3) {
        //if current does not have the bits for button_state_3 activated, turn those bits on
        if (!(current & BUTTON_STATE_3)) {

            //toggle appropriate bits
            current = current | BUTTON_STATE_3;
            //result now holds and stores button 3's down action
            result = result | BUTTON_EVENT_3DOWN;
        }
    }        //check if state and the button_state_3 don't match
    else if (!(state & BUTTON_STATE_3)) {

        //if they current and state3 match, that means button was released
        if (current & BUTTON_STATE_3) {

            //invert the bits of state3 then AND it with current
            current = current & (~BUTTON_STATE_3);
            //change result to store the up state
            result = result | BUTTON_EVENT_3UP;
        }
    }
    //BUTTON 4 CODE
    if (state & BUTTON_STATE_4) {
        //if current does not have the bits for button_state_4 activated, turn those bits on
        if (!(current & BUTTON_STATE_4)) {

            //toggle appropriate bits
            current = current | BUTTON_STATE_4;
            //result now holds and stores button 4's down action
            result = result | BUTTON_EVENT_4DOWN;
        }
    }        //check if state and the button_state_4 don't match
    else if (!(state & BUTTON_STATE_4)) {

        //if they current and state4 match, that means button was released
        if (current & BUTTON_STATE_4) {

            //invert the bits of state4 then AND it with current
            current = current & (~BUTTON_STATE_4);
            //change result to store the up state
            result = result | BUTTON_EVENT_4UP;
        }
    }
    return result;
}