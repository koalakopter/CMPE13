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

uint8_t ButtonsCheckEvents(void)
{
    /**
     * Provides a way to quickly get the status of all 4 pushbuttons in to 4-bits, where a bit is 1 if
     * the button is being pressed and 0 if it's not. The buttons are ordered such that bit 3 is button
     * 4 and bit 0 is button 1. */
    uint8_t state = BUTTON_STATES();
    uint8_t result = 0; //used to store the end result and is returned at the end of the function.
    //will be used for bitwise OR operations
    uint8_t current;

    //checks if current state and button_state_1 match
    if (state & BUTTON_STATE_1) {
        //if current does not have the bits for button_state_1 activated, turn those bits on
        if (!(current & BUTTON_STATE_1)) {
            
            //toggle appropriate bits
            current = current | BUTTON_STATE_1;
            //result now holds and stores button 1's down action
            result = result | BUTTON_EVENT_1DOWN;
        }
    }
        //check if state and the button_state_1 don't match
    else if (!(state & BUTTON_STATE_1)) {
        
        //if they current and state1 match, that means button was released
        if (current & BUTTON_STATE_1) {
            
            //invert the bits of state1 then AND it with current
            current = current & (~BUTTON_STATE_1);
            //change result to store the up state
            result = result | BUTTON_EVENT_1UP;
        }
    }

    return result;
}