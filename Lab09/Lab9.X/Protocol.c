#include "Protocol.h"
#include "Board.h"
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BOOLEAN int

//xor variables
uint8_t xorHash; //return value for the xor helper function

int loop; //used to iterate through loops to clear arrays


//check sum calculator that simply takes in a pointer to a string, and performs an XOR operation
uint8_t CheckSum(char *data)
{
    loop = 0;
    //increments through a loop until a NULL is found (the end of the array))
    while(data[loop] != NULL)
    {
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
    while(temp[loop] != NULL)
    {
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
    
}

int ProtocolEncodeChaMessage(char *message, const NegotiationData *data)
{
    
}

int ProtocolEncodeDetMessage(char *message, const NegotiationData *data)
{
    
}


ProtocolParserStatus ProtocolDecode(char in, NegotiationData *nData, GuessData *gData)
{
    
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