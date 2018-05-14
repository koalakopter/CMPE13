//LAB 6 PART 1 bounce_switch.c
//created by Julian To
#ifndef LEDS_H
#define LEDS_H

#include "BOARD.h"
#include <xc.h>

#define LEDS_INIT() do{ \
TRISE = 0;    \//zero
LATE = 0x0;      \//?
}while (0)

#define LEDS_GET() (LATE)
#define LEDS_SET(x) (LATE = x)

#endif //end definition