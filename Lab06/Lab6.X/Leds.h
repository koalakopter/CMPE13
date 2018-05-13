//LAB 6 PART 1 bounce_switch.c
//created by Julian To
#ifndef LEDS_H
#define LEDS_H

#include "BOARD.h"
#include <xc.h>

#define LEDS_INIT() do {
TRISE = 0xF6; \//1111 0110 
LATE = 0x09; \//0000 1001
} while (0)
    
#define LEDS_GATE() 

#define LEDS_SET(x)

#endif //end definition