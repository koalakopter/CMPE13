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
    
    printf("\ntesting encode COO message\n");
    gData.row = 0;
    gData.col = 2;
    //address of gData passed into function as argument
    x = ProtocolEncodeCooMessage(testMessage, &gData);
    printf("Encoded string should have format: COO,%%u,%%u\n");
    printf("Encoded string: %sand Length of string: %d\n", testMessage, x);
    
    printf("\ntesting encode HIT message\n");
    gData.hit = 0;
    x = ProtocolEncodeHitMessage(testMessage, &gData);
    printf("Encoded string should have format: HIT,%%u,%%u,%%u\n");
    printf("Encoded string: %sand Length of string: %d\n", testMessage, x);
    
    printf("\ntesting encode CHA message\n");
    nData.hash = 139;
    nData.encryptedGuess = 54104;
    x = ProtocolEncodeChaMessage(testMessage, &nData);
    printf("Encoded string should have format: CHA,%%u,%%u,\n");
    printf("Encoded string: %sand Length of string: %d\n", testMessage, x);
    
    printf("\ntesting encode DET message\n");
    nData.encryptionKey = 21382;
    nData.guess = 32990;
    x = ProtocolEncodeDetMessage(testMessage, &nData);
    printf("Encoded string should have format: DET,%%u,%%u,\n");
    printf("Encoded string: %sand Length of string: %d\n", testMessage, x);

/******************************************************************************
 * Your code goes in between this comment and the preceeding one with asterisks
 *****************************************************************************/

    while (1);
}