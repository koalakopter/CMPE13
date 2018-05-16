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

//ButtonsCheckEvents function
uint8_t ButtonsCheckEvents(void)
{
    
}