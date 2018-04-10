// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "SimpleMath.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries


// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

#define QX 1.5
#define QY 2.8
#define PX -2.3
#define PY 8.6
#define DX (QX-PX)
#define DY (QY-PY)
//define bigger function



int main()
{
    BOARD_Init();
    {

        /******************************** Your custom code goes below here *******************************/

        double mathHypot = hypotf(DX, DY);
        printf("Hypot returned %f and should return %f\r\n", mathHypot, 6.9340);

        double mathAtan2 = atan2(QX, QY);
        printf("Atan2 returned %f and should return %f\r\n", mathAtan2, .4918);

        //test for AddTwoNumbers
        int test, x = 13, y = 10;
        test = AddTwoNumbers(x, y);
        printf("Adding %d and %d with AddTwoNumbers yields: %d \n", (int) x, (int) y, (int) test);

        //test for IncrementByOne
        int test2, z = 68;
        test2 = IncrementByOne(68);
        printf("Performing the IncrementByOne function on: %d yields: %d \n", (int)z, (int) test2);

        //testing the Bigger function, which takes two inputs and returns the greater number
        int big = 420;
        int small = 69;

        int compare = Bigger(big, small);
        printf("Comparing two numbers, %d and %d. Should return: %d \n", (int) big, (int) small, (int) compare);
        /*************************************************************************************************/

        // You can never return from main() in an embedded system (one that lacks an operating system).
        // This will result in the processor restarting, which is almost certainly not what you want!
        while (1);
    }
}



