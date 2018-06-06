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
static int x;
static float test;

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
    if (x == 12) {
        test++;
    }

    printf("\ntesting encode HIT message\n");
    gData.hit = 0;
    x = ProtocolEncodeHitMessage(testMessage, &gData);
    printf("Encoded string should have format: HIT,%%u,%%u,%%u\n");
    printf("Encoded string: %sand Length of string: %d\n", testMessage, x);
    if (x == 14) {
        test++;
    }

    printf("\ntesting encode CHA message\n");
    nData.hash = 139;
    nData.encryptedGuess = 54104;
    x = ProtocolEncodeChaMessage(testMessage, &nData);
    printf("Encoded string should have format: CHA,%%u,%%u,\n");
    printf("Encoded string: %sand Length of string: %d\n", testMessage, x);
    if (x == 18) {
        test++;
    }

    printf("\ntesting encode DET message\n");
    nData.encryptionKey = 21382;
    nData.guess = 32990;
    x = ProtocolEncodeDetMessage(testMessage, &nData);
    printf("Encoded string should have format: DET,%%u,%%u,\n");
    printf("Encoded string: %sand Length of string: %d\n", testMessage, x);
    if (x == 20) {
        test++;
    }

    //testing generate and validate negotiation Data
    printf("\nTesting Generate and Validate Negotiation Data\n");
    ProtocolGenerateNegotiationData(&nData);
    x = ProtocolValidateNegotiationData(&nData);
    printf("Generated and validated valid NegotiationData, expect a 1 here for TRUE: %d\n", x);
    if (x == 1) {
        test++;
    }

    //generate invalid negotiationData (please ignore the errors in compilation)
    ProtocolGenerateNegotiationData(&xData);
    xData.hash = 12345; //changed the hash to some random number
    x = ProtocolValidateNegotiationData(&xData);
    printf("Generated an invalid NegotiationData hash key expect a 0 here for FALSE: %d\n", x);
    if (x == 0) {
        test++;
    }

    printf("\nTesting Turn Order (TIE: -1, DEFER: 0, START: 1\n");
    xData.encryptedGuess = 62132;
    xData.encryptionKey = 16067;
    xData.guess = 52343;
    xData.hash = 70;

    ProtocolGenerateNegotiationData(&nData);
    ProtocolGenerateNegotiationData(&xData);

    tOrder = ProtocolGetTurnOrder(&nData, &xData);
    printf("Turn Order: %d\n", tOrder);
    if (tOrder == 0 || tOrder == 1) {
        test++;
    }
    tOrder = ProtocolGetTurnOrder(&xData, &nData);
    printf("Turn Order (Switched): %d\n", tOrder);
    if (tOrder == 1 || tOrder == 0) {
        test++;
    }

    printf("\nTesting decode message function, "
            "refer to enum in Protocol.h for expected output values\n");
    int s = 0;
    int testSwitch = 0;
    while (TRUE) {
        switch (testSwitch) {
        case 0:
            ProtocolEncodeDetMessage(testMessage, &nData);
            printf("\nEncoding the following message: %s", testMessage);
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (expect 5 for PROTOCOL_PARSED_DET_MESSAGE)\n", pStatus);
                }
                if (pStatus == 5) {
                    test++;
                }
                s++;
            }
            testSwitch++;
            break;
        case 1:
            ProtocolEncodeChaMessage(testMessage, &nData);
            printf("\nEncoding the following message: %s", testMessage);
            s = 0;
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (expect 4 for PROTOCOL_PARSED_DET_MESSAGE)\n", pStatus);
                }
                if (pStatus == 4) {
                    test++;
                }
                s++;
            }
            testSwitch++;
            break;
        case 2:
            ProtocolEncodeCooMessage(testMessage, &gData);
            printf("\nEncoding the following message: %s", testMessage);
            s = 0;
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (expect 2 for PROTOCOL_PARSED_COO_MESSAGE)\n", pStatus);
                }
                if (pStatus == 2) {
                    test++;
                }
                s++;
            }
            testSwitch++;
            break;
        case 3:

            ProtocolEncodeHitMessage(testMessage, &gData);
            printf("\nEncoding the following message: %s", testMessage);
            s = 0;
            while (testMessage[s] != NULL) {
                pStatus = ProtocolDecode(testMessage[s], &nData, &gData);
                if (testMessage[s + 1] == NULL) {
                    printf("DECODE STATUS: %d (expect 3 for PROTOCOL_PARSED_HIT_MESSAGE)\n", pStatus);
                }
                if (pStatus == 3) {
                    test++;
                }
                s++;
            }
            testSwitch++;
            break;
        default:
            printf("\n%d out of 12 tests passed\n", (int)test);
            test = (test/12.0) * 100.0;
            printf("\n%.2f out of 100%% tests passed", (double)test);
            while(1);
            break;
        }
    }
    
    
    /******************************************************************************
     * Your code goes in between this comment and the preceeding one with asterisks
     *****************************************************************************/

    while (1);
}