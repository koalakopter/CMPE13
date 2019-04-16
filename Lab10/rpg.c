// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CMPE13 Support Library
#include "UNIXBOARD.h"



// User libraries
#include "Player.h"
#include "Game.h"

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
char input = '\0';
char direction = '\0';
// **** Declare any function prototypes here ****

int main()
{

    /******************************** Your custom code goes below here ********************************/
    //printf("hiii");
    printf("\033[2J\n"); //clear the screen
    if (GameInit() == STANDARD_ERROR) {
        printf("ERROR");
        //FATAL_ERROR();
        //idk but this causes the code to not compile
        STANDARD_ERROR;
    }
    while (1) {
        printf("\nPlease select a direction to go! n-North s-South e-East w-West, or q-Quit\n");
        input = getchar();
        if (input != EOF) //checks for a single char
        {
            if (input == 'n' || input == 's' || input == 'w' || input == 'e' || input == 'q') {
                direction = input; //if invalid is a valid input, set direction to input
            }
        }
        switch (direction) {

        case 'n':
            GameGoNorth();
            break;
        case 's':
            GameGoSouth();
        case 'w':
            GameGoWest();
        case 'e':
            GameGoEast();
        case 'q':
            printf("\nGame Quit");
            direction = '\0';
            break;
        default:
            printf("\nINVALID DIRECTION OR CHARACTER INPUT");
            break;
        }
    }
    /**************************************************************************************************/
}

