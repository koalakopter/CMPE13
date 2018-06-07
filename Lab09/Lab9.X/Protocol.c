/*
 * Julian To -- jcto@ucsc.edu
 * Lab09 - Battle boats
 * June 1, 2018 
 */

#include "Protocol.h"
#include "Board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define BOOLEAN int

//short hand for checking chars (makes stuff look cleaner)
#define VALID_CHAR in == '1' || in == '2' || in == '3' || in == '4' || in == '5' || in == '6' || \
                in == '7' || in == '8' || in == '9' || in == '0' || in == 'A' || in == 'C' || \
                in == 'D' || in == 'E' || in == 'H' || in == 'I' || in == 'O' || in == 'T' || in == ',' 

#define VALID_HEX in == '1' || in == '2' || in == '3' || in == '4' || in == '5' || in == '6' || \
                in == '7' || in == '8' || in == '9' || in == '0' || in == 'A' || in == 'B' || \
                in == 'C' || in == 'D' || in == 'E' || in == 'F' || in == 'a' || in == 'b' || \
                in == 'c' || in == 'd' || in == 'e' || in == 'f'

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
    loop = 0; //clear loop and xorhash
    xorHash = 0;
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
    loop = 0;
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (loop < PROTOCOL_MAX_MESSAGE_LEN) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"COO,%u,%u"   Coordinate message: row, col
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_COO, data->row, data->col);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 11)
    return strlen(message);
}

int ProtocolEncodeHitMessage(char *message, const GuessData *data)
{
    loop = 0;
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (loop < PROTOCOL_MAX_MESSAGE_LEN) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"HIT,%u,%u,%u"  Hit message: row, col, hit (see HitStatus)
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_HIT, data->row, data->col, data->hit);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 13)
    return strlen(message);
}

int ProtocolEncodeChaMessage(char *message, const NegotiationData *data)
{
    loop = 0;
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (loop < PROTOCOL_MAX_MESSAGE_LEN) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"CHA,%u,%u"     Challenge message: encryptedGuess, hash
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_CHA, data->encryptedGuess, data->hash);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 20)
    return strlen(message);
}

int ProtocolEncodeDetMessage(char *message, const NegotiationData *data)
{
    loop = 0;
    char temp[PROTOCOL_MAX_MESSAGE_LEN];
    while (loop < PROTOCOL_MAX_MESSAGE_LEN) {
        temp[loop] = NULL; //sets every element to NULL
        loop++;
    }
    //"DET,%u,%u"  Determine message: guess, encryptionKey
    //puts the formatted string into string 'temp'
    sprintf(temp, PAYLOAD_TEMPLATE_DET, data->guess, data->encryptionKey);

    //compiles the final output string into message using calculated XOR values
    sprintf(message, MESSAGE_TEMPLATE, temp, CheckSum(temp));

    //returns length of string (its 28)
    return strlen(message);
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
            //set some stuff to default values
            decodeData.indexPos = 0;
            int sloop = 0;
            //clear the storage message array
            while(sloop < PROTOCOL_MAX_MESSAGE_LEN)
            {
                decodeData.dataRecording[sloop] = NULL;
                sloop++;
            }
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
        //an invalid char is one that cannot show up in the pre-constructed messages
        if (VALID_CHAR) {
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
        if (VALID_HEX) {

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
        if (VALID_HEX) {
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
            decodeData.value = NULL;
            if (decodeData.dataRecording[0] == 'C' && decodeData.dataRecording[1] == 'O') {

                decodeData.value = PROTOCOL_PARSED_COO_MESSAGE;
            } else if (decodeData.dataRecording[0] == 'H' && decodeData.dataRecording[1] == 'I') {

                decodeData.value = PROTOCOL_PARSED_HIT_MESSAGE;
            } else if (decodeData.dataRecording[0] == 'D' && decodeData.dataRecording[1] == 'E' ) {

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
            currentStatus = WAITING; //go back to default state
            return decodeData.value;
        }
        decodeData.indexPos = 0;
        break;
        //if an invalid statement is passed in somehow...
    default:
        currentStatus = WAITING;
        return PROTOCOL_PARSING_FAILURE;
        break;

    }
    //I have no idea how you got here (please stay out)
    return PROTOCOL_PARSING_FAILURE;

}

void ProtocolGenerateNegotiationData(NegotiationData * data)
{
    uint8_t temp; //creates a temp placeholder
    //random keys
    data->guess = (rand()&0x0FFFF);
    data->encryptionKey = (rand()&0x0FFFF);

    //xor the guess with the encryption key
    data->encryptedGuess = ((data->guess) ^ (data->encryptionKey));

    //bit shift right by 8 bits to since the generated number is a 16 bit field
    temp = ((data->guess) >> 8);
    //then xor it
    temp ^= (data->guess);

    //same thing here , shift right by 8 bits so 16bits -> 8
    temp ^= ((data->encryptionKey) >> 8);
    temp ^= ((data->encryptionKey));

    //store the result to hash
    data->hash = temp;
}

uint8_t ProtocolValidateNegotiationData(const NegotiationData * data)
{
    uint8_t check;
    //uses the same formula as before to validate the guess
    //xor check with guess, after shifting guess up right 8 bits
    check = ((data->guess) >> 8);
    check ^= (data->guess);

    check ^= ((data->encryptionKey) >> 8);
    check ^= (data-> encryptionKey);

    if (check == (data->hash)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

TurnOrder ProtocolGetTurnOrder(const NegotiationData *myData, const NegotiationData * oppData)
{
    //determine who goes first by comparing keys
    uint16_t compare = ((oppData->encryptionKey) ^ (myData->encryptionKey));
    //if the two fields OR'd is 1, if guess A > guess B, A goes first
    if ((compare & 1) == 1) {
        if (myData->encryptionKey > oppData->encryptionKey) {
            return TURN_ORDER_START;
        } else if (myData->encryptionKey < oppData->encryptionKey) {
            return TURN_ORDER_DEFER;
        } else {
            return TURN_ORDER_TIE;
        }
    }        //if the two fields OR'd is 0, if guess A > guess B, B goes first
    else {
        if (myData->encryptionKey < oppData->encryptionKey) {
            return TURN_ORDER_START;
        } else if (myData->encryptionKey > oppData->encryptionKey) {
            return TURN_ORDER_DEFER;
        } else {
            return TURN_ORDER_TIE;
        }
    }
}