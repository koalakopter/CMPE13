#include "Game.h"
#include "Player.h"
#include "UNIXBOARD.h"
#include <stdio.h>
#include <string.h>

static struct {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1]; //includes the \0
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t exits; //exits
    int exitRooms[3]; //checks for room the num of the exit
    uint8_t roomNum;
    uint8_t itemRec;

    char fileName[69]; //for storing the name of the file?

    int titleLen; //self explanatory
    int descLen;
    int encryptKey;
} theRoom; //oh hai Mark

static FILE *file;
static int loop; // for loops ofc
static char *tit, *des;

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

int GameGoNorth(void)
{
    //if exit doesn't exist, return error
    if (theRoom.exits & GAME_ROOM_EXIT_NORTH_EXISTS) {
        GameGetCurrentRoomTitle(tit);
        GameGetCurrentRoomDescription(des);
        printf("ROOM: %s, DESCRIPTION: %s, EXITS %d", tit, des, theRoom.exits);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameGoEast(void)
{
    //if exit doesn't exist, return error
    if (theRoom.exits & GAME_ROOM_EXIT_EAST_EXISTS) {
        GameGetCurrentRoomTitle(tit);
        GameGetCurrentRoomDescription(des);
        printf("ROOM: %s, DESCRIPTION: %s, EXITS %d", tit, des, theRoom.exits);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameGoSouth(void)
{
    //if exit doesn't exist, return error
    if (theRoom.exits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
        GameGetCurrentRoomTitle(tit);
        GameGetCurrentRoomDescription(des);
        printf("ROOM: %s, DESCRIPTION: %s, EXITS %d", tit, des, theRoom.exits);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameGoWest(void)
{
    //if exit doesn't exist, return error
    if (theRoom.exits & GAME_ROOM_EXIT_WEST_EXISTS) {
        GameGetCurrentRoomTitle(tit);
        GameGetCurrentRoomDescription(des);
        printf("ROOM: %s, DESCRIPTION: %s, EXITS %d", tit, des, theRoom.exits);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameInit(void)
{
    theRoom.roomNum = STARTING_ROOM;
    GameGetCurrentRoomTitle(tit);
    GameGetCurrentRoomDescription(des);
    printf("ROOM: %s, DESCRIPTION: %s, EXITS %d", tit, des, theRoom.exits);

    return SUCCESS;
    //    sprintf(theRoom.fileName, "RoomFiles/room%d.txt", theRoom.roomNum);
    //    file = fopen(theRoom.fileName, "rb"); //opens a file for reading
    //    if (file == NULL) {
    //        return STANDARD_ERROR;
    //    }
    //    fseek(file, 0, SEEK_SET); //go to beginning of file
    //    theRoom.encryptKey = theRoom.roomNum + DECRYPTION_BASE_KEY;
    //    loop = 0;
    //    while (getc(file) != NULL) {
    //        theRoom.fileContents[loop] = getc(file);
    //        printf("%c", theRoom.fileContents);
    //        loop++;
    //    }
    //    printf("%s", theRoom.fileContents);
    //    return 1;
}

static char temp;
static int x;

int GameGetCurrentRoomTitle(char *title)
{

    theRoom.encryptKey = DECRYPTION_BASE_KEY + theRoom.roomNum;
    sprintf(theRoom.fileName, "RoomFiles/room%d.txt", theRoom.roomNum);
    file = fopen(theRoom.fileName, "rb");
    if (file == NULL) {
        return STANDARD_ERROR;
    }
    fread(&x, 1, 1, file);
    theRoom.titleLen = x ^ theRoom.encryptKey; //decrypt the title
    theRoom.titleLen = fgetc(file);
    for (loop = 0; loop < theRoom.titleLen; loop++) {
        temp = fgetc(file); //reads a character from the title
        theRoom.title[loop] = temp ^ theRoom.encryptKey; //decodes the character
    }
    theRoom.title[loop] = NULL; //terminates the string with a null
    strcpy(title, theRoom.title);
    return strlen(theRoom.title);

}

//should be called directly after gamegetcurrentroomtitle to work

int GameGetCurrentRoomDescription(char *desc)
{
    fread(&x, 1, 1, file);
    theRoom.itemRec = x ^ theRoom.encryptKey;
    uint8_t tempNum = theRoom.itemRec;
    BOOLEAN present = TRUE; //checks if items are present in inventory
    for (loop = 0; loop < tempNum; loop++) {
        fread(&x, 1, 1, file);
        theRoom.itemRec = x ^ theRoom.encryptKey;
        //try to find item in inventory
        if (FindInInventory(theRoom.itemRec) != SUCCESS) {
            present = FALSE;
        }
    }
    fread(&x, 1, 1, file);
    theRoom.descLen = x ^ theRoom.encryptKey; //get the actual description of the room!
    theRoom.descLen = fgetc(file);
    for (loop = 0; loop < theRoom.descLen; loop++) {
        temp = fgetc(file); //reads a character from the title
        theRoom.description[loop] = temp ^ theRoom.encryptKey; //decodes the character
    }
    //add dat null char if this is the only version
    if (present == FALSE) {
        theRoom.description[loop] = NULL;
        GameGetCurrentRoomExits();
        return strlen(theRoom.description);
    }
    return strlen(theRoom.description);
}

//should be called directly after gamegetcurrentroomexits to work

uint8_t GameGetCurrentRoomExits(void)
{
    fread(&x, 1, 1, file);
    x ^= theRoom.encryptKey;
    theRoom.exits = 0;
    if (x & GAME_ROOM_EXIT_WEST_EXISTS) {
        theRoom.exits |= 0x0001;
    }
    if (x & GAME_ROOM_EXIT_EAST_EXISTS) {
        theRoom.exits |= 0x0010; //or the results with the current result
    }
    if (x & GAME_ROOM_EXIT_NORTH_EXISTS) {
        theRoom.exits |= 0x0100; //or the results with the current result
    }
    if (x & GAME_ROOM_EXIT_SOUTH_EXISTS) {
        theRoom.exits |= 0x1000; //or the results with the current result
    }
    return theRoom.exits;
}