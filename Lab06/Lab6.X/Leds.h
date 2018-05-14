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

//get the value of LATE
#define LEDS_GET() (LATE)
//sets LATE to whatever x is
#define LEDS_SET(x) LATE = x

#endif //end definition