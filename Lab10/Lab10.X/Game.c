#include "Game.h"
#include "UNIXBOARD.h"
#include <stdio.h>

static struct {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1]; //includes the \0
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t exits[3]; //4 exits 0 = N, 1 = E, 2 = S, 3 = W
    uint8_t roomNum;

    char fileName[20]; //for storing the name of the file?
} theRoom; //oh hai Mark

static FILE *file;

int GameGoNorth(void)
{
    //if exit doesn't exist, return error
    if (theRoom.exits[0] == 0) {
        return STANDARD_ERROR;
    }
    //get the filename
    sprintf(theRoom.fileName, "RoomFiles/room%u.txt", theRoom.roomNum);
    file = fopen(theRoom.fileName, "r"); //opens a file for reading
    //checks if the file is valid
    if (file == NULL) {
        //FATAL_ERROR();
    }
    //GET TITLE OF ROOM
    
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
    
}

int GameGetCurrentRoomDescription(char *desc)
{
    
}

uint8_t GameGetCurrentRoomExits(void)
{
    
}