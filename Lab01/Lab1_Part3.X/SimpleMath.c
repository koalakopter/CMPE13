#include "SimpleMath.h"
int Bigger(int x, int y);

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

//defining the "Bigger" Function

int Bigger(int x, int y)
{
    if (x >= y) {
        return x;
    } else {
        return y;
    }
}