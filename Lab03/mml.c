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

void Checker(int check, int counter)
{
    if (check != 1.0) {
        counter++;
    }
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

    //test for MatrixScalarMultiply
    int count3 = 0;
    float nine[3][3] = {
        {-2, 5, -2},
        {4, 2, 0},
        {-1, -3, 6}
    };
    float ten[3][3] = {
        {4, -10, 4},
        {-8, -4, 0},
        {2, 6, -12}
    };
    float eleven[3][3];
    float twelve[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    MatrixScalarMultiply(-2.0, nine, nine);
    MatrixScalarMultiply(0, eleven, eleven);

    int testFive = MatrixEquals(nine, ten);
    int testSix = MatrixEquals(twelve, eleven);
    if (testFive == 1) {
        count3++;
    }
    if (testSix == 1) {
        count3++;
    }
    printf("MatrixScalarMultiply Function tested: %d out of 2 tests successful \n", count3);

    //test for MatrixMultiply
    int count4;
    float thirteen[3][3] = {
        {1, 2, 3},
        {4, 6, -3},
        {-9, -3, 6}
    };
    float fourteen[3][3] = {
        {2, 2, 3},
        {-4, 9, 1},
        {-8, 5, -2}
    };
    float fifteen[3][3] = {
        {-30, 35, -1},
        {8, 47, 24},
        {-54, -15, -42}
    };
    float sixteen[3][3] = {
        {1, 2, 3},
        {9, 8, 7},
        {4, 5, 6}
    };
    float seventeen[3][3] = {
        {31, 33, 35},
        {109, 117, 125},
        {73, 78, 83}
    };
    float eighteen[3][3];
    float nineteen[3][3];

    MatrixMultiply(thirteen, fourteen, eighteen);
    MatrixMultiply(sixteen, sixteen, nineteen);

    int testSeven = MatrixEquals(eighteen, fifteen);
    int testEight = MatrixEquals(nineteen, seventeen);
    if (testSeven == 1) {
        count4++;
    }
    if (testEight == 1) {
        count4++;
    }
    printf("MatrixMultiply Function tested: %d out of 2 tests successful \n", count4);

    //testing MatrixAdd
    int count5;
    float twenty[3][3] = {
        {-1, -2, -3},
        {-4, -5, -6},
        {-7, -8, -9}
    };
    float twentyOne[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    float twentyTwo[3][3] = {
        {0.5, 1, 1.5},
        {2, 3, -1.5},
        {-4.5, -1.5, 3}
    };
    float twentyThree[3][3];
    float twentyFour[3][3];
    
    MatrixAdd(twenty, twentyOne, twentyThree);
    MatrixAdd(twentyTwo, twentyTwo, twentyFour);
    
    int testNine = MatrixEquals(twentyThree, twelve);
    int testTen = MatrixEquals(twentyFour, thirteen);
    if (testNine == 1) {
        count5++;
    }
    if (testTen == 1) {
        count5++;
    }
    printf("MatrixAdd Function tested: %d out of 2 tests successful \n", count5);



    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}

