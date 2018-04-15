// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries


// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****
/******************************************************************************
 * Your function prototypes go in between this comment and the following one with asterisks.
 *****************************************************************************/
double Round(double operand);

double AbsoluteValue(double operand);

double FarenheitToCelsius(double operand);

double CelsiusToFarenheit(double operand);

double Tangent(double operand);

double Average(double operand);

double Multiplication(double operand, double operand2); 

double Division(double operand, double operand2);

double Addition(double operand, double operand2);

double Subtraction(double operand, double operand2);

/******************************************************************************
 * Your function prototypes go in between this comment and the preceding one with asterisks
 *****************************************************************************/


// If this code is used for testing, rename main to something we can call from our testing code.
#ifndef LAB2_TESTING

int main(void)
{
    BOARD_Init();
#else

int their_main(void)
{
#endif // LAB2_TESTING

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    //welcome messages
    printf("Welcome to the calculator!\n");
    printf("Please choose a program to perform\n");
    printf("Available commands: *, /, +, -, v, a, c, f, t, r\n");
    
    char command[5];
    scanf("%c", &command);
    
    printf("Chosen command was: %c", command);




    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/
    while (1);
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double x)
{
    if (x >= 0) {
        return x;
    } else {
        return x*-1;
    }
}


/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/



/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/



/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/



/*********************************************************************************
 * Define the Tangent function that takes input in degrees (Note: Your tangent 
 * function relies on a call from the tangent function of math.h which uses 
 * radians).
 ********************************************************************************/

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    return operand;
}

