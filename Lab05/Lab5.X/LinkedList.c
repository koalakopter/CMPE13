#include <stdio.h>
#include <stdlib.h> 
#include "LinkedList.h"

//sets up a new linked list item

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

//compare two Strings

int CompareStrings(ListItem *first, ListItem *second)
{
    int x, y;
    //if the data is not null, set the length of that string to x
    if ((first->data) != NULL) {
        x = strcmp(first->data);
    }
    //do the same thing for the second input
    if ((second->data) != NULL) {
        y = strcmp(second->data);
    }

    //compare the lengths 
    //case 1, first str is alphabetically before second str
    if (x < y) {
        return -1;
    }        //case 2, second str is alphabetically before first str
    else if (x > y) {
        return 1;
    }        //case 3, they are equal
    else {
        return 0;
    }

}

//Linked List Remove function
char *LinkedListRemove(ListItem *item)
{
    //can't free after a return, so make a temp storage
    ListItem *temp = LinkedListNew(NULL);
    temp->data = item->data;
    free(item);
    return temp->data;
}