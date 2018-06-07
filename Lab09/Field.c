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
    
    //filling the lives for the boats
    f->smallBoatLives = FIELD_BOAT_LIVES_SMALL;
    f->mediumBoatLives = FIELD_BOAT_LIVES_MEDIUM;
    f->largeBoatLives = FIELD_BOAT_LIVES_LARGE;
    f->hugeBoatLives = FIELD_BOAT_LIVES_HUGE;
    
    //There is no return.
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
    //determining what type of boat we have for the field
    int fieldBoatType = 0;
    switch(type)
    {
        case FIELD_BOAT_SMALL:
            fieldBoatType = FIELD_POSITION_SMALL_BOAT;
            break;
            
        case FIELD_BOAT_MEDIUM:
            fieldBoatType = FIELD_POSITION_MEDIUM_BOAT;
            break;
            
        case FIELD_BOAT_LARGE:
            fieldBoatType = FIELD_POSITION_LARGE_BOAT;
            break;
            
        case FIELD_BOAT_HUGE:
            fieldBoatType = FIELD_POSITION_HUGE_BOAT;
            break;
    }
    
    //variable for my for loops
    int i;
    
    //This just figures out the number of lives (number of spaces the boat occupies)
    //this way we can determine if the boat will fit or not up front
    int lives = type + FIELD_BOAT_LIVES_SMALL;
    
    //storing the data at the given field coordinates
    int fieldData = f->field[row][col];
    
    if(fieldData == FIELD_POSITION_EMPTY)
    {
        //switch so we can make sure we are handling the directions properly.
        switch(dir)
        {
            case FIELD_BOAT_DIRECTION_NORTH:
                //row changes (-1) col stays constant 

                //checking if the boat goes off the field
                if((row - lives) < 0)
                {
                    return FALSE;
                }
                
                for(i = 0; i < lives; i++)
                {
                    if(f->field[row - i][col] != FIELD_POSITION_EMPTY)
                    {
                        return FALSE;
                    }
                }

                for(i = 0; i < lives; i++)
                {
                    f->field[row - i][col] = fieldBoatType;
                }

                break;

            case FIELD_BOAT_DIRECTION_EAST:
                //row stays constant col shifts to the right (col+1)

                //checking if the boat goes off the field
                if((col + lives) > FIELD_COLS)
                {
                    return FALSE;
                }
                
                for(i = 0; i < lives; i++)
                {
                    if(f->field[row][col + i] != FIELD_POSITION_EMPTY)
                    {
                        return FALSE;
                    }
                }

                for(i = 0; i < lives; i++)
                {
                    f->field[row][col + i] = fieldBoatType;
                }

                break;

            case FIELD_BOAT_DIRECTION_SOUTH:
                //col stays constant row shifts down (row+1)

                //checking if the boat goes off the field
                if((row + lives) > FIELD_ROWS)
                {
                    return FALSE;
                }
                
                for(i = 0; i < lives; i++)
                {
                    if(f->field[row + i][col] != FIELD_POSITION_EMPTY)
                    {
                        return FALSE;
                    }
                }

                for(i = 0; i < lives; i++)
                {
                    f->field[row + i][col] = fieldBoatType;
                }

                break;

            case FIELD_BOAT_DIRECTION_WEST:
                //row stays constant col changes (col-1)

                //checking if the boat goes off the field
                if((col - lives) < 0)
                {
                    return FALSE;
                }
                
                for(i = 0; i < lives; i++)
                {
                    if(f->field[row][col - i] != FIELD_POSITION_EMPTY)
                    {
                        return FALSE;
                    }
                }

                for(i = 0; i < lives; i++)
                {
                    f->field[row][col - i] = fieldBoatType;
                }

                break;
        }
    }
    else 
    {
        //if there is already something in that field position then we fail.
        return FALSE;
    }
    
    //if we get through the if and the switch, nothing went wrong so we return true.
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
            case FIELD_POSITION_SMALL_BOAT:
                f->smallBoatLives -= 1;
                
                if(f->smallBoatLives > 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_SMALL_BOAT;
                }
                break;
                
            case FIELD_POSITION_MEDIUM_BOAT:               
                f->mediumBoatLives -= 1;
                
                if(f->mediumBoatLives > 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_MEDIUM_BOAT;
                }
                break;
                
            case FIELD_POSITION_LARGE_BOAT:
                f->largeBoatLives -= 1;
                
                if(f->largeBoatLives > 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_LARGE_BOAT;
                }
                break;
                
            case FIELD_POSITION_HUGE_BOAT:
                f->hugeBoatLives -= 1;
                
                if(f->hugeBoatLives > 0)
                {
                    gData->hit = HIT_HIT;
                }
                else
                {
                    gData->hit = HIT_SUNK_HUGE_BOAT;
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
    
    if(f->smallBoatLives > 0)
    {
        workingBitField = workingBitField | FIELD_BOAT_STATUS_SMALL;
    }
    
    if(f->mediumBoatLives > 0)
    {
        workingBitField = workingBitField | FIELD_BOAT_STATUS_MEDIUM;
    }
    
    if(f->largeBoatLives > 0)
    {
        workingBitField = workingBitField | FIELD_BOAT_STATUS_LARGE;
    }
    
    if(f->hugeBoatLives > 0)
    {
        workingBitField = workingBitField | FIELD_BOAT_STATUS_HUGE;
    }
    
    //and with 15 so we keep the lower four bits and make sure 
    //that the top four bits are clear (0).
    workingBitField = workingBitField & 0x0f;
    
    return workingBitField;
}