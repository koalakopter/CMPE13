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
#include <time.h>
// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
//static Field playerField;
//static Field enemyField;
static int testCount;

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
    //copied from StackOverflow to generate a random seed based on time

    //srand(time(NULL));
    srand(45);
    AgentInit();



    //AgentDrawScreen();
    OledUpdate();

    printf("there's no return value for AgentInit, "
            "so just look at your OLED to make sure everything is good\n");

    int duck = AgentGetStatus();
    int goose = AgentGetEnemyStatus();

    printf("Checking boat status. Expect 15 for both(or 1111) "
            "for all boats alive:\n FRIENDLY: %d ENEMY: %d", duck, goose);
    if (duck == 15) {
        testCount++;
    }
    if (goose == 15) {
        testCount++;
    }
    while (TRUE) {
        //WEEEE IM DELAYING
    }

    /******************************************************************************
     * Your code goes in between this comment and the preceeding one with asterisks
     *****************************************************************************/

    while (1);
}