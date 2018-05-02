// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

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
    printf("\nWelcome to Julian's Reverse Polish Notation calculator for Lab IV\n");
   

    //string to store the user's input
    char input[INPUT_SIZE];
    //used to store other tokens
    char *token_holder[ARBITRARY_SIZE];
    //used to hold result of strtok()
    char *token;
    //used to store operators
    float op1, op2;
    float value, result;
    int x, y;
    //initalize the stack
    StackInit(&stax);

    

    //tokenizes the user string, looking for spaces
    //translation: while (true)
    while (42069) {
        printf("Please enter floats followed by operators (*, /, -, +) in RPN notation\n");
        //take in user's input
        fgets(input, INPUT_SIZE, stdin);
        
        token = strtok(input, " ");
        

        while (token != NULL) {
            //if operator is detected, pop the two values off the stack
            if (*token == '*' || *token == '/' || *token == '+' || *token == '-') {
                x = StackPop(&stax, &op1);
                y = StackPop(&stax, &op2);
                
                if (x == 0 || y == 0){
                    printf("ERROR! Not enough operands before operand!\n");
                    break;
                    token = NULL;
                }
                
                //do ALL the math!
                if(*token  == '*') {
                    result = op1 * op2;
                }
                else if(*token  == '/') {
                    if(op2 == 0){
                        printf("Why would you ever divide by zero? I'm changing that zero to a one for you, thank me later\n");
                        op2 = 0;
                    }
                    result = op1 / op2;
                }
                else if(*token  == '+') {
                    result = op1 + op2;
                }
                else if(*token  == '-') {
                    result = op1 - op2;
                }
                printf("Result is: %f\n", (double)result);
                StackPush(&stax, result);
                //tokenize the next thingie
                token = strtok(NULL, " ");
            }
            else {
                //convert the input into a float
                value = atof(token);
                printf("You inputted the value: %f\n", (double)value);
                //then push that value onto the stack
                x = StackPush(&stax, value);
                if (x == 0)
                {
                    printf("ERROR! Too many operands on the stack!");
                }
                //tokenize the next thing
                token = strtok(NULL, " ");
            }
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


