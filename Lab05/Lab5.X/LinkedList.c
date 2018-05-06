#include <stdio.h>
#include "LinkedList.h"

ListItem *LinkedListNew(char *data)
{
    //sets up a pointer for a new list item
    ListItem *currentList;
    //if malloc fails, return null
    if (currentList = (ListItem *) malloc(sizeof (ListItem))) {
        currentList->data = data;
        currentList->nextItem = NULL;
        currentList->previousItem = NULL;
        return currentList;
    }
    return NULL;
}
