#include "Protocol.h"
#include "Board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define BOOLEAN int

//xor variables
static uint8_t xorHash; //return value for the xor helper function

int loop; //used to iterate through loops to clear arrays



//struct for variables necessary for the decode function

struct decodeData {
    char dataRecording[PROTOCOL_MAX_MESSAGE_LEN]; //used to record messages in the decoding function
    char checkSum[2]; //stores the 2 digits of the checksum
    int indexPos; //used in the FSM to determine which char you are on
    uint8_t checkSumResult; //the 8 bit representation of the 2-char CheckSum
    //determines what type of message is being transmitted according to the enum;
    ProtocolParserStatus value;

} decodeData;



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
            decodeData.indexPos = 0;
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
        if (in == '1' || in == '2' || in == '3' || in == '4' || in == '5' || in == '6' ||
                in == '7' || in == '8' || in == '9' || in == '0' || in == 'A' || in == 'C' ||
                in == 'D' || in == 'E' || in == 'H' || in == 'I' || in == 'O' || in == 'T') {
            //read and copy the character to the recording array, and increment loop
            decodeData.dataRecording[decodeData.indexPos] = in;
            decodeData.indexPos++;
            return PROTOCOL_PARSING_GOOD;
            break;
        }//if asterisk is reached, break loop and move to FIRST_CHECKSUM_HALF
        else if (in == '*') {
            currentStatus = FIRST_CHECKSUM_HALF;
            return PROTOCOL_PARSING_GOOD;
            break;
        }//non valid char reached somehow
        else {
            currentStatus = WAITING;
            return PROTOCOL_PARSING_FAILURE;
            break;
        }
        break;
        //stores the first checksum hex char
    case FIRST_CHECKSUM_HALF:
        //checks for hex char (both upper and lower just in case)
        if (in == '1' || in == '2' || in == '3' || in == '4' || in == '5' || in == '6' ||
                in == '7' || in == '8' || in == '9' || in == '0' || in == 'A' || in == 'B' ||
                in == 'C' || in == 'D' || in == 'E' || in == 'F' || in == 'a' || in == 'b' ||
                in == 'c' || in == 'd' || in == 'e' || in == 'f') {

            //stores the first character into checkSum array
            decodeData.checkSum[0] = in;
            currentStatus = SECOND_CHECKSUM_HALF; //progress to next char
            return PROTOCOL_PARSING_GOOD;
            break;
        }//if invalid character, return a FAIL
        else {
            currentStatus = WAITING;
            return PROTOCOL_PARSING_FAILURE;
            break;
        }
        break;
        //checks for the second checksum hex char
    case SECOND_CHECKSUM_HALF:
        if (in == '1' || in == '2' || in == '3' || in == '4' || in == '5' || in == '6' ||
                in == '7' || in == '8' || in == '9' || in == '0' || in == 'A' || in == 'B' ||
                in == 'C' || in == 'D' || in == 'E' || in == 'F' || in == 'a' || in == 'b' ||
                in == 'c' || in == 'd' || in == 'e' || in == 'f') {

            //store the second char
            decodeData.checkSum[1] = in;
            loop = 0;
            uint8_t resultHash, originalHash = 0x00;
            //creates an xor of the original message
            while (decodeData.dataRecording[loop] != NULL) {
                originalHash ^= decodeData.dataRecording[loop]; //xor the original message string
                loop++;
            }
            //according to StackOverflow, this converts an ASCII string to an int
            resultHash = xtoi(decodeData.checkSum);

            //compare the two hashes
            if (originalHash == resultHash) {
                currentStatus = NEWLINE;
                return PROTOCOL_PARSING_GOOD;
                break;
            } else {
                currentStatus = WAITING;
                return PROTOCOL_PARSING_FAILURE;
                break;
            }
        }//if an invalid character is reached, failure
        else {
            currentStatus = WAITING;
            return PROTOCOL_PARSING_FAILURE;
            break;
        }
        break;

        //checks what kind of data is being received, and return appropriately
    case NEWLINE:
        //checks for the newline char
        if (in == '\n') {
            //determine what message has been sent by looking at the first characters
            if (decodeData.dataRecording[0] == 'C' && decodeData.dataRecording[1] == 'O') {

                decodeData.value = PROTOCOL_PARSED_COO_MESSAGE;
            } else if (decodeData.dataRecording[0] == 'H') {

                decodeData.value = PROTOCOL_PARSED_HIT_MESSAGE;
            } else if (decodeData.dataRecording[0] == 'D') {

                decodeData.value = PROTOCOL_PARSED_DET_MESSAGE;
            } else if (decodeData.dataRecording[0] == 'C' && decodeData.dataRecording[1] == 'H') {

                decodeData.value = PROTOCOL_PARSED_CHA_MESSAGE;
            }

            //tokenize strings appropriately
            char *tag, *str1, *str2, *str3; //string pointers for tokens and return values
            if (decodeData.value == PROTOCOL_PARSED_COO_MESSAGE) {
                //tokenize the string into tag, row, col
                tag = strtok(decodeData.dataRecording, ",");
                str1 = strtok(decodeData.dataRecording, ",");
                str2 = strtok(decodeData.dataRecording, ",");

                //put results into GuessData
                gData->row = atoi(str1); //convert string to int
                gData->col = atoi(str2);

            } else if (decodeData.value == PROTOCOL_PARSED_HIT_MESSAGE) {

                //tokenize the string into tag, row, col, hit  
                tag = strtok(decodeData.dataRecording, ",");
                str1 = strtok(decodeData.dataRecording, ",");
                str2 = strtok(decodeData.dataRecording, ",");
                str3 = strtok(decodeData.dataRecording, ",");

                //put results into GuessData
                gData->row = atoi(str1);
                gData->col = atoi(str2);
                gData->hit = atoi(str3);

            } else if (decodeData.value == PROTOCOL_PARSED_DET_MESSAGE) {

                //tokenize the string into tag, guess, encryptionKey
                tag = strtok(decodeData.dataRecording, ",");
                str1 = strtok(decodeData.dataRecording, ",");
                str2 = strtok(decodeData.dataRecording, ",");

                nData->guess = atoi(str1);
                nData->encryptionKey = atoi(str2);
            } else if (decodeData.value == PROTOCOL_PARSED_CHA_MESSAGE) {

                //tokenize the string into tag, encryptedGuess, hash
                tag = strtok(decodeData.dataRecording, ",");
                str1 = strtok(decodeData.dataRecording, ",");
                str2 = strtok(decodeData.dataRecording, ",");

                nData->encryptedGuess = atoi(str1);
                nData->hash = atoi(str2);
            }
            tag = tag; //makes unused variable error go away... its stupid but works
            return decodeData.value;
        }

        break;
        //if an invalid statement is passed in somehow...
    default:
        currentStatus = WAITING;
        return PROTOCOL_PARSING_FAILURE;
        break;

    }

}

void ProtocolGenerateNegotiationData(NegotiationData * data)
{

}

uint8_t ProtocolValidateNegotiationData(const NegotiationData * data)
{

}

TurnOrder ProtocolGetTurnOrder(const NegotiationData *myData, const NegotiationData * oppData)
{

}