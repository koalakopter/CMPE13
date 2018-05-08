#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "LinkedList.h"
#include "BOARD.h"

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

//creates an item after a certain place in a linkedlist

ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *newItem = LinkedListNew(data);
    //check if you are trying to put it at the head of list
    if (item->nextItem == NULL) {
        newItem->previousItem = item;
        //no nextItem since its at the head
        newItem->nextItem = NULL;
        newItem->data = data;
        item->nextItem = newItem;
    }//if passed an item not at the head, insert the item into the list
    else {
        newItem->previousItem = item;
        newItem->nextItem = item->nextItem;
        newItem->data = data;
        //makes the item passed in as an argument point to this new item we created
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
    //while loop until the previous item isn't null
    while ((list->previousItem) != NULL) {
        list = list->previousItem;
    }
    return list;
}

//LinkedListPrint function

int LinkedListPrint(ListItem *list)
{
    //return NULL if the pointer points nowhere
    if (list == NULL) {
       //return STANDARD_ERROR;
    }
    //else, print out the list like normal
    //get the first item of the list and print from there
    list = LinkedListGetFirst(list);
    printf("[ ");
    //keep going until the nextItem is NULL, or the head of the list is reached
    while ((list->nextItem) != NULL) {
        //prints the head item (has a special character in front and a newline)
        /*if ((list->previousItem) == NULL) {
            printf("\n{%s, ", list->data);
        }//prints the last item in the list (has special character in back and a newline at the end))
        else if ((list->nextItem) == NULL) {
            printf("%s}\n", list->data);
        }
            //prints out the middle items without any special formatting
        else {
            printf("%s, ", list->data);
        }
        list = list->nextItem;*/
        //printf("Data Piece: %c  \n", list->data);
        printf("%c, ", list->data);
        list = list->nextItem;
        

    }
    printf(" ]");
    return SUCCESS;
}

//LinkedListSize function

int LinkedListSize(ListItem *list)
{
    //return zero if the argument is pointing to an empty list
    if (list == NULL) {
        return 0;
    }

    int count = 1;
    //start at the head of the list
    list = LinkedListGetFirst(list);

    //keep going until nextItem is NULL, aka reach the head item
    while ((list->nextItem) != NULL) {
        //slowly move up the list and increment the counter
        list = list->nextItem;
        count = count + 1;
    }
    return count;

}


