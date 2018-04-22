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

float counter; //just to keep track of things

void MatrixMultiply(float a[3][3], float b[3][3], float c[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            counter = 0; //start the counter at zero
            counter += (a[x][0] * b[0][y]);
            counter += (a[x][1] * b[1][y]);
            counter += (a[x][2] * b[2][y]);

            c[x][y] = counter;
        }

    }
}
//adds two 3 by 3 matrices together, self-explanatory

void MatrixAdd(float a[3][3], float b[3][3], float c[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            c[x][y] = a[x][y] + b[x][y];
        }

    }
}

//multiplies a 3 by 3 matrix by a scalar
//s is the scalar

void MatrixScalarMultiply(float s, float a[3][3], float b[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            b[x][y] = (s * a[x][y]);
        }

    }
}

//adds a 3 by 3 matrix with a scalar
//x is the scalar

void MatrixScalarAdd(float s, float a[3][3], float b[3][3])
{
    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            b[x][y] = (s + a[x][y]);
        }

    }
}

//calculates the cross product, or determinant, of a 3 by 3 matrix
//formula for a cross product 
// a11[(a22*a33)-(a23*a32)] - a12[(a21*a33)-(a23*a31)] + a13[(a21*a32)-(a22*a31)]
// arrays start at zero so subtract 1 from every subscript

float MatrixDeterminant(float a[3][3])
{
    counter = 0;
    counter += ((a[1][1] * a[2][2])-(a[1][2] * a[2][1])) * a[0][0];
    counter -= ((a[1][0] * a[2][2])-(a[1][2] * a[2][0])) * a[0][1];
    counter += ((a[1][0] * a[2][1])-(a[1][1] * a[2][0])) * a[0][2];
    return counter;
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
