// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

#include "Oled.h"
#include "OledDriver.h"
#include "Ascii.h"
// User libraries


// **** Set macros and preprocessor directives ****
#define TRUE 1
#define FALSE 0

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

struct AdcResult {
    uint8_t event;
    uint16_t value;
};

//struct that stores data (IDK what good variable name I can give this....)
struct AdcResult data;
// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Enable interrupts for the ADC
    ConfigIntADC10(ADC_INT_PRI_2 | ADC_INT_SUB_PRI_0 | ADC_INT_ON);

    // Set B2 to an input so AN0 can be used by the ADC.
    TRISBCLR = 1 << 2;

    // Configure and start the ADC
    // Read AN0 as sample a. We don't use alternate sampling, so setting sampleb is pointless.
    SetChanADC10(ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN2);
    OpenADC10(
            ADC_MODULE_ON | ADC_IDLE_CONTINUE | ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON,
            ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_8 |
            ADC_BUF_16 | ADC_ALT_INPUT_OFF,
            ADC_SAMPLE_TIME_29 | ADC_CONV_CLK_PB | ADC_CONV_CLK_51Tcy2,
            ENABLE_AN2_ANA,
            SKIP_SCAN_ALL
            );
    EnableADC10();

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to the Lab 6 Part 2 by Julian To. ME NO REMOVE\n");

    double percentage;
    //magic number for string length
    int magicNum = 88;
    //create an array of characters to pass into drawString
    char string1[magicNum];
    //starts the LED display
    OledInit();

    //constantly reads the potentiometer values
    while (1) {
        //set percentage to data.value so I can print it
        percentage = (data.value / 1023.0)*100.0;
        //copies a formatted string into variable string, so it can be printed out
        //MAX LINE LENGTH ON SCREEN IS 20 CHARS
        sprintf(string1, "VAL OF POTENTIOMETER:\n%d\nPERCENTAGE OF TOTAL:\n%.0f%%", data.value, percentage);

        //print the strings
        //OledDrawString(string2);
        //OledUpdate; //updates the display screen

        OledDrawString(string1);
        OledUpdate();
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the ISR for the ADC1 peripheral. It runs continuously triggered by the hardware directly
 * and not called by any code, as all interrupts are. During each run it reads all 8 samples from
 * the ADC (registers ADC1BUF0 through ADC1BUF7), averages them, and stores them in a module-level
 * AdcResult struct. If this averaged ADC value has changed between this run and the last one, the
 * event flag in the AdcResult struct is set to true.
 */
void __ISR(_ADC_VECTOR, IPL2AUTO) AdcHandler(void)
{
    //get the average of the registers, then store it in an unsigned 16 bit integer
    uint16_t average = ((ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8.0);
    if (average != data.value) {
        data.value = average;
        data.event = TRUE;
    }
    data.value = average;
    // Clear the interrupt flag.
    INTClearFlag(INT_AD1);


}