// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    //declare variables
    float fahr, celsius;
    int lower, upper, step;
    
    //Initialize Variables
    lower = 0; //lower limit of temperature
    upper = 300; //upper limit
    step = 20; //step size
    fahr = lower;
    
    //Print out table
    while (fahr <= upper) {
        celsius = (5.0/9.0)*(fahr-32.0);
        printf("%f %f\n", (double)fahr, (double)celsius);
        fahr = fahr + step;  
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}
