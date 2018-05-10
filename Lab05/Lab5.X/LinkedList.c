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
    //if either list elemnt is null, return 42069, since ERROR is -1, and we are using that
    if (first == NULL || second == NULL) {
        return -42069;
    }

    //check for null strings
    if (first->data == NULL && second->data != NULL) {
        return -1;
    }
    if (first->data != NULL && second->data == NULL) {
        return 1;
    }
    if (first->data == NULL && second->data == NULL) {
        return 0;
    }

    //first, compare the length of the strings
    if (strlen(first->data) < strlen(second->data)) {
        return -1;
    } else if (strlen(first->data) > strlen(second->data)) {
        return 1;
    }

    //else, compare alphabetically
    int x = strcmp(first->data, second->data);
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

/*
char *LinkedListRemove(ListItem *item)
{
    if (item == NULL) {
        return NULL;
    }
    //can't free after a return, so make a temp storage
    ListItem *temp = LinkedListNew(NULL);
    temp->data = item->data;
    temp->nextItem = item->nextItem;

    //set the previous item to point to the argument's next item and vice versa
    if ((item->previousItem) != NULL) {
        item->previousItem->nextItem = item->nextItem;
    }//if there is no previous item, set the next item's previous item to NULL
    else {
        item->nextItem->previousItem = NULL;
    }

    if ((item->nextItem) != NULL) {
        item->nextItem->previousItem = item->previousItem;
    } else {
        item->previousItem->nextItem = NULL;
    }
    //exit routine
    free(item);
    return temp->data;
}
 */
char *LinkedListRemove(ListItem *item)
{
    if (item == NULL) {
        return NULL;
    }
    //can't free after a return, so make a temp storage
    char *temp = item->data; 

    //case1: first list item
    if (item->nextItem != NULL && item->previousItem == NULL) {
        item->nextItem->previousItem = NULL;
        
        //case2: last list item
    } else if (item->previousItem != NULL && item->nextItem == NULL) {
        item->previousItem->nextItem = NULL;
        
        //case3: middle item
    } else if (item->nextItem != NULL && item->previousItem != NULL) { \
        item->previousItem->nextItem = item->nextItem;
        item->nextItem->previousItem = item->previousItem;
    }
    
    //exit routine
    free(temp);
    return temp;
}
//creates an item after a certain place in a linkedlist

ListItem * LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *newItem = LinkedListNew(data);
    //check if you are trying to put it at the head of list
    if ((item->nextItem) == NULL) {
        newItem->previousItem = item;
        //no nextItem since its at the head
        newItem->nextItem = NULL;
        item->nextItem = newItem;
        newItem->data = data;

        //makes the item passed in point to the newItem you just made
        item->nextItem = newItem;
    }//if passed an item not at the head, insert the item into the list
    else {
        newItem->nextItem = item->nextItem;
        item->nextItem->previousItem = newItem;
        item->nextItem = newItem;
        newItem->previousItem = item;
        newItem->data = data;
    }
    return newItem;
}

ListItem * LinkedListGetFirst(ListItem * list)
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
//%c only works on single char, %s works on everything else I guess

int LinkedListPrint(ListItem * list)
{
    //return NULL if the pointer points nowhere
    if (list == NULL) {
        //return STANDARD_ERROR;
    }
    //else, print out the list like normal
    //get the first item of the list and print from there
    list = LinkedListGetFirst(list);
    printf("\n[ ");
    //keep going until the nextItem is NULL, or the head of the list is reached
    while ((list->nextItem) != NULL) {
        printf("%s, ", list->data);
        list = list->nextItem;
    }
    //prints out the last item in the list
    printf("%s ]\n", list->data);
    return SUCCESS;
}

//LinkedListSize function

int LinkedListSize(ListItem * list)
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

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{

    //error flag if one of the items passed in is NULL
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    }
    //if they're both the same no need to swap them
    if (firstItem ->data == secondItem->data) {
        return SUCCESS;
    }
    //otherwise, proceed as normal
    //create a temporary holder + memory to store the data as its switched around
    ListItem *inventory = (ListItem *) malloc(sizeof (ListItem));

    //store the data in inventory temporarily
    inventory->data = firstItem->data;
    //swap the data around, second going to first
    firstItem->data = secondItem->data;
    //set second.data to stored data
    secondItem->data = inventory->data;

    //exit routine
    free(inventory);
    return SUCCESS;


}

//sorts a list from LOWEST to HIGHEST
//and then, sorts alphabetically

int LinkedListSort(ListItem * list)
{
    //again ERROR if passed an invalid list
    if (list == NULL) {
        return STANDARD_ERROR;
    }
    //go to the beginning of the list
    list = LinkedListGetFirst(list);
    //creates a temporary storage unit to hold the next item in the list
    ListItem *next = malloc(sizeof (ListItem));
    next = list->nextItem;

    //outer loop iteration
    while ((list->nextItem) != NULL) {
        //inner loop
        for (next = list->nextItem; next->nextItem != NULL; next = next->nextItem) {
            //swaps the values if list < next
            if (CompareStrings(list, next) >= 0) {
                LinkedListSwapData(list, next);
            }
        }
        //check the last element of the list, since that wasn't checked in the loop
        if ((next->nextItem) == NULL) {
            if (CompareStrings(list, next) >= 0) {
                LinkedListSwapData(list, next);
            }
        }

        //end of inner loop

        //move list one up
        list = list->nextItem;
    }
    //end of outer loop

    //exit routine
    free(next);
    return SUCCESS;
}



