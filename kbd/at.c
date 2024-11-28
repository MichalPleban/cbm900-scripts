
#include "main.h"
#include "at.h"
#include "led.h"

#define AT_CLOCK_WAIT do { while(!AT_CLOCK); while(AT_CLOCK); } while(0)

#define AT_LOOP_MAX 5000

unsigned char AT_state;
unsigned char AT_flags;

unsigned char AT_input()
{
    unsigned char code, loop, par;
    int i;

    AT_CLOCK_HIGH;
    AT_CLOCK_INPUT;
    AT_DATA_INPUT;

    // Wait for clock pulse (start bit)
    while(!AT_CLOCK);
    for(i = 0; i < AT_LOOP_MAX; i++)
    {
        if(!AT_CLOCK) break;
    }
    if(i == AT_LOOP_MAX)
    {
        return 0;
    }

    LED0_ON;

    code = 0;
    par = 1;
    for(loop = 0; loop < 8; loop++)
    {
        // Shift incoming byte right
        code >>= 1;

        // Wait for clock pulse (data bit)
        AT_CLOCK_WAIT;

        // Check incoming data bit
        if(AT_DATA)
        {
            code |= 0x80;
            par = par ^ 0x01;
        }
    }
    
    // Wait for clock pulse (parity bit)
    AT_CLOCK_WAIT;

    // Wait for clock pulse (stop bit)
    AT_CLOCK_WAIT;
    while(!AT_CLOCK);

    LED0_OFF;

    /*
    AT_DATA_HIGH;
    AT_CLOCK_LOW;
    AT_CLOCK_OUTPUT;
    AT_DATA_OUTPUT;
    */
    AT_CLOCK_OUTPUT;
    AT_DATA_OUTPUT;
    AT_CLOCK_LOW;
    
    return code;
}

void AT_output(unsigned char code)
{
    unsigned char loop, par;

    // Abort transmission by taking clock low
    AT_CLOCK_LOW;
    AT_CLOCK_OUTPUT;
    AT_DELAY;

    // Release the clock line
    AT_CLOCK_HIGH;
    AT_CLOCK_INPUT;

    // Set data line low
    AT_DATA_OUTPUT;
    AT_DATA_LOW;

    // Wait for a clock pulse (start bit)
    while(AT_CLOCK);
    LED1_ON;

    par = 1;
    for(loop = 0; loop < 8; loop++)
    {
        // Clock outgoing data bit
        if(code & 0x01)
        {
            AT_DATA_HIGH;
            par = par ^ 0x01;
        }
        else
        {
            AT_DATA_LOW;
        }

        // Wait for clock pulse (data bit)
        AT_CLOCK_WAIT;

        // Shift outgoing byte right
        code >>= 1;
    }

    // Output parity bit
    if(par)
        AT_DATA_HIGH;
    else
        AT_DATA_LOW;

    // Wait for clock pulse (parity bit)
    AT_CLOCK_WAIT;
    
    // Output stop bit
    AT_DATA_INPUT;

    // Wait for clock pulse (stop bit)
    AT_CLOCK_WAIT;

    // Wait for clock pulse (ACK bit)
    while(!AT_CLOCK);

    AT_CLOCK_LOW;
    AT_CLOCK_OUTPUT;

    LED1_OFF;
}

unsigned char AT_command(unsigned char code)
{
    AT_output(code);
    return AT_input();
}

void AT_process(unsigned char code)
{
    if(code == 0xF0)
        AT_state |= AT_STATE_F0;
    else if(code == 0xE0)
        AT_state |= AT_STATE_E0;
    else if(code == 0xE1)
        AT_state |= AT_STATE_E1;
    else
    {
        AT_state = 0;
    }
}