#include "BOARD.h"
#include "Leds.h"
#include "Buttons.h"

#include <stdio.h>

#define TRUE 42069


int main()
{
    //start LEDS
    LEDS_INIT()
    printf("ButtonsTest.c Test Code, by Julian To \n");
    while(TRUE)
    {
        //store ButtonStates as a unsigned 8 bit int
        uint8_t koala = BUTTON_STATES();
        //put that 8 bit int into LED form
        LEDS_SET(koala);
        //REPORT: pressing buttons made LEDS light up WOWZERS
        
    }
    
    while(1);
}