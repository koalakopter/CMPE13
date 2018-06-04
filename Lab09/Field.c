/*
 * Colin Mitchell - coamitch@ucsc.edu
 * Lab09 - Battle boats
 * June 1, 2018 
 */

#include "Field.h"
#include "BOARD.h"

void FieldInit(Field *f, FieldPosition p)
{
    int i;
    int j;
    
    //looping through the whole field.
    //outer loop goes through the rows
    for(i = 0; i < FIELD_ROWS; i++)
    {
        //inner loop goes through the columns
        for(j = 0; j < FIELD_COLS; j++)
        {
            //setting the current row column position to the field
            //FieldPosition p
            f->field[i][j] = p;
        }
    }
    
    //There is no return type.
}

FieldPosition FieldAt(const Field *f, uint8_t row, uint8_t col)
{
    return f->field[row][col];
}

FieldPosition FieldSetLocation(Field *f, uint8_t row, uint8_t col, FieldPosition p)
{
    //storing the old position for the return later.
    FieldPosition oldPosition = f->field[row][col];
    
    //setting the new position
    f->field[row][col] = p;
    
    //returning the old position
    return oldPosition;
}

uint8_t FieldAddBoat(Field *f, uint8_t row, uint8_t col, BoatDirection dir, BoatType type)
{
    uint8_t workingRow = row;
    uint8_t workingCol = col;
    
    int done = FALSE;
    int boatTypeCounter = 0;
    
    while(!done)
    {
        //switch so we can make sure we are handling the directions properly.
        switch(dir)
        {
            case FIELD_BOAT_DIRECTION_NORTH:
                //row changes (-1) col stays constant 
                
                //checking if the boat goes off the field
                if(workingRow < 0)
                {
                    return FALSE;
                }
                
                //if there is still more boat to enter into the field
                if(boatTypeCounter < type)
                {
                    f->field[workingRow][workingCol] = type;
                }
                else
                {
                    done = TRUE;
                }

                boatTypeCounter += 1;
                workingRow -= 1;
                break;

            case FIELD_BOAT_DIRECTION_EAST:
                //row stays constant col shifts to the right (col+1)
                
                //checking if the boat goes off the field
                if(workingCol > FIELD_COLS - 1)
                {
                    return FALSE;
                }
                
                //if there is still more boat to enter into the field
                if(boatTypeCounter < type)
                {
                    f->field[workingRow][workingCol] = type;
                }
                else
                {
                    done = TRUE;
                }

                boatTypeCounter += 1;
                workingCol += 1;
                break;

            case FIELD_BOAT_DIRECTION_SOUTH:
                //col stays constant row shifts down (row+1)
                
                //checking if the boat goes off the field
                if(workingRow > FIELD_ROWS - 1)
                {
                    return FALSE;
                }
                
                //if there is still more boat to enter into the field
                if(boatTypeCounter < type)
                {
                    f->field[workingRow][workingCol] = type;
                }
                else
                {
                    done = TRUE;
                }

                boatTypeCounter += 1;
                workingRow += 1;
                break;

            case FIELD_BOAT_DIRECTION_WEST:
                //row stays constant col changes (col-1)
                
                //checking if the boat goes off the field
                if(workingCol < 0)
                {
                    return FALSE;
                }
                
                //if there is still more boat to enter into the field
                if(boatTypeCounter < type)
                {
                    f->field[workingRow][workingCol] = type;
                }
                else
                {
                    done = TRUE;
                }

                boatTypeCounter += 1;
                workingCol -= 1;
                break;
        }
    }
    
    //if we get through the while, nothing went wrong so we return true.
    return TRUE;
}

FieldPosition FieldRegisterEnemyAttack(Field *f, GuessData *gData)
{
    int originalData = f->field[gData->row][gData->col];
    
    //first we check to see if there was a hit or not. 
    if(originalData != FIELD_POSITION_EMPTY)
    {
        //updating the field with the hit status
        f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
        
        //switch on the original data to determine the boat we hit.
        switch(originalData)
        {
            case FIELD_BOAT_LIVES_SMALL:
                f->smallBoatLives -= 1;
                
                if(f->smallBoatLives != 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_SMALL_BOAT;
                }
                break;
                
            case FIELD_BOAT_LIVES_MEDIUM:               
                f->mediumBoatLives -= 1;
                
                if(f->mediumBoatLives != 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_SMALL_BOAT;
                }
                break;
                
            case FIELD_BOAT_LIVES_LARGE:
                f->largeBoatLives -= 1;
                
                if(f->largeBoatLives != 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_SMALL_BOAT;
                }
                break;
                
            case FIELD_BOAT_LIVES_HUGE:
                f->hugeBoatLives -= 1;
                
                if(f->hugeBoatLives != 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_SMALL_BOAT;
                }
                break;
        }
    }
    else //we missed and update accordingly
    {
        f->field[gData->row][gData->col] = FIELD_POSITION_MISS;
        
        gData->hit = HIT_MISS;
    }
    
    return originalData;
}

FieldPosition FieldUpdateKnowledge(Field *f, const GuessData *gData)
{
    int originalData = f->field[gData->row][gData->col];
    
    switch(gData->hit)
    {
        case HIT_MISS:
            f->field[gData->row][gData->col] = FIELD_POSITION_EMPTY;
            break;
            
        case HIT_HIT: 
            f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
            break;
            
        case HIT_SUNK_SMALL_BOAT:
            f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
            f->smallBoatLives = 0;
            break;
        
        case HIT_SUNK_MEDIUM_BOAT:
            f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
            f->mediumBoatLives = 0;
            break;
            
        case HIT_SUNK_LARGE_BOAT:
            f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
            f->largeBoatLives = 0;
            break;
            
        case HIT_SUNK_HUGE_BOAT:
            f->field[gData->row][gData->col] = FIELD_POSITION_HIT;
            f->hugeBoatLives = 0;
            break;
    }
    
    return originalData;
}

uint8_t FieldGetBoatStates(const Field *f)
{
    uint8_t workingBitField = 0;
    
    if(f->smallBoatLives != 0)
    {
        workingBitField = workingBitField | 1;
    }
    
    if(f->mediumBoatLives != 0)
    {
        workingBitField = workingBitField | 2;
    }
    
    if(f->largeBoatLives != 0)
    {
        workingBitField = workingBitField | 4;
    }
    
    if(f->hugeBoatLives != 0)
    {
        workingBitField = workingBitField | 8;
    }
    
    //and with 15 so we keep the lower four bits and make sure 
    //that the top four bits are clear (0).
    workingBitField = workingBitField & 15;
    
    return workingBitField;
}