#include "MatrixMath.h"

//counter for rows
int x;
//counter for columns
int y;

//returns 1 if true, 0 if false

int MatrixEquals(float a[3][3], float b[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            if (a[x][y] - b[x][y] <= FP_DELTA && a[x][y] - b[x][y] >= FP_DELTA) {        
                continue;
            } else {
                return 0;
            }
        }
    }
    //returns 1 if every pair is equal
    return 1;
}