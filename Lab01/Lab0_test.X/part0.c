/*
 * File:   Part0.c
 * Author: julia
 *
 * Created on April 5, 2018, 1:53 PM
 */


#include "xc.h"
#include "BOARD.h"
//added for part4
/*
#include "Ascii.h"
#include "Oled.h"
#include "OledDriver.h" 
*/
void main(void)
{
    BOARD_Init();
    OledInit();
    OledDrawString("Hello \nWorld! \n");
    OledUpdate();
    printf("Hello World\n");
    while(1); 
}
