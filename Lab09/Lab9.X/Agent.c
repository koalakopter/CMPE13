#include "Agent.h"
#include "Protocol.h"
#include "Field.h"
#include "FieldOled.h"
#include "Oled.h"
#include "Field.h"

//you and your opponents guess and negotiation data
NegotiationData nData;
NegotiationData nData_opp;

GuessData gData;
GuessData gData_opp;

ProtocolParserStatus myStatus;
int agentEvent = AGENT_EVENT_NONE; //flag for current AgentEvent
static AgentState checkState = AGENT_EVENT_NONE;

//turn order
static TurnOrder order = TURN_ORDER_TIE; //starts at TIE to avoid cheating


//creating fields for the player and the enemy
static Field *playerField;
static Field *enemyField;

//Im doing Agent Run and AgentGetEnemyStatus

int AgentRun(char in, char *outBuffer)
{
    myStatus = ProtocolDecode(in, &nData, &gData);
    //check what ProtocolDecode returns and set a flag
    if (in != NULL) {
        if (myStatus == PROTOCOL_PARSING_GOOD) {
            agentEvent = AGENT_EVENT_NONE;
        } else if (myStatus == PROTOCOL_PARSED_CHA_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_CHA_MESSAGE;
        } else if (myStatus == PROTOCOL_PARSED_COO_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_COO_MESSAGE;
        } else if (myStatus == PROTOCOL_PARSED_DET_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_DET_MESSAGE;
        } else if (myStatus == PROTOCOL_PARSED_HIT_MESSAGE) {
            agentEvent = AGENT_EVENT_RECEIVED_HIT_MESSAGE;
        } else {
            //if tne input isn't valid, set an error flag
            agentEvent = AGENT_EVENT_MESSAGE_PARSING_FAILED;
        }
    }

    //follows the state machine logic
    switch (checkState) {
    case AGENT_STATE_GENERATE_NEG_DATA:
        //generate Negotiation data and put it into nData
        ProtocolGenerateNegotiationData(&nData);

        //encode some challenge data
        ProtocolEncodeChaMessage(outBuffer, &nData);
        checkState = AGENT_STATE_SEND_CHALLENGE_DATA;
        return strlen(outBuffer); //returns length of the outBuffer string
        break;

    case AGENT_STATE_SEND_CHALLENGE_DATA:

        //send determine data
        ProtocolEncodeDetMessage(outBuffer, &nData);
        checkState = AGENT_STATE_DETERMINE_TURN_ORDER;
        return strlen(outBuffer);
        break;

    case AGENT_STATE_DETERMINE_TURN_ORDER:

        //validate opponent data, if fail, return error
        ProtocolValidateNegotiationData(&nData_opp);
        if (ProtocolValidateNegotiationData(&nData_opp) == FALSE) {
            checkState = AGENT_STATE_INVALID;
            return AGENT_EVENT_NONE;
            break;
        }
        //if it doesn't fail, proceed as normal
        order = ProtocolGetTurnOrder(&nData, &nData_opp);

        //checks who goes first
        if (order == TURN_ORDER_START) {
            //you go first
            checkState = AGENT_STATE_SEND_GUESS;
            //draw the screen
            FieldOledDrawScreen(playerField, enemyField, FIELD_OLED_TURN_MINE);
        } else if (order == TURN_ORDER_DEFER) {
            //they go first
            checkState = AGENT_STATE_WAIT_FOR_GUESS;
            //draw the screen
            FieldOledDrawScreen(playerField, enemyField, FIELD_OLED_TURN_THEIRS);
        }            //somehow a tie happened
        else {
            checkState = AGENT_STATE_INVALID;
            return AGENT_EVENT_NONE;
            break;
        }
        
        return 0; //returns nothing but indicates a success I think? 
        //outBuffer is not modified here...
        break;

    case AGENT_STATE_SEND_GUESS:
        
        break;
    case AGENT_STATE_WAIT_FOR_HIT:

        break;
    case AGENT_STATE_WAIT_FOR_GUESS:

        break;
        
    //somehow an invalid state happened
    case AGENT_STATE_INVALID:
        
        
        break;
    case AGENT_STATE_LOST:

        break;
    case AGENT_STATE_WON:

        break;

    }
}

void AgentInit(void)
{
    //init of the player and enemy fields
    FieldInit(playerField, FIELD_POSITION_EMPTY);
    FieldInit(enemyField, FIELD_POSITION_UNKNOWN);

    //now for agent placement on its playerField

    int done = FALSE;
    int randRow;
    int randCol;
    int randDir;
    int checkPlacedBoat;
    int boatType = FIELD_BOAT_SMALL;

    while (!done) {
        //here we are getting the modulo of the rand so we ensure that our
        //value is 0-5 for rows, 0-9 for columns, and 0-3 for direction
        randRow = rand() % 7;
        randCol = rand() % 10;
        randDir = rand() % 4;

        switch (boatType) {
        case FIELD_BOAT_SMALL:
            checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                boatType = FIELD_BOAT_MEDIUM;
            }

            break;

        case FIELD_BOAT_MEDIUM:
            checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                boatType = FIELD_BOAT_LARGE;
            }

            break;

        case FIELD_BOAT_LARGE:
            checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                boatType = FIELD_BOAT_HUGE;
            }

            break;

        case FIELD_BOAT_HUGE:
            checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                done = TRUE;
            }

            break;
        }
    }
}

uint8_t AgentGetStatus(void)
{
    return FieldGetBoatStates(playerField);
}

uint8_t AgentGetEnemyStatus(void)
{
    return FieldGetBoatStates(enemyField);
}
