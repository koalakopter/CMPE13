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

// **** Declare function prototypes ****


// This code will unit test the Stack.c implementation. You should run at least two different tests
// on each function to be able to determine if it is working correctly. You will have to write these
// tests yourself.

//just testing variables
struct Stack testStack;
float wombat = 56;

int main()
{
    BOARD_Init();

    /******************************** Your custom testing code goes below here ***********************/
    printf("\nWelcome to CMPE13 Stack Unit Testing for JULIAN TO, jcto. Replace XXX with your cruzID and name.\r\n");
    StackInit(&testStack);
    int empty = StackIsEmpty(&testStack);
    printf("Is it empty? %d (0 if false, 1 if true, should be 1)\n", empty);
    int full = StackIsFull(&testStack);
    printf("Is it full? %d (0 if false, 1 if true, should be 0 since last test said empty)\n", full);

    int x = StackPush(&testStack, wombat);
    StackPush(&testStack, 69);
    printf("Did it push correctly? (1 means yes, 0 means no, hopefully outputs 1 here) %d\n", x);

    float koala;
    int y = StackPop(&testStack, &koala);
    printf("VALUE POPPED IS: %f should be 69 \n", koala);
    
    StackPush(&testStack, 12);
    StackPush(&testStack, 7);
    StackPush(&testStack, 1941);
    int kangaroo = StackGetSize(&testStack);
    
    printf("Size of stack is: %d (EXCPECT 4 SINCE I PUSHED 2, POPPED 1, AND THEN PUSHED 3\n", kangaroo);
    int loop;
    float dingo;
    for(loop = 4; loop < 20; loop++)
    {
        dingo++;
        StackPush(&testStack, dingo);
    }
    full = StackIsFull(&testStack);
    printf("Is it full? %d (0 if false, 1 if true, should be true because of the for loop)\n", full);
    empty = StackIsEmpty(&testStack);
    printf("Is it empty? %d (0 if false, 1 if true, should be 0 since there is stuff in it)\n", empty);
    


    /*************************************************************************************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}
