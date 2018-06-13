#include "Game.h"
#include "UNIXBOARD.h"
#include <stdio.h>

static struct {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1]; //includes the \0
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t exits; //exits
    uint8_t roomNum;

    char fileName[20]; //for storing the name of the file?
    
    int titleLen;
    int descLen;
    int encryptKey;
} theRoom; //oh hai Mark

static FILE *file;
static int loop; // for loops ofc

int GameGoNorth(void)
{
    //if exit doesn't exist, return error
    if (theRoom.exits & GAME_ROOM_EXIT_NORTH_EXISTS) {
        return STANDARD_ERROR;
    }
    //get the filename
    sprintf(theRoom.fileName, "RoomFiles/room%u.txt", theRoom.roomNum);
    file = fopen(theRoom.fileName, "r"); //opens a file for reading
    //checks if the file is valid
    if (file == NULL) {
        //FATAL_ERROR();
    }
    //decrypt the file
    fseek(file, 0, SEEK_SET); //go to beginning of file
    theRoom.encryptKey =  theRoom.roomNum + DECRYPTION_BASE_KEY;
    while(getc(file) != NULL)
    {
        
    }
    
}

int GameGoEast(void)
{
    
}

int GameGoSouth(void)
{
    
}

int GameGoWest(void)
{
    
}

int GameInit(void)
{
    theRoom.roomNum = STARTING_ROOM;
}

int GameGetCurrentRoomTitle(char *title)
{
    if (file == NULL)
    {
        return STANDARD_ERROR;
    }
    theRoom.titleLen = getc(file);
    for(loop = 0; loop < theRoom.titleLen; loop++)
    {
        //get characters one at a time
        theRoom.title[loop] = getc(file);
    }
    theRoom.title[loop] = '\0'; //finish it off with a null
    return theRoom.titleLen;
}

int GameGetCurrentRoomDescription(char *desc)
{
    
}

uint8_t GameGetCurrentRoomExits(void)
{
    
}