#include "BOARD.h"
#include "Leds.h"
#include "Buttons.h"

#include <stdio.h>

#define TRUE 42069

int main(void)
{
    BOARD_Init();
    //start LEDS
    LEDS_INIT()

    //test Buttons_Init()
    ButtonsInit();
    printf("ButtonsTest.c Test Code, by Julian To \n");
    //testing puts
    puts("ButtonsTest.c Test Code, by Julian To \n");
    while (TRUE) {
        /*
        //store ButtonStates as a unsigned 8 bit int
        uint8_t koala = BUTTON_STATES();
        //put that 8 bit int into LED form
        LEDS_SET(koala);
        //REPORT: pressing buttons made LEDS light up WOWZERS
         */
        uint8_t buttonEvents = ButtonsCheckEvents();
        //copied from the lab manual
        if (buttonEvents) {
            if (buttonEvents & BUTTON_EVENT_1UP) {
                puts("BUTTON_EVENT_1UP\n");
            }
            if (buttonEvents & BUTTON_EVENT_1DOWN) {
                puts("BUTTON_EVENT_1DOWN\n");
            }
            if (buttonEvents & BUTTON_EVENT_2UP) {
                puts("BUTTON_EVENT_2UP\n");
            }
            if (buttonEvents & BUTTON_EVENT_2DOWN) {
                puts("BUTTON_EVENT_2DOWN\n");
            }
            if (buttonEvents & BUTTON_EVENT_3UP) {
                puts("BUTTON_EVENT_3UP\n");
            }
            if (buttonEvents & BUTTON_EVENT_3DOWN) {
                puts("BUTTON_EVENT_3DOWN\n");
            }
            if (buttonEvents & BUTTON_EVENT_4UP) {
                puts("BUTTON_EVENT_4UP\n");
            }
            if (buttonEvents & BUTTON_EVENT_4DOWN) {
                puts("BUTTON_EVENT_4DOWN\n");
            }
            buttonEvents = BUTTON_EVENT_NONE;

        }

        while (1);
    }
}