// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries

#include "Stack.h"

// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****


// This code will unit test the Stack.c implementation. You should run at least two different tests
// on each function to be able to determine if it is working correctly. You will have to write these
// tests yourself.


int main() {
    BOARD_Init();

    /******************************** Your custom testing code goes below here ***********************/
    printf("Welcome to CMPE13 Stack Unit Testing for XXX. Replace XXX with your cruzID and name.\r\n");


    /*************************************************************************************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}


