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
        {7, 8, 9}};
    float two[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    float three[3][3];
    float four[3][3];
     float five[3][3] = {
        {5, 2, 1},
        {4, 5, 6},
        {7, 4, 3}};
    
    /*TESTING SECTION BEWARE OF BUGS*/
    int z = MatrixEquals(one, two);
    printf("result is %d, should be one", z);
    
    
    //MatrixMultiply(one, two, three);
    //MatrixPrint(three);
   
    int scalar = 5;
    MatrixScalarMultiply(scalar, one, three);
    MatrixPrint(three);
    
    MatrixScalarAdd(2, one, four);
    MatrixPrint(four);
    
    //MatrixPrint(one);
     
    float det = MatrixDeterminant(five);
    printf("determinant is  %f", det);
   

    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}

