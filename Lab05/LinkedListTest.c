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
    static char *dog = "dog"; //testing code from sort.c
    char ijn[20] = "Yamato";
    char kms[20] = "Bismarck";
    char usn[20] = "Iowa";
    char rn[20] = "King_George_V";
    
    ListItem *one = LinkedListNew(ijn);
    ListItem *two = LinkedListCreateAfter(one, kms);
    ListItem *three = LinkedListCreateAfter(two, rn);
    ListItem *four = LinkedListCreateAfter(two, usn);
    
    ListItem *five = LinkedListCreateAfter(three, dog);

    int y = LinkedListPrint(one);
    int x = LinkedListSize(three);
    

    int a = CompareStrings(one, two);
    printf("ASASHIO IS GUD IN RANKED? %d", a);

    LinkedListSwapData(one, four);
    //LinkedListPrint(one);
    

    //test the print
    LinkedListSort(one);
    LinkedListPrint(one);

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}