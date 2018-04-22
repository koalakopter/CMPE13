#include "MatrixMath.h"

/* Im gonna need this a lot
     for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {

        }

    }*/

//counter for rows
int x;
//counter for columns
int y;

//test equality of two 3 by 3 matricies
//returns 1 if true, 0 if false

int MatrixEquals(float a[3][3], float b[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            if (a[x][y] - b[x][y] <= FP_DELTA && a[x][y] - b[x][y] >= -FP_DELTA) {
                continue;
            } else {
                return 0;
            }
        }
    }
    //returns 1 if every pair is equal
    return 1;
}

void MatrixMultiply(float a[3][3], float b[3][3], float c[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {

        }

    }
}

void MatrixAdd(float a[3][3], float b[3][3], float c[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            c[x][y] = a[x][y] + b[x][y];
        }

    }
}

//prints the contents of a 3 by 3 matrix into a nice little grid

void MatrixPrint(float a[3][3])
{
    for (x = 0; x < 3; x++) {
        printf("\n | ");
        for (y = 0; y < 3; y++) {
            printf("%f, ", a[x][y]);
        }
        printf(" | ");
    }
    printf("\n"); //new lines to make it look nicer
}
