#include "Agent.h"
#include "Protocol.h"
#include "Field.h"
#include "FieldOled.h"
#include "Oled.h"
#include "Field.h"

#include <stdio.h>
#include <stdlib.h>

//you and your opponents guess and negotiation data
static NegotiationData nData;
static NegotiationData nData_opp;

static GuessData gData;
static GuessData gData_opp;

static ProtocolParserStatus myStatus;
static int agentEvent = AGENT_EVENT_NONE; //flag for current AgentEvent
static AgentState checkState = AGENT_EVENT_NONE;

//turn order
static TurnOrder order = TURN_ORDER_TIE; //starts at TIE to avoid cheating

//creating fields for the player and the enemy
static Field *playerField;
static Field *enemyField;

//used to randomly generate rows and columns with rand()
static int randRow;
static int randCol;
static int alreadyGuessed[6][10]; //2d array to keep track of what has been guessed, 6 rows, 10 columns

static int time; //for the delay

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
            //if the input isn't valid, set an error flag and commit code-sudoku
            OledClear(0);
            OledDrawString("ERROR_STRING_PARSING");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;
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

            //clear the OLED
            OledClear(0);
            OledDrawString("ERROR_STRING_NEG_DATA");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;
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
        } else { //somehow a tie happened
            OledClear(0);
            OledDrawString("ERROR_STRING_ORDERING");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;
            break;
        }

        return 0; //returns nothing but indicates a success I think? 
        //outBuffer is not modified here...
        break;

    case AGENT_STATE_SEND_GUESS:
        //randomly generate a guess until one that hasn't been guessed already is given
        while (TRUE) {
            for (time = 0; time < BOARD_GetPBClock() / 8; time++) {
                //artificial delay
            }
            randRow = rand() % 7;
            randCol = rand() % 10;
            //pass guess into gData struct
            gData.col = randCol;
            gData.row = randRow;
            if (alreadyGuessed[randRow][randCol] != TRUE) {
                //set a flag so that we can't guess that square again
                alreadyGuessed[randRow][randCol] = TRUE;
                break;
            }
        }
        //encode a message
        ProtocolEncodeCooMessage(outBuffer, &gData);
        checkState = AGENT_STATE_WAIT_FOR_HIT; //move onto checking for hit
        return strlen(outBuffer);
        break;
    case AGENT_STATE_WAIT_FOR_HIT:
        //decode enemy data about hit
        //first check to make sure hit message is recieved
        if (agentEvent == AGENT_EVENT_RECEIVED_HIT_MESSAGE) {
            //check if there was a hit
            FieldUpdateKnowledge(enemyField, &gData_opp);
            //check if you won (0 means no boats left)
            if (AgentGetEnemyStatus() == 0);
            {
                FieldOledDrawScreen(playerField, enemyField, FIELD_OLED_TURN_NONE);
                checkState = AGENT_STATE_WON;
            }
            if (AgentGetEnemyStatus() != 0) {
                //update screen, wait for opponent turn
                FieldOledDrawScreen(playerField, enemyField, FIELD_OLED_TURN_THEIRS);
                checkState = AGENT_STATE_WAIT_FOR_GUESS;
            }

        } else {
            //if something else is received, commit code sudoku
            OledClear(0);
            OledDrawString("ERROR_STRING_PARSING");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;
            break;
        }
        return 0;
        break;
    case AGENT_STATE_WAIT_FOR_GUESS:
        //decode enemy data about opponent guess
        //first check to make sure hit message is received
        if (agentEvent == AGENT_EVENT_RECEIVED_COO_MESSAGE) {
            //check if there was a hit
            FieldUpdateKnowledge(enemyField, &gData_opp);
            //check if you won (0 means no boats left)
            if (AgentGetStatus() == 0);
            {
                FieldOledDrawScreen(playerField, enemyField, FIELD_OLED_TURN_NONE);
                checkState = AGENT_STATE_LOST;
            }
            if (AgentGetStatus() != 0) {
                //update screen, wait for opponent turn
                FieldOledDrawScreen(playerField, enemyField, FIELD_OLED_TURN_THEIRS);
                checkState = AGENT_STATE_SEND_GUESS;
            }

        } else {
            //if something else is received, commit code sudoku
            OledClear(0);
            OledDrawString("ERROR_STRING_PARSING");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;
            break;
        }
        return 0;
        break;

        //somehow an invalid state happened
    case AGENT_STATE_INVALID:

        printf("wahhh we broke! :P\n");
        while (1);
        break;
    case AGENT_STATE_LOST:
        //you lost (sorry man)
        printf("\n'It is well war is so terrible, "
                "otherwise we should grow to fond of it' -Robert E. Lee\n");
        return 0;
        break;
    case AGENT_STATE_WON:
        //you won (don't do anything next?)
        printf("\n'War is cruelty. There is no use trying to reform it. "
                "The crueler it is, the sooner it will be over.' -William Tecumseh Sherman\n");
        return 0;
        break;

    }
    return 0;
}

void AgentInit(void)
{
    //init of the player and enemy fields
    FieldInit(playerField, FIELD_POSITION_EMPTY);
    FieldInit(enemyField, FIELD_POSITION_UNKNOWN);

    //now for agent placement on its playerField

    int done = FALSE;
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
