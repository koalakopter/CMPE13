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
double operand, operand2, output;
// **** Declare function prototypes ****
/******************************************************************************
 * Your function prototypes go in between this comment and the following one with asterisks.
 *****************************************************************************/
double Round(double operand);

double AbsoluteValue(double operand);

double FarenheitToCelsius(double operand);

double CelsiusToFarenheit(double operand);

double Tangent(double operand);

double Average(double operand, double operand2);

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
    while (1) {
        printf("Welcome to the calculator!\n");
        printf("Please choose a program to perform\n");
        printf("Available commands: (mult)*\n (div)/\n (add)+\n (sub)-\n (avg)v\n |abs|a\n (F->C)c\n (C->F)f\n (tan)t\n (round)r\n");

        char command;
        scanf("%c", &command);


        printf("\nChosen command was: %c", command);
        
        printf("\nPlease input a number:");
        
        scanf("%f", &operand);
        printf("chosen operand is %f\n", operand); //for test
        
        //absolute value
        if (command = 'a')
        {
            output = AbsoluteValue(operand);
            printf("The Absolute Value of %f is: %f\n\n", operand, output);
        }
        //Fahrenheit to Celsius
        else if (command = 'c')
        {
            output = FarenheitToCelsius(operand);
            printf("%f in Celsius is: %f", operand, output);
        }
        //Celsius to Fahrenheit
        else if (command = 'f')
        {
            output = CelsiusToFarenheit(operand);
            printf("%f in Fahrenheit is: %f", operand, output);
        }
        else if (command = 'v')
        {
            output = Average(operand, operand2);
            printf("The average of %f and %f is: %f", operand, operand2, output);
        }
    }
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
    double FarenheitToCelsius(double x)
    {
        x = (x - 32.0)*(5 / 9);
        return x;
    }

    /*********************************************************************************
     * Define the Celsius to Fahrenheit function here.
     ********************************************************************************/
    double CelsiusToFarenheit(double x)
    {
        x = (x * 1.8) + 32;
        return x;
    }

    /********************************************************************************
     * Define the Average function here.
     *******************************************************************************/
    double Average(double x, double y)
    {
        return (x + y) / 2.0;
    }

    /*********************************************************************************
     * Define the Tangent function that takes input in degrees (Note: Your tangent 
     * function relies on a call from the tangent function of math.h which uses 
     * radians).
     ********************************************************************************/
    double Tangent(double x)
    {
        x = x * (M_PI / 180.0);
        return tan(x);
    }

    //arithmetic operations

    double Multiplication(double x, double y)
    {
        double z = x * y;
        return z;
    }

    double Division(double x, double y)
    {
        if (y = 0) {
            return 0;
        } else {
            return x / y;
        }
    }

    double Subtraction(double x, double y)
    {
        double z = x - y;
        return z;
    }

    double Addition(double x, double y)
    {
        double z = x + y;
        return z;
    }

    /*********************************************************************************
     * Define the Round function here.
     * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
     * this function.
     ********************************************************************************/
    double Round(double operand)
    {
        return operand;
    }

