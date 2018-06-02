#include "Protocol.h"
#include "Board.h"
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BOOLEAN int

//xor variables
static uint8_t xorHash; //return value for the xor helper function

int loop; //used to iterate through loops to clear arrays

int index; //used in the FSM to determine which char you are on

char dataRecording[PROTOCOL_MAX_MESSAGE_LEN]; //used to record messages in the decoding function

//enum for all states of the decoding FSM

typedef enum {
    WAITING,
    RECORDING,
    FIRST_CHECKSUM_HALF,
    SECOND_CHECKSUM_HALF,
    NEWLINE,
} statusStates;
//status starts with waiting
statusStates currentStatus = WAITING;

//check sum calculator that simply takes in a pointer to a string, and performs an XOR operation

uint8_t CheckSum(char *data)
{
    loop = 0;
    //increments through a loop until a NULL is found (the end of the array))
    while (data[loop] != NULL) {
        //xor operation on every element in array
        xorHash ^= data[loop];
        loop++;
    }
    return xorHash;
}

int ProtocolEncodeCooMessage(char *message, const GuessData *data)
{
    //allocates a temporary array that is the size of max message length
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (temp[loop] != NULL) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"COO,%u,%u"   Coordinate message: row, col
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_COO, data->row, data->col);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 11)
    return 11;
}

int ProtocolEncodeHitMessage(char *message, const GuessData *data)
{
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (temp[loop] != NULL) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"HIT,%u,%u,%u"  Hit message: row, col, hit (see HitStatus)
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_HIT, data->row, data->col, data->hit);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 13)
    return 13;
}

int ProtocolEncodeChaMessage(char *message, const NegotiationData *data)
{
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (temp[loop] != NULL) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"CHA,%u,%u"     Challenge message: encryptedGuess, hash
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_CHA, data->encryptedGuess, data->hash);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 20)
    return 20;
}

int ProtocolEncodeDetMessage(char *message, const NegotiationData *data)
{
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (temp[loop] != NULL) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"DET,%u,%u"  Determine message: guess, encryptionKey
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_DET, data->guess, data->encryptionKey);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 28)
    return 28;
}

ProtocolParserStatus ProtocolDecode(char in, NegotiationData *nData, GuessData *gData)
{
    //determine which status you are currently in
    switch (currentStatus) {
    case WAITING:
        //check for dollar sign to start things off
        if (in == '$') {
            //move to recording as per FSM definition
            currentStatus = RECORDING;
            index = 0;
            return PROTOCOL_PARSING_GOOD;
            break;
        }//if no dollar sign, keep waiting
        else {
            currentStatus = WAITING;
            return PROTOCOL_WAITING;
        }
        break;
        //recording state, takes in all bytes until the asterisk(*) is reached    
    case RECORDING:
        //determines what the message is, breaking if an invalid char is given
        //an invalid char is one that cannot show up in the preconstructed messages
        if (in == '1' || in == '2' || in == '3' || in == '4' || in == '5' || in == '6' || in == '7' ||
                in == '8' || in == '9' || in == '0' || in == 'A' || in == 'C' || in == 'D' ||
                in == 'E' || in == 'H' || in == 'I' || in == 'O' || in == 'T') {
            //read and copy the character to the recording array, and increment loop
            dataRecording[index] = in;
            index++;
            return PROTOCOL_PARSING_GOOD;
            break;
        }//if asterisk is reached, break loop and move to FIRST_CHECKSUM_HALF
        else if (in = '*') {
            currentStatus = FIRST_CHECKSUM_HALF;
            return PROTOCOL_PARSING_GOOD;
        }//non valid char reached somehow
        else {
            return PROTOCOL_PARSING_FAILURE;
        }
        break;
    }
}

void ProtocolGenerateNegotiationData(NegotiationData *data)
{

}

uint8_t ProtocolValidateNegotiationData(const NegotiationData *data)
{

}

TurnOrder ProtocolGetTurnOrder(const NegotiationData *myData, const NegotiationData *oppData)
{

}