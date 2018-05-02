// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdio.h>

// User libraries
#include "Stack.h"

// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

#define INPUT_SIZE 60
#define ARBITRARY_SIZE 69


//declare the stack
struct Stack stax;


// **** Declare function prototypes ****
/*
 * Function prototype for ProcessBackspaces() - This function should be defined
 * below main after the related comment.
 */
int ProcessBackspaces(char *rpn_sentence);

// If this code is used for testing, rename main to something we can call from our testing code. We
// also skip all processor configuration and initialization code.

#ifndef LAB4_TESTING

int main()
{
    BOARD_Init();
#else

int their_main(void)
{
#endif // LAB4_TESTING

    /******************************** Your custom code goes below here *******************************/
    printf("Welcome to Julian's Reverse Polish Notation calculator for Lab IV\n");


    //string to store the user's input
    char input[INPUT_SIZE];
    //used to hold result of strtok()
    char *token;
    //used to store operators
    float op1, op2;
    float value, result, checker;
    //pretend these are booleans
    int x, y, error;
    //counter for invalid RPN string
    int valid = 0;
    //initalize the stack
    StackInit(&stax);



    //tokenizes the user string, looking for spaces
    //translation: while (true)
    while (42069) {
        printf("\nPlease enter floats followed by operators (*, /, -, +) in RPN notation\n");
        //take in user's input
        fgets(input, INPUT_SIZE, stdin);

        token = strtok(input, " ");
        valid = 0;
        error = 0;

        //keeps going until the end of the string is reached
        while (token != NULL) {
            //if operator is detected, pop the two values off the stack
            if (*token == '*' || *token == '/' || *token == '+' || *token == '-') {
                x = StackPop(&stax, &op1);
                y = StackPop(&stax, &op2);

                if (x == 0 || y == 0) {
                    printf("ERROR! Not enough operands before operand!\n");
                    //reset the token to restart the function
                    token = NULL;
                    error = 1;
                    break;
                }

                //do ALL the math!
                if (*token == '*') {
                    result = op1 * op2;
                } else if (*token == '/') {
                    if (op2 == 0) {
                        printf("Why would you ever divide by zero? I'm changing that zero to a one for you, thank me later\n");
                        op2 = 1;
                    }
                    result = op1 / op2;
                } else if (*token == '+') {
                    result = op1 + op2;
                } else if (*token == '-') {
                    result = op1 - op2;
                }
                StackPush(&stax, result);
                //printf("result is %f\n", (double)result);
                //tokenize the next thingie
                token = strtok(NULL, " ");
                valid = 1;
            } else {
                //convert the input into a float if not an operator
                valid++;

                //declare error if token is not a digit
                //printf("this is what you typed: %f",(double)*token);
                //cast token to a float to check ASCII values
                checker = (float) *token;
                if (checker < 48 || checker > 57) {
                    printf("ERROR! UNEXPECTED CHARACTER IN BAGGING AREA (floats and operators only please)\n");
                    error = 1;
                    token = NULL;
                    break;
                }

                //if three numbers appear in a row, its not a valid RPN string, so error
                if (valid >= 3) {
                    printf("ERROR! Not a valid RPN string! (Too many operators before operand)\n");
                    //reset the token to restart the function
                    token = NULL;
                    valid = 0;
                    error = 1;
                    break;
                }
                value = atof(token);
                //printf("You inputted the value: %f\n", (double)value);
                //then push that value onto the stack
                x = StackPush(&stax, value);
                //check if stack is full (if StackPush is not successful, stack is full)
                if (x == 0) {
                    printf("ERROR! Too many operands on the stack!\n");
                    token = NULL;
                    error = 1;
                    break;
                }
                //tokenize the next thing
                token = strtok(NULL, " ");
            }
        }
        //error if extra stuff on the stack at the end (greater than 1 item left))
        if (StackGetSize(&stax) >= 2 || error == 1) {
            error = 1;
            printf("Invalid RPN string, stuff left on stack. Valid strings should end with an operator");
        }

        //Prints an exit message if no error was found
        if (error != 1) {
            StackPop(&stax, &result);
            printf("Final result of RPN string is: %f\n", (double) result);
        }
    }




    /*************************************************************************************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}

/**
 * Extra Credit: Define ProcessBackspaces() here - This function should read through an array of
 * characters and when a backspace character is read it should replace the preceding character with
 * the following character. It should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings that are at
 * least 256 characters in length.
 * @param rpn_sentence The string that will be processed for backspaces. This string is modified in
 *                     place.
 * @return Returns the size of the resultant string in `rpn_sentence`.
 */
int ProcessBackspaces(char *rpn_sentence)
{
    return 0;
}


