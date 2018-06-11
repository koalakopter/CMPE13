
#include "UNIXBOARD.h"
#include "Player.h"
#include <stdint.h>
#include <stdio.h>

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

//inventory
uint8_t inventory[INVENTORY_SIZE];
static BOOLEAN added;
static int loop;

int AddToInventory(uint8_t item)
{
    added = FALSE;
    loop = 0;
    //loops through inventory until it finds an open slot, or inv is full
    while (loop < INVENTORY_SIZE) {
        if (inventory[loop] == NULL) {
            //add the item
            inventory[loop] = item;
            return SUCCESS;
        }
        loop++;
    }
    return STANDARD_ERROR;
}

int FindInInventory(uint8_t item)
{
    loop = 0;
    while (loop < INVENTORY_SIZE) {
        if(inventory[loop] == item)
        {
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}