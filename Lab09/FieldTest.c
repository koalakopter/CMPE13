// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Field.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****


// **** Declare any function prototypes here ****



int main()
{
    BOARD_Init();



/******************************************************************************
 * Your code goes in between this comment and the following one with asterisks.
 *****************************************************************************/
    //enum used for switching the testing state
    enum testState {FIELD_INIT,
                    FIELD_AT,
                    FIELD_SET_LOCATION,
                    FIELD_ADD_BOAT,
                    FIELD_ENEMY_ATTACK, 
                    FIELD_UPDATE_KNOW,
                    FIELD_GET_STATUS} test = FIELD_INIT; 
                  
    //variables used for checking functionality
    Field *testField = malloc(sizeof(Field));
    GuessData *guessData = malloc(sizeof(GuessData));
    
    //FIELD_INIT:
    int totalLives = 0;
    
    //check variables:
    int check1 = 0;
    int check2 = 0;
    int check3 = 0;
    int check4 = 0;
    
    //looping variables:
    int done = FALSE;
    int i;
    int j;
    
    //calculating the total and percentage variables:
    float pass = 0;
    float points = 0;
    float totalPoints = 0;
    float percentage = 0;
       
    //print statement to show the beginning of testing.
    printf("Test harness for Field.c:\n");
    printf("*************************\n");
    while(!done)
    {
        //resetting the pass value so we get a clean
        //count each time through the loop.
        pass = 0;
        
        switch(test)
        {
            case FIELD_INIT: //2 tests - 1 point, 1 visual
                //initializing the field
                FieldInit(testField, FIELD_POSITION_EMPTY);

                //Test 1: correct boat lives
                //the correct value if you add them all up
                //is 18, so we add and check for 18
                totalLives += testField->smallBoatLives + testField->mediumBoatLives;
                totalLives += testField->largeBoatLives + testField->hugeBoatLives;

                if(totalLives == 18)
                {
                    pass++;
                    printf("FieldInit() test 1: passed\n");
                }
                else
                {
                    printf("FieldInit() test 1: failed\n");
                }

                

                //Test 2: printing the field and making sure its initialized correctly
                //printing the expected result
                printf("Expected:\n");
                printf("------------\n");
                printf("[0000000000]\n");
                printf("[0000000000]\n");
                printf("[0000000000]\n");
                printf("[0000000000]\n");
                printf("[0000000000]\n");
                printf("[0000000000]\n");
                printf("------------\n\n");

                //printing the actual result
                printf("Actual:\n");
                printf("------------\n");
                for(i = 0; i < FIELD_ROWS; i++)
                {
                    printf("[");
                    for(j = 0; j < FIELD_COLS; j++)
                    {
                        printf("%d", testField->field[i][j]);
                    }
                    printf("]\n");
                }
                printf("------------\n");

                //printing the function test divider.
                printf("*************************\n");
                //adding points for the running total and switching the state
                points += pass;
                totalPoints += 1.0;
                test++;
                break;

            case FIELD_AT: //2 tests - 2 points
                //Test 1: retrieving data set manually
                //setting some points to check
                testField->field[0][3] = 9;
                testField->field[3][0] = 8;
                
                check1 = FieldAt(testField, 0, 3);
                check2 = FieldAt(testField, 3, 0);
                
                if(check1 == 9 && check2 == 8)
                {
                    pass++;
                    printf("FieldAt() test 1: passed\n");
                }
                else
                {
                    printf("FieldAt() test 1: failed\n");
                }
                
                testField->field[0][3] = FIELD_POSITION_EMPTY;
                testField->field[3][0] = FIELD_POSITION_EMPTY;
                
                //Test 2: trying to retrieve data off the field
                //setting check three to a value that should return null
                check3 = FieldAt(testField, 7, 11);
                
                if(check3 == NULL)
                {
                    pass++;
                    printf("FieldAt() test 2: passed\n");
                }
                else
                {
                    printf("FieldAt() test 2: failed\n");
                }
                
                //printing the function test divider.
                printf("*************************\n");
                //adding points for the running total and switching the state
                points += pass;
                totalPoints += 2.0;
                test++;
                break;

            case FIELD_SET_LOCATION: //2 tests - 2 points
                //test 1: setting a value on an empty field
                check1 = FieldSetLocation(testField, 3, 0, 9);
                check2 = testField->field[3][0];
                
                if(check1 == 0 && check2 == 9)
                {
                    pass++;
                    printf("FieldSetLocation() test 1: passed\n");
                }
                else
                {
                    printf("FieldAt() test 1: failed\n");
                }
                
                //test 2: setting a value on an occupied space
                testField->field[0][3] = 5;
                
                check1 = FieldSetLocation(testField, 0, 3, 8);
                check2 = testField->field[0][3];
                
                if(check1 == 5 && check2 == 8)
                {
                    pass++;
                    printf("FieldSetLocation() test 2: passed\n");
                }
                else
                {
                    printf("FieldAt() test 2: failed\n");
                }
                
                //resetting the field to empty 
                testField->field[0][3] = FIELD_POSITION_EMPTY;
                testField->field[3][0] = FIELD_POSITION_EMPTY;
                
                //printing the function test divider.
                printf("*************************\n");
                //adding points for the running total and switching the state
                points += pass;
                totalPoints += 2.0;
                test++;
                break;

            case FIELD_ADD_BOAT: //2 tests - 2 points 2 visuals
                //Test 1: placing four boats in each direction
                check1 = FieldAddBoat(testField, 0, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_HUGE);
                check2 = FieldAddBoat(testField, 0, 9, FIELD_BOAT_DIRECTION_SOUTH, FIELD_BOAT_LARGE);
                check3 = FieldAddBoat(testField, 5, 9, FIELD_BOAT_DIRECTION_WEST, FIELD_BOAT_MEDIUM);
                check4 = FieldAddBoat(testField, 5, 0, FIELD_BOAT_DIRECTION_NORTH, FIELD_BOAT_SMALL);
                
                if(check1 == TRUE && check2 == TRUE)
                {
                    if(check3 == TRUE && check4 == TRUE)
                    {
                        pass++;
                        printf("FieldAddBoat() test 1: passed\n");
                    }
                    else
                    {
                        printf("FieldAddBoat() test 1: failed\n");
                    }
                }
                else
                {
                    printf("FieldAddBoat() test 1: failed\n");
                }
                
                printf("Expected:\n");
                printf("------------\n");
                printf("[4444440003]\n");
                printf("[0000000003]\n");
                printf("[0000000003]\n");
                printf("[1000000003]\n");
                printf("[1000000003]\n");
                printf("[1000002222]\n");
                printf("------------\n\n");

                //printing the actual result
                printf("Actual:\n");
                printf("------------\n");
                for(i = 0; i < FIELD_ROWS; i++)
                {
                    printf("[");
                    for(j = 0; j < FIELD_COLS; j++)
                    {
                        printf("%d", testField->field[i][j]);
                    }
                    printf("]\n");
                }
                printf("------------\n");
                
                //Test 2: placing boats that wont aren't valid
                //check that the boat wont go off the field
                check1 = FieldAddBoat(testField, 4, 3, FIELD_BOAT_DIRECTION_NORTH, FIELD_BOAT_SMALL);
                //check that the boat wont go into another boat
                check2 = FieldAddBoat(testField, 3, 6, FIELD_BOAT_DIRECTION_WEST, FIELD_BOAT_LARGE);
                                
                if(check1 == TRUE && check2 == FALSE)
                {
                    pass++;
                    printf("FieldAddBoat() test 2: passed\n");
                }
                else
                {
                    printf("FieldAddBoat() test 2: failed\n");
                }
                
                //printing the expected values
                printf("Expected:\n");
                printf("------------\n");
                printf("[4444440003]\n");
                printf("[0000000003]\n");
                printf("[0001000003]\n");
                printf("[1001000003]\n");
                printf("[1001000003]\n");
                printf("[1000002222]\n");
                printf("------------\n\n");
                
                //printing the actual result
                printf("Actual:\n");
                printf("------------\n");
                for(i = 0; i < FIELD_ROWS; i++)
                {
                    printf("[");
                    for(j = 0; j < FIELD_COLS; j++)
                    {
                        printf("%d", testField->field[i][j]);
                    }
                    printf("]\n");
                }
                printf("------------\n");
                
                //printing the function test divider.
                printf("*************************\n");
                //adding points for the running total and switching the state
                points += pass;
                totalPoints += 2.0;
                test++;
                break;

            case FIELD_ENEMY_ATTACK: //3 tests - 3 points
                //Test 1: hitting a boat
                guessData->row = 3;
                guessData->col = 0;
                
                //check1 should be equal to the original data (0)
                check1 = FieldRegisterEnemyAttack(testField, guessData);
                //check2 should be equal to a hit status (FIELD_POSITION_HIT)
                check2 = testField->field[guessData->row][guessData->col];
                
                //if check1 and check2 are true then we move to the next condition
                if(check1 == FIELD_POSITION_SMALL_BOAT && check2 == FIELD_POSITION_HIT)
                {
                    //checking that guessData's hit is a hit
                    if(guessData->hit == HIT_HIT)
                    {
                        //checking that the number of lives has been decreased
                        if(testField->smallBoatLives == 2)
                        {
                            pass++;
                            printf("FieldRegisterEnemyAttack() test 1: passed\n");
                        }
                        else
                        {
                            printf("FieldRegisterEnemyAttack() test 1: failed\n");
                        }
                    }
                    else
                    {
                        printf("FieldRegisterEnemyAttack() test 1: failed\n");
                    }
                }
                else
                {
                    printf("FieldRegisterEnemyAttack() test 1: failed\n");
                }

                //Test 2: sinking the small boat
                //doing the second hit on the small boat
                guessData->row = 4;
                guessData->col = 0;
                FieldRegisterEnemyAttack(testField, guessData);
                
                //sinking hit on the small boat
                guessData->row = 5;
                guessData->col = 0;
                check1 = FieldRegisterEnemyAttack(testField, guessData);
                check2 = testField->field[guessData->row][guessData->col];
                
                //if check1 and check2 are true then we move to the next condition
                if(check1 == FIELD_POSITION_SMALL_BOAT && check2 == FIELD_POSITION_HIT)
                {
                    //checking that guessData's hit is a hit
                    if(guessData->hit == HIT_SUNK_SMALL_BOAT)
                    {
                        //checking that the number of lives has been decreased
                        if(testField->smallBoatLives == 0)
                        {
                            pass++;
                            printf("FieldRegisterEnemyAttack() test 2: passed\n");
                        }
                        else
                        {
                            printf("FieldRegisterEnemyAttack() test 2: failed\n");
                        } 
                    }
                    else
                    {
                        printf("FieldRegisterEnemyAttack() test 2: failed\n");
                    }   
                }
                else
                {
                    printf("FieldRegisterEnemyAttack() test 2: failed\n");
                }
                
                //Test 3: missing
                //miss coordinates 
                guessData->row = 3;
                guessData->col = 1;
                check1 = FieldRegisterEnemyAttack(testField, guessData);
                check2 = testField->field[guessData->row][guessData->col];
                
                //if check1 and check2 are true then we move to the next condition
                if(check1 == FIELD_POSITION_EMPTY && check2 == FIELD_POSITION_MISS)
                {
                    //checking that guessData's hit is a hit
                    if(guessData->hit == HIT_MISS)
                    {
                        //no need to check the lives since we didn't change them
                        pass++;
                        printf("FieldRegisterEnemyAttack() test 3: passed\n");
                    }
                    else
                    {
                        printf("FieldRegisterEnemyAttack() test 3: failed\n");
                    }
                }
                else
                {
                    printf("FieldRegisterEnemyAttack() test 3: failed\n");
                }
                
                //printing the function test divider.
                printf("*************************\n");
                //adding points for the running total and switching the state
                points += pass;
                totalPoints += 3.0;
                test++;
                break; 

            case FIELD_UPDATE_KNOW: //3 tests - 3 points
                //Test 1: Hitting a boat
                guessData->row = 5;
                guessData->col = 9;
                FieldRegisterEnemyAttack(testField, guessData);
                //because we are just using 1 field to test, fieldRegisterEnemyAttck 
                //changes the position to a hit while it runs, so to see if the return
                //works for update, we set the original data manually.
                testField->field[guessData->row][guessData->col] = FIELD_POSITION_MEDIUM_BOAT;
                
                check1 = FieldUpdateKnowledge(testField, guessData);
                check2 = testField->field[guessData->row][guessData->col];
                
                if(check1 == FIELD_POSITION_MEDIUM_BOAT && check2 == FIELD_POSITION_HIT)
                {
                    pass++;
                    printf("FieldUpdateKnowledge() test 1: passed\n");
                }
                else
                {
                    printf("FieldUpdateKnowledge() test 1: failed\n");
                }
                
                //Test 2: Missing a boat
                guessData->row = 4;
                guessData->col = 7;
                FieldRegisterEnemyAttack(testField, guessData);
                
                testField->field[guessData->row][guessData->col] = FIELD_POSITION_EMPTY;
                check1 = FieldUpdateKnowledge(testField, guessData);
                check2 = testField->field[guessData->row][guessData->col];
                
                if(check1 == FIELD_POSITION_EMPTY && check2 == FIELD_POSITION_EMPTY)
                {
                    pass++;
                    printf("FieldUpdateKnowledge() test 2: passed\n");
                }
                else
                {
                    printf("FieldUpdateKnowledge() test 2: failed\n");
                }
                
                //Test 3: Sinking a boat
                //second hit of medium ship
                guessData->row = 5;
                guessData->col = 8;
                FieldRegisterEnemyAttack(testField, guessData);
                
                //third hit of medium ship
                guessData->row = 5;
                guessData->col = 7;
                FieldRegisterEnemyAttack(testField, guessData);
                
                //sinking hit of medium ship
                guessData->row = 5;
                guessData->col = 6;
                FieldRegisterEnemyAttack(testField, guessData);
                
                testField->field[guessData->row][guessData->col] = FIELD_POSITION_MEDIUM_BOAT;
                check1 = FieldUpdateKnowledge(testField, guessData);
                check2 = testField->field[guessData->row][guessData->col];
                check3 = testField->mediumBoatLives;
                
                if(check1 == FIELD_POSITION_MEDIUM_BOAT && check2 == FIELD_POSITION_HIT)
                {
                    if(check3 == 0)
                    {
                        pass++;
                        printf("FieldUpdateKnowledge() test 3: passed\n");
                    }
                    else
                    {
                        printf("FieldUpdateKnowledge() test 3: failed\n");
                    }
                }
                else
                {
                    printf("FieldUpdateKnowledge() test 3: failed\n");
                }
                
                //printing the function test divider.
                printf("*************************\n");
                //adding points for the running total and switching the state
                points += pass;
                totalPoints += 3.0;
                test++;
                break;

            case FIELD_GET_STATUS: //2 tests - 2 points
                //Test 1: all boats alive
                //since we have sunk the small and medium boats, those 
                //spots in the bit field should be 0 (0b0000|1100)
                
                check1 = FieldGetBoatStates(testField);
                
                if(check1 == 0b00001100)
                {
                    pass++;
                    printf("FieldGetBoatStates() test 1: passed\n");
                }
                else
                {
                    printf("FieldGetBoatStates() test 1: failed\n");
                }
                
                //Test 2: all boats sunk
                //in order to simulate all the boats sunk, we set the
                //remaining boats lives to 0
                testField->hugeBoatLives = 0;
                testField->largeBoatLives = 0;
                
                check1 = FieldGetBoatStates(testField);
                
                if(check1 == 0)
                {
                    pass++;
                    printf("FieldGetBoatStates() test 2: passed\n");
                }
                else
                {
                    printf("FieldGetBoatStates() test 2: failed\n");
                }
                
                 //printing the function test divider.
                printf("*************************\n");
                //adding points for the running total and switching the state
                points += pass;
                totalPoints += 2.0;
                test++;
                break;

            default:
                //calculating the grade percentage
                percentage = (points / totalPoints) * 100.0;
                
                //printing results
                printf("Points earned: %.0f\n", (double)points);
                printf("Total points: %.0f\n", (double)totalPoints);
                printf("Grade: %.1f\n", (double)percentage);
                
                //ending our while loop
                done = TRUE;
                
                break;
        }
    }

/******************************************************************************
 * Your code goes in between this comment and the preceeding one with asterisks
 *****************************************************************************/

    while (1);
}