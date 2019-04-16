/*
 * Colin Mitchell - coamitch@ucsc.edu
 * Lab09 - Battle boats
 * June 1, 2018 
 */

#include "BOARD.h"
#include "Field.h"
#include "Protocol.h"

//creating fields for the player and the enemy
static Field *playerField;
static Field *enemyField;

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
    
    while(!done)
    {
        //here we are getting the modulo of the rand so we ensure that our
        //value is 0-5 for rows, 0-9 for columns, and 0-3 for direction
        randRow = rand() % 7;
        randCol = rand() % 10;
        randDir = rand() % 4;

        switch(boatType)
        {
            case FIELD_BOAT_SMALL:
                checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

                if(checkPlacedBoat)
                {
                    boatType = FIELD_BOAT_MEDIUM;
                }

                break;

            case FIELD_BOAT_MEDIUM:
                checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

                if(checkPlacedBoat)
                {
                    boatType = FIELD_BOAT_LARGE;
                }

                break;

            case FIELD_BOAT_LARGE:
                checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

                if(checkPlacedBoat)
                {
                    boatType = FIELD_BOAT_HUGE;
                }

                break;

            case FIELD_BOAT_HUGE:
                checkPlacedBoat = FieldAddBoat(playerField, randRow, randCol, randDir, boatType);

                if(checkPlacedBoat)
                {
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