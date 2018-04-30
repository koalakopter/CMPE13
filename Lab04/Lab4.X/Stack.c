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

int StackPop(struct Stack *stack, float *value)
{
    if (stack->initialized != TRUE || stack->currentItemIndex == -1) {
        return STANDARD_ERROR;
    }
    *value = stack->stackItems[stack->currentItemIndex];
    stack->currentItemIndex -= 1;
    return SUCCESS;
}

int StackIsEmpty(const struct Stack *stack)
{
    if (stack->initialized != TRUE || stack->stackItems[stack->currentItemIndex] != -1) {
        return STANDARD_ERROR;
    }
    return SUCCESS;
}

int StackIsFull(const struct Stack *stack)
{
    if (stack->initialized != TRUE){
        return STANDARD_ERROR;
    }
    if (stack->currentItemIndex == STACK_SIZE -1)
    {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized != TRUE){
        return SIZE_ERROR;
    }
    if (stack->currentItemIndex == -1)
    {
        return 0;
    }
    return stack->currentItemIndex + 1;
}



