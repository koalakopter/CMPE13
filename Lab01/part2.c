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

    //column headers
    printf("%5c %5c \n", 'F', 'C');
    //Print out table
    while (fahr <= upper) {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%7.1f %04.0f \n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }
    printf("\n"); //add a new line between conversion tables

    //Kelvin to Fahrenheit
    float kelvin = lower;
    //column header
    printf("%5c %6c \n", 'K', 'F');
    
    while (kelvin <= upper) {
        fahr = ((kelvin - 273.15)*1.8) + 32.0;
        printf("%3.3f %5f\n", (double) kelvin, (double) fahr);
        kelvin = kelvin + step;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}
