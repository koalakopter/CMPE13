// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"


// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "MatrixMath.h"

// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****
//checks if a function passes a test, and if it does, increment a counter

int pass(int check, int counter)
{
    if (check == 1) {
        return counter + 1;
    }
    return counter;
}

int main()
{
    BOARD_Init();

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    //me test
    float one[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    float two[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    float three[3][3];
    float four[3][3] = {
        {5, 2, 1},
        {4, 5, 6},
        {7, 4, 3}
    };

    /*TESTING HARNESS SECTION*/
    //testing MatrixEquals
    int count1 = 0; //counts how many tests passed
    int testOne = MatrixEquals(one, two);
    int testTwo = MatrixEquals(four, three);

    if (testOne == 1) {
        count1++;
    }
    if (testTwo == 0) {
        count1++;
    }
    printf("MatrixEquals Function tested: %d out of 2 tests successful \n", count1);

    //Testing MatrixScalarAdd
    int count2 = 0;
    float five[3][3] = {
        {-1, -2, -3},
        {-4, -5, -6},
        {-7, -8, -9}
    };
    float six[3][3] = {
        {-11, -12, -13},
        {-14, -15, -16},
        {-17, -18, -19}
    };
    float seven[3][3];
    float eight[3][3] = {
        {-5, -5, -5},
        {-5, -5, -5},
        {-5, -5, -5}
    };
    MatrixScalarAdd(-10, five, five);
    MatrixScalarAdd(-5, seven, seven);

    int testThree = MatrixEquals(five, six);
    int testFour = MatrixEquals(seven, eight);

    if (testThree == 1) {
        count2++;
    }
    if (testFour == 1) {
        count2++;
    }
    printf("MatrixScalarAdd Function tested: %d out of 2 tests successful \n", count2);





    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}

