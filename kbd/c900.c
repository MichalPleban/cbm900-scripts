
#include "main.h"
#include "c900.h"
#include "led.h"

unsigned char C900_hex_codes[] =
{ 0x0B, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x1E, 0x30, 0x2E, 0x20, 0x12, 0x21 };

void C900_output(unsigned char code)
{
    unsigned char loop;

    C900_CLOCK_HIGH;
    C900_DATA_OUTPUT;
    C900_CLOCK_OUTPUT;

    LED2_ON;

    /*
    C900_DATA_LOW;
    for(loop = 0; loop < 8; loop++)
    {
        C900_CLOCK_HIGH;
        C900_DELAY;
        C900_CLOCK_LOW;
        C900_DELAY;
    }
    */
    
    C900_DELAY;
    C900_DATA_HIGH;
    C900_DELAY;
    C900_CLOCK_LOW;
    C900_DELAY;

    for(loop = 0; loop < 16; loop++)
    {
        C900_CLOCK_HIGH;
        C900_DELAY;
        if(code & 1)
            C900_DATA_HIGH;
        else
            C900_DATA_LOW;
        C900_DELAY;
        C900_CLOCK_LOW;
        C900_DELAY;
        code = code >> 1;
    }

    C900_CLOCK_HIGH;
    C900_DELAY;
    C900_DATA_LOW;
    C900_DELAY;
    C900_CLOCK_LOW;
    C900_DELAY;
    LED2_OFF;

    C900_CLOCK_INPUT;
    C900_DATA_INPUT;

    C900_DELAY;
}

void C900_hex(unsigned char code)
{
    C900_output(C900_hex_codes[code>>4]);
    C900_output(C900_hex_codes[code&15]);
}