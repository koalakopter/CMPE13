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
char command;
int out;
// **** Declare function prototypes ****
/******************************************************************************
 * Your function prototypes go in between this comment and the following one with asterisks.
 *****************************************************************************/
double Round(double operand);

double AbsoluteValue(double operand);

double FahrenheitToCelsius(double operand);

double CelsiusToFahrenheit(double operand);

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
        //reset inputs
        operand = 0;
        operand2 = 0;
        command = '\0';
        
        printf("Welcome to Julian's calculator program!\n");
        printf("Available commands: (mult)*\n (div)/\n (add)+\n (sub)-\n (avg)v\n |abs|a\n (F->C)c\n (C->F)f\n (tan)t\n (round)r\n");

        printf("Please choose a command to perform\n");
        scanf(" %c", &command);


        printf("\nChosen command was: %c", command);

        printf("\nPlease input a number:");

        scanf(" %f", &operand);
        printf("chosen operand is %f\n", operand); //for test

        //if a second operator is needed
        if (command == '*' || command == '/' || command == '+' || command == '-' || command == 'v') {
            printf("\nPlease input a second number:");
            scanf(" %f", &operand2);
            printf("chosen second operand is %f\n", operand2); //for test
        }

        //absolute value
        if (command == 'a') {
            output = AbsoluteValue(operand);
            printf("The Absolute Value of %f is: %f\n\n", operand, output);
        }//Fahrenheit to Celsius
        else if (command == 'c') {
            output = FahrenheitToCelsius(operand);
            printf("%fFahrenheit in Celsius is: %f", operand, output);
        }//Celsius to Fahrenheit
        else if (command == 'f') {
            output = CelsiusToFahrenheit(operand);
            printf("%fCelsius in Fahrenheit is: %f", operand, output);
            //average value
        } else if (command == 'v') {
            output = Average(operand, operand2);
            printf("The average of %f and %f is: %f", operand, operand2, output);
            //tangent
        } else if (command == 't') {
            output = Tangent(operand);
            printf("Tangent of %f degrees is: %f", operand, output);
            //multiplication
        } else if (command == '*') {
            output = Multiplication(operand, operand2);
            printf("Multiplying %f and %f results in: %f", operand, operand2, output);
            //division
        } else if (command == '/') {
            output = Division(operand, operand2);
            printf("Dividing %f and %f results in: %f", operand, operand2, output);
            //addition
        } else if (command == '+') {
            output = Addition(operand, operand2);
            printf("Adding %f and %f results in: %f", operand, operand2, output);
            //subtraction
        } else if (command == '-') {
            output = Subtraction(operand, operand2);
            printf("Subtracting %f and %f results in: %f", operand, operand2, output);
        }//round (extra credit)
        else if (command == 'r') {
            output = Round(operand);
            printf("Rounding %f to the nearest integer gives: %f", operand, output);
        } else {
            printf("Not a valid command, Please try again");
            
        }
        printf("\n\n\n\n"); //newline buffer to make things look nicer
        
        char stuff;
        //some other stuff for cleanliness
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
double FahrenheitToCelsius(double x)
{
    x = (x - 32.0)*(5 / 9);
    return x;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double x)
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
    if (y == 0) {
        printf("\nERROR DIVIDE BY ZERO WHAT HAVE YOU DONE\n");
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
    double z = x + y
    return z;
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    if (operand >= 0) {
        out = operand + 0.5;
        return out;
    } else {
        out = operand - 0.5;
        return out;
    }

}

