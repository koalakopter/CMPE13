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
static AgentState checkState = AGENT_STATE_GENERATE_NEG_DATA;

//turn order
static TurnOrder order = TURN_ORDER_TIE; //starts at TIE to avoid cheating

//creating fields for the player and the enemy
static Field playerField;
static Field enemyField;

//used to randomly generate rows and columns with rand()
static int randRow;
static int randCol;
static int alreadyGuessed[6][10]; //2d array to keep track of what has been guessed, 6 rows, 10 columns

static int time; //for the delay
static int returnVal;
static char bleh[50];

void AgentInit(void)
{

    //init of the player and enemy fields
    FieldInit(&playerField, FIELD_POSITION_EMPTY);
    FieldInit(&enemyField, FIELD_POSITION_UNKNOWN);

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
            checkPlacedBoat = FieldAddBoat(&playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                boatType = FIELD_BOAT_MEDIUM;
            }

            break;

        case FIELD_BOAT_MEDIUM:
            checkPlacedBoat = FieldAddBoat(&playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                boatType = FIELD_BOAT_LARGE;
            }

            break;

        case FIELD_BOAT_LARGE:
            checkPlacedBoat = FieldAddBoat(&playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                boatType = FIELD_BOAT_HUGE;
            }

            break;

        case FIELD_BOAT_HUGE:
            checkPlacedBoat = FieldAddBoat(&playerField, randRow, randCol, randDir, boatType);

            if (checkPlacedBoat) {
                done = TRUE;
            }

            break;
        }
    }
    FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_NONE);
    for (time = 0; time < BOARD_GetPBClock() / 8; time++) {
        //artificial delay
    }
}

//Im doing Agent Run and AgentGetEnemyStatus

