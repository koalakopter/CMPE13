// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Protocol.h"
#include "Ascii.h"
#include "Agent.h"
#include "Field.h"
#include "FieldOled.h"
#include "Leds.h"
#include "Oled.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdio.h>
// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
static Field *playerField;
static Field *enemyField;


// **** Declare any function prototypes here ****



int main()
{
    BOARD_Init();



/******************************************************************************
 * Your code goes in between this comment and the following one with asterisks.
 *****************************************************************************/
    //printf("Starting tests!\n");
    OledInit();
    LEDS_INIT();
    AgentInit();
    FieldOledDrawScreen(playerField, enemyField, FIELD_OLED_TURN_NONE);
    //OledDrawString("FUUCCKKK");
    OledUpdate();

/******************************************************************************
 * Your code goes in between this comment and the preceeding one with asterisks
 *****************************************************************************/

    while (1);
}