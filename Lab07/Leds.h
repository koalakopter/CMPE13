//LAB 6 PART 1 bounce_switch.c
//created by Julian To
#ifndef LEDS_H
#define LEDS_H

#include "BOARD.h"
#include <xc.h>

#define LEDS_INIT() do{ \
    TRISE = 0x0;    \
    LATE = 0x0;      \
}while (0);

//sets LATE to whatever input is (usually a series of 8 bits)
#define LEDS_SET(input) (LATE = input)
//get the value of the LATE register
#define LEDS_GET() (LATE)


#endif //end definition