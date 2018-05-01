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
int test1, test2, test3, test4;

int main()
{
    BOARD_Init();

    /******************************** Your custom testing code goes below here ***********************/
    printf("\nWelcome to CMPE13 Stack Unit Testing for JULIAN TO, jcto. Replace XXX with your cruzID and name.\r\n");
    //initialize a stack
    StackInit(&testStack);
    //check if empty
    int empty = StackIsEmpty(&testStack);
    printf("Is it empty? %d (0 if false, 1 if true, should be 1)\n", empty);
    if (empty == 1) {
        test1++;
    }
    
    //check if stack is full
    int full = StackIsFull(&testStack);
    printf("Is it full? %d (0 if false, 1 if true, should be 0 since last test said empty)\n", full);
    if (full == 0) {
        test2++;
    }
    
    //check StackPush function
    int x = StackPush(&testStack, wombat);
    StackPush(&testStack, 69);
    printf("Did it push correctly? %d (1 means yes, 0 means no, hopefully outputs 1 here) \n", x);

    if (x == 1) {
        test3++;
    }
    
    //check StackPop function
    float koala;
    int y = StackPop(&testStack, &koala);
    printf("VALUE POPPED IS: %f should be 69 \n", (double)koala);

    if (y == 1) {
        test4++;
        printf("pop successful!\n");
    }

    
    x = StackPush(&testStack, 12);
    printf("Did it push correctly? %d(1 means yes, 0 means no, hopefully outputs 1 here)\n", x);
    if (x == 1) {
        test3++;
    }

    StackPush(&testStack, 7);
    StackPush(&testStack, 1941);
    int kangaroo = StackGetSize(&testStack);

    printf("Size of stack is: %d (EXCPECT 4 SINCE I PUSHED 2, POPPED 1, AND THEN PUSHED 3\n", kangaroo);
    int loop;
    float dingo;
    for (loop = 4; loop < 20; loop++) {
        dingo++;
        StackPush(&testStack, dingo);
    }
    full = StackIsFull(&testStack);
    printf("Is it full? %d (0 if false, 1 if true, should be true because of the for loop)\n", full);
    if (full == 1) {
        test2++;
    }
    empty = StackIsEmpty(&testStack);
    printf("Is it empty? %d (0 if false, 1 if true, should be 0 since there is stuff in it)\n", empty);
    if (empty == 0) {
        test1++;
    }
    
    y = StackPop(&testStack, &koala);
    if (y == 1) {
        test4++;
        printf("pop successful!");
    }
    
    printf("\n\nStackEmpty: tests passed: %d / 2", test1);
    printf("\n\nStackFull: tests passed: %d / 2", test2);
    printf("\n\nStackPush: tests passed: %d / 2", test3);
    printf("\n\nStackPop: tests passed: %d / 2", test4);
    
    float final = test1 + test2 + test3 + test4 + 0.0;
    final = (final/8)*100;
    printf("\nFinal Tally: %f %% passed", (double)final);



    /*************************************************************************************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}