int AgentRun(char in, char *outBuffer)
{
    myStatus = ProtocolDecode(in, &nData_opp, &gData_opp);

    //check what ProtocolDecode returns and set a flag
    if (in != NULL) {

        if (myStatus == PROTOCOL_PARSING_GOOD || myStatus == PROTOCOL_WAITING) {
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
            /*//if the input isn't valid, set an error flag and commit code-sudoku
            //printf("fuck me");
            OledClear(0);
            OledDrawString("ERROR_STRING_PARSING");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;*/
            agentEvent = AGENT_EVENT_MESSAGE_PARSING_FAILED;
        }
    }

    //follows the state machine logic
    switch (checkState) {
    case AGENT_STATE_GENERATE_NEG_DATA:
        //generate Negotiation data and put it into nData
        ProtocolGenerateNegotiationData(&nData);

        //encode some challenge data
        returnVal = ProtocolEncodeChaMessage(outBuffer, &nData);
        checkState = AGENT_STATE_SEND_CHALLENGE_DATA;
        return returnVal; //returns length of the outBuffer string
        break;

    case AGENT_STATE_SEND_CHALLENGE_DATA:

        //send determine data
        if (AGENT_EVENT_RECEIVED_CHA_MESSAGE == agentEvent) {
            returnVal = ProtocolEncodeDetMessage(outBuffer, &nData);
            checkState = AGENT_STATE_DETERMINE_TURN_ORDER;
            //agentEvent = AGENT_EVENT_NONE;
            //puts("really?");
            return returnVal;
            break;
        } else if (AGENT_EVENT_NONE == agentEvent) {
            //puts("#########");
            return 0;
        } else {
            printf("???????");
            checkState = AGENT_STATE_INVALID;
            return 0;
            break;
        }

    case AGENT_STATE_DETERMINE_TURN_ORDER:

        if (agentEvent & AGENT_EVENT_NONE || agentEvent & AGENT_EVENT_RECEIVED_CHA_MESSAGE) {
            puts("^^^^^^^^^");
            return 0;
        } else if (agentEvent & AGENT_EVENT_RECEIVED_DET_MESSAGE) {
            puts("please?");

            //continue on
        } else if (agentEvent & AGENT_EVENT_MESSAGE_PARSING_FAILED) {
            puts("!!!!!!!!!");
            checkState = AGENT_STATE_INVALID;
            return 0;
        } else {
            puts("@@@@@@@@@");
            //checkState = AGENT_STATE_INVALID;
            return 0;
        }
        //validate opponent data, if fail, return error
        agentEvent = AGENT_EVENT_NONE;
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
            puts("start");
            checkState = AGENT_STATE_SEND_GUESS;
            //draw the screen
            FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_MINE);
        } else if (order == TURN_ORDER_DEFER) {
            //they go first
            puts("not me");
            checkState = AGENT_STATE_WAIT_FOR_GUESS;
            //draw the screen
            FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_THEIRS);
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
        FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_MINE);
        //randomly generate a guess until one that hasn't been guessed already is given

        //puts("WEEEE");
        for (time = 0; time < BOARD_GetPBClock() / 8; time++) {
            //artificial delay
        }
        while (TRUE) {
            randRow = rand() % FIELD_ROWS;
            randCol = rand() % FIELD_COLS;
            //pass guess into gData struct

            if (alreadyGuessed[randRow][randCol] != TRUE) {
                //set a flag so that we can't guess that square again
                sprintf(bleh, "meme row: %d and row %d", randRow, randCol);
                //puts(bleh);
                alreadyGuessed[randRow][randCol] = TRUE;
                gData.col = randCol;
                gData.row = randRow;
                break;
            }
        }
        //encode a message
        returnVal = ProtocolEncodeCooMessage(outBuffer, &gData);
        checkState = AGENT_STATE_WAIT_FOR_HIT; //move onto checking for hit
        return returnVal;
        break;
    case AGENT_STATE_WAIT_FOR_HIT:
        FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_MINE);
        //decode enemy data about hit
        //first check to make sure hit message is recieved
        if (agentEvent == AGENT_EVENT_RECEIVED_HIT_MESSAGE) {
            //check if there was a hit
            agentEvent = AGENT_EVENT_NONE;  
            //puts("yurr durr");
            FieldUpdateKnowledge(&enemyField, &gData_opp);
            //check if you won (0 means no boats left)
            if (AgentGetEnemyStatus() == 0) {
                FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_NONE);
                checkState = AGENT_STATE_WON;
                return 0;
            } else {
                //update screen, wait for opponent turn
                FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_THEIRS);
                checkState = AGENT_STATE_WAIT_FOR_GUESS;
                return 0;
            }

        } else if (agentEvent == AGENT_EVENT_NONE) {
            //puts("wee wee");
            return 0;
        } else if (agentEvent == AGENT_EVENT_MESSAGE_PARSING_FAILED) {
            //if something else is received, commit code sudoku 
            printf("(ERROR Tag: GEARING)");
            OledClear(0);
            OledDrawString("ERROR_STRING_PARSING");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;
            break;
        } else {
            agentEvent = AGENT_EVENT_NONE;
            return 0;
        }
        return 0;
        break;
    case AGENT_STATE_WAIT_FOR_GUESS:
        FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_THEIRS);
        //decode enemy data about opponent guess
        //first check to make sure hit message is received
        if (agentEvent == AGENT_EVENT_RECEIVED_COO_MESSAGE) {
            returnVal = ProtocolEncodeHitMessage(outBuffer, &gData_opp);
            //puts("yee haww");
            //check if there was a hit
            //FieldUpdateKnowledge(&enemyField, &gData_opp);
            //check if you won (0 means no boats left)
            if (AgentGetStatus() == 0) {
                FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_NONE);
                checkState = AGENT_STATE_LOST;
                return returnVal;
            } else {
                //update screen, wait for opponent turn
                FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_MINE);
                checkState = AGENT_STATE_SEND_GUESS;
                return returnVal;
            }
        } else if (agentEvent == AGENT_EVENT_NONE) {
            //puts("panzer vor");
            return 0;
        } else if (agentEvent == AGENT_EVENT_MESSAGE_PARSING_FAILED) {
            //if something else is received, commit code sudoku 
            printf("(ERROR TAG: SHIMAKAZE)");
            OledClear(0);
            OledDrawString("ERROR_STRING_PARSING");
            OledUpdate();

            checkState = AGENT_STATE_INVALID;
            break;
        } else {
            return 0;
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
        while (1);
        return 0;
        break;
    case AGENT_STATE_WON:
        //you won (don't do anything next?)
        printf("\n'War is cruelty. There is no use trying to reform it. "
                "The crueler it is, the sooner it will be over.' -William Tecumseh Sherman\n");
        while (1);
        return 0;
        break;

    }
    return 0;
}

uint8_t AgentGetStatus(void)
{
    return FieldGetBoatStates(&playerField);
}

uint8_t AgentGetEnemyStatus(void)
{
    return FieldGetBoatStates(&enemyField);
}

//merely a test function for drawing the screen

void AgentDrawScreen(void)
{
    FieldOledDrawScreen(&playerField, &enemyField, FIELD_OLED_TURN_NONE);
}
