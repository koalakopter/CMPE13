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
    ListItem *six = LinkedListCreateAfter(four, "Vittorio Veneto");
    
    //BEGIN TESTING FRAMEWORK
    //test print function
    printf("Test PRINT Function: expect Yamato, Bismarck, Dog, King_George_V, Iowa, Vittorio Veneto\n");
    LinkedListPrint(one);
    
    //test size function
    int x = LinkedListSize(three);
    printf("SIZE OF LIST IS: %d, we expect '5'\n", x);
    
    //test swap data function
    LinkedListSwapData(four, two);
    printf("SWAPPED data four(Iowa), and two (Bismarck), expect those swapped in the following test:\n");
    LinkedListPrint(two);
    
    //test Remove function
    LinkedListRemove(six);
    printf("REMOVED Vittorio Veneto from list\n");
    LinkedListPrint(five);
    
    //test sort function
    LinkedListSort(one);
    printf("SORTED list: Expected: Dog, Iowa, Yamato, Bismarck, KGV\n");
    LinkedListPrint(one);
    

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}