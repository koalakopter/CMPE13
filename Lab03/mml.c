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
int functionPassed;
// **** Declare function prototypes ****

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
    if (count1 == 2) {
        functionPassed++;
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
    if (count2 == 2) {
        functionPassed++;
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
    if (count3 == 2) {
        functionPassed++;
    }
    printf("MatrixScalarMultiply Function tested: %d out of 2 tests successful \n", count3);

    //test for MatrixMultiply
    int count4 = 0;
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
    if (count4 == 2) {
        functionPassed++;
    }
    printf("MatrixMultiply Function tested: %d out of 2 tests successful \n", count4);

    //testing MatrixAdd
    int count5 = 0;
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
    if (count5 == 2) {
        functionPassed++;
    }
    printf("MatrixAdd Function tested: %d out of 2 tests successful \n", count5);

    //testing MatrixDeterminant function
    int count6 = 0;
    float testEleven = MatrixDeterminant(six);
    float testTwelve = MatrixDeterminant(ten);

    if (testEleven == 0) {
        count6++;
    }
    if (testTwelve == 992.0) {
        count6++;
    }
    if (count6 == 2) {
        functionPassed++;
    }
    printf("MatrixDeterminant Function tested: %d out of 2 tests successful \n", count6);

    //testing MatrixTrace function
    int count7 = 0;
    float testThirteen = MatrixTrace(six);
    float testFourteen = MatrixTrace(ten);

    if (testThirteen == -45.0) {
        count7++;
    }
    if (testFourteen == -12.0) {
        count7++;
    }
    if (count7 == 2) {
        functionPassed++;
    }
    printf("MatrixTrace Function tested: %d out of 2 tests successful \n", count7);

    //Testing for Matrix Transpose
    int count8 = 0;
    float twentyFive[3][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    float twentySix[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    MatrixTranspose(one, one);
    MatrixTranspose(twentySix, twentySix);

    int testFifteen = MatrixEquals(one, twentyFive);
    int testSixteen = MatrixEquals(twentySix, twelve);

    if (testFifteen == 1) {
        count8++;
    }
    if (testSixteen == 1) {
        count8++;
    }
    if (count8 == 2) {
        functionPassed++;
    }
    printf("MatrixTranspose Function tested: %d out of 2 tests successful \n", count8);

    //test for Matrix Inverse
    int count9 = 0;
    //case1: invertable
    float twentySeven[3][3] = {
        {2, -3, 6},
        {-4, 1, 5},
        {2, 1, -4}
    };
    //case2: if the inverse matrix doesn't exist, return the same matrix
    float twentyEight[3][3] = {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}
    };
    float twentyNine[3][3] = {
        {1.0 / 4, 1.0 / 6, 7.0 / 12},
        {1.0 / 6, 5.0 / 9, 17.0 / 18},
        {1.0 / 6, 2.0 / 9, 5.0 / 18}
    };
    float thirty [3][3];
    float thirtyOne [3][3];
    MatrixInverse(twentyEight, thirtyOne);
    MatrixInverse(twentySeven, thirty);

    int testSeventeen = MatrixEquals(thirty, twentyNine);
    int testEighteen = MatrixEquals(twentySix, thirtyOne);
    if (testSeventeen == 1) {
        count9++;
    }
    if (testEighteen == 1) {
        count9++;
    }
    if (count9 == 2) {
        functionPassed++;
    }
    printf("MatrixInverse Function tested: %d out of 2 tests successful \n", count9);

    double passPercent = (functionPassed / 9.0)*100.0;
    printf("\nPassed %d out of 9 functions: %f %% success rate \n", functionPassed, passPercent);
    //TEST FOR MATRIX PRINT FUNCTION

    // for loop creates matrix that looks like this
    /*
     1 2 3
     4 5 6
     7 8 9
     */
    int x, y;
    float value = 1;
    float array[3][3];
    printf("\nEXPECTED OUTPUT OF ARRAY \n");
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            array[x][y] = value;
            printf(" %f, ", (double) value);
            value++;
        }
        printf("\n");
    }
    printf("\nOUTPUT OF ARRAY WITH MatrixPrint():\n");
    MatrixPrint(array);
    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}

