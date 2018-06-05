// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Protocol.h"
#include "Ascii.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdio.h>

// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****


// **** Declare any function prototypes here ****
GuessData gData;
NegotiationData nData;

char testMessage[PROTOCOL_MAX_PAYLOAD_LEN];
int x;


int main()
{
    BOARD_Init();



/******************************************************************************
 * Your code goes in between this comment and the following one with asterisks.
 *****************************************************************************/
    printf("\nTest harness for CMPE 13 Lab 9 Protocol.c\n");
    
    printf("testing encode message\n");
    gData.row = 1;
    gData.col = 1;
    //address of gData passed into function as argument
    ProtocolEncodeCooMessage(testMessage, &gData);

/******************************************************************************
 * Your code goes in between this comment and the preceeding one with asterisks
 *****************************************************************************/

    while (1);
}