// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "LinkedList.h"


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****

// **** Declare any function prototypes here ****

int main()
{
    BOARD_Init();
    printf("\r\nWelcome to the LinkedList testing suite\r\n");
    //
    // Your testing code goes after here
    //
    //testing code, WW2 Era battleships + dog
    static char *dog = "Dog"; //testing code from sort.c
    char ijn[20] = "Yamato";
    char km[20] = "Bismarck";
    char usn[20] = "Iowa";
    char rn[20] = "King_George_V";
    
    ListItem *one = LinkedListNew(ijn);
    ListItem *two = LinkedListCreateAfter(one, km);
    ListItem *three = LinkedListCreateAfter(two, rn);
    ListItem *four = LinkedListCreateAfter(three, usn);
    ListItem *five = LinkedListCreateAfter(two, dog);
    ListItem *six = LinkedListCreateAfter(four, "Littorio");
    
    //haha the swiss don't have a navy XD TOPKEK
    ListItem *swissNavy = LinkedListCreateAfter(six, NULL);
    
    
    //BEGIN TESTING FRAMEWORK
    printf("\nSTART OF TESTING\n");
    //test print function
    printf("Test PRINT Function: expect Yamato, Bismarck, Dog, King_George_V, Iowa, Littorio, NULL\n");
    LinkedListPrint(one);
    //printf("COMPARE STRINGSSS %d\n", CompareStrings(four, two));
    
    //test size function
    int x = LinkedListSize(three);
    printf("SIZE OF LIST IS: %d, we expect '7'\n", x);
    
    //test swap data function
    LinkedListSwapData(four, two);
    printf("\nSWAPPED data four(Iowa), and two (Bismarck), expect those swapped in the following test:");
    LinkedListPrint(two);
    
    //test Remove function
    LinkedListRemove(one);
    printf("\nREMOVED Yamato from list");
    LinkedListPrint(five);
    
    //test sort function
    LinkedListSort(two);
    printf("SORTED list: Expected: NULL, Dog, Iowa, Bismarck, Littorio, KGV\n");
    LinkedListPrint(two);
    
    LinkedListRemove(four);
    printf("\n(2nd test) REMOVED Bismarck from list");
    LinkedListPrint(five);
    
    //test GetFirst Function
    one = LinkedListGetFirst(swissNavy);
    printf("Testing the GetFirst() function, expect 'NULL' after sort: %s\n", one->data);
    
    x = LinkedListSize(three);
    printf("SIZE OF LIST IS: %d, after two removals, we expect '5'\n", x);
    

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}