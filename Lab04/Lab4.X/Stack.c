#include <stdio.h>
#include "Stack.h"

void StackInit(struct Stack *stack)
{
    stack -> currentItemIndex = -1;
    stack -> initialized = TRUE;
}

int StackPush(struct Stack *stack, float value)
{
    if (stack->initialized != TRUE) {
        return STANDARD_ERROR;
    }
    stack->currentItemIndex += 1;
    stack->stackItems[stack->currentItemIndex] = value; 
    return SUCCESS;
}



