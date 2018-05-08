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
    char f = 'f';
    char h = 'h';
    char g = 'g';
    ListItem *one = LinkedListNew(f);
    ListItem *two = LinkedListCreateAfter(one, g);
    ListItem *three = LinkedListCreateAfter(two,h);
    ListItem *four = LinkedListCreateAfter(two, 'i');
    
    ListItem *test = LinkedListNew('m');
    
    int x;
    int y = LinkedListPrint(one);
    x = LinkedListSize(three);
    //compare = CompareStrings(*one, *two);
    printf("\nI did a thing! %d", x);
    printf("\nme test, me smart! %d", y);

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}