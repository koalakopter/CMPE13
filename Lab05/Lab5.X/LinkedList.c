#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "LinkedList.h"

//sets up a new linked list item

ListItem *LinkedListNew(char *data)
{
    //sets up a pointer for a new list item
    ListItem *currentList = malloc(sizeof (ListItem));
    //if malloc fails, return null
    if (currentList != NULL) {
        currentList->nextItem = NULL;
        currentList->previousItem = NULL;
        currentList->data = data;

        return currentList;
    }
    return NULL;
}

//compare two Strings

int CompareStrings(ListItem *first, ListItem *second)
{
    int x;
    //if the data is not null, set the length of that string to x
    //if ((first->data) != NULL && (second->data != NULL)) {
    x = strcmp(first->data, second ->data);
    //}

    //compare the lengths 
    //case 1, first str is alphabetically before second str
    if (x < 0) {
        return -1;
    }//case 2, second str is alphabetically before first str
    else if (x > 0) {
        return 1;
    }//case 3, they are equal
    else {
        return 0;
    }

}

//Linked List Remove function

char *LinkedListRemove(ListItem *item)
{
    if (item == NULL) {
        return NULL;
    }
    //can't free after a return, so make a temp storage
    ListItem *temp = LinkedListNew(NULL);
    temp->data = item->data;
    free(item);
    return temp->data;
}

int LinkedListSize(ListItem *list)
{
    int counter = 0;

}

ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *newItem = LinkedListNew(data);
    //check if the item passed in is NULL, if so, no previous element
    if (item->data == NULL) {
        newItem->previousItem = NULL;
        newItem->nextItem = NULL;
        newItem->data = data;
    }//if passed a valid item, put new list item after that one
    else {
        newItem->previousItem = item;
        newItem->nextItem = NULL;
        newItem->data = data;
        //makes the item passed in point to the new item
        item->nextItem = newItem;
    }
    return newItem;
}

ListItem *LinkedListGetFirst(ListItem *list)
{
    //if passed in a NULL item, return NULL
    if (list == NULL) {
        return NULL;
    }
    //if passed in the first element in the list, return itself
    if (list->previousItem == NULL) {
        return list;
    }
    //while loop until the previous item isn't null
    while (list->previousItem != NULL) {
        list = list->previousItem;
    }
    return list;
}
