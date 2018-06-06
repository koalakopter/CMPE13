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
NegotiationData xData; //for invalid ValidateNegotiationData and other testing
ProtocolParserStatus pStatus;
TurnOrder tOrder;

char testMessage[PROTOCOL_MAX_PAYLOAD_LEN];
int x;

int main()
{
    BOARD_Init();



    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    printf("\nTest harness for CMPE 13 Lab 9 Protocol.c\n");
    printf("Testing Encode Message according to Lab Manual example outputs\n");

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

    //testing generate and validate negotiation Data
    printf("\nTesting Generate and Validate Negotiation Data\n");
    ProtocolGenerateNegotiationData(&nData);
    x = ProtocolValidateNegotiationData(&nData);
    printf("Generated and validated valid NegotiationData, expect a 1 here for TRUE: %d\n", x);

    //generate invalid negotiationData (please ignore the errors in compilation)
    ProtocolGenerateNegotiationData(&xData);
    xData.hash = 12345; //changed the hash to some random number
    x = ProtocolValidateNegotiationData(&xData);
    printf("Generated an invalid NegotiationData hash key expect a 0 here for FALSE: %d\n", x);

    printf("\nTesting Turn Order (-1: TIE, 0: DEFER, 1: START\n");
    xData.encryptedGuess = 62132;
    xData.encryptionKey = 16067;
    xData.guess = 52343;
    xData.hash = 70;

    ProtocolGenerateNegotiationData(&nData);
    ProtocolGenerateNegotiationData(&xData);

    tOrder = ProtocolGetTurnOrder(&nData, &xData);
    printf("Turn Order: %d\n", tOrder);
    tOrder = ProtocolGetTurnOrder(&xData, &nData);
    printf("Turn Order (Switched): %d\n", tOrder);


    printf("\nTesting decode message function\n");
    int s = 0;
    int testSwitch = 0;
    while (TRUE) {
        switch (testSwitch) {
        case 0:
            ProtocolEncodeDetMessage(testMessage, &nData);
            printf("\n%s", testMessage);
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (0 means PROTOCOL_WAITING)\n", pStatus);
                }
                s++;
            }
            testSwitch++;
            break;
        case 1:
            ProtocolEncodeChaMessage(testMessage, &nData);
            printf("\n%s", testMessage);
            s = 0;
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (0 means PROTOCOL_WAITING)\n", pStatus);
                }
                s++;
            }
            testSwitch++;
            break;
        case 2:
            ProtocolEncodeCooMessage(testMessage, &gData);
            printf("\n%s", testMessage);
            s = 0;
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (0 means PROTOCOL_WAITING)\n", pStatus);
                }
                s++;
            }
            testSwitch++;
            break;
        case 3:
            ProtocolEncodeHitMessage(testMessage, &gData);
            printf("\n%s", testMessage);
            s = 0;
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (0 means PROTOCOL_WAITING)\n", pStatus);
                }
                s++;
            }
            testSwitch++;
            break;
        default:
            break;
        }
    }
    /******************************************************************************
     * Your code goes in between this comment and the preceeding one with asterisks
     *****************************************************************************/

    while (1);
}