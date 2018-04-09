#include "SimpleMath.h"

int AddTwoNumbers(int x, int y)
{
    int z = x + y;
    return z;
}

int IncrementByOne(int x)
{
    int y = AddTwoNumbers(x, 1);
    return y;
} 