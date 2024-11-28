#include <htc.h>
#include "main.h"
#include "led.h"

#ifndef AT_H
#define	AT_H

#define AT_INIT TRISBbits.TRISB7 = TRISBbits.TRISB6 = LATBbits.LATB7 = LATBbits.LATB6 = 1

#define AT_DELAY __delay_ms(20)

#define AT_DATA PORTBbits.RB6
#define AT_CLOCK PORTBbits.RB7

#define AT_DATA_OUTPUT TRISBbits.TRISB6 = 0
#define AT_CLOCK_OUTPUT TRISBbits.TRISB7 = 0

#define AT_DATA_INPUT TRISBbits.TRISB6 = 1
#define AT_CLOCK_INPUT TRISBbits.TRISB7 = 1

#define AT_CLOCK_HIGH LATBbits.LATB7 = 1
#define AT_CLOCK_LOW LATBbits.LATB7 = 0

#define AT_DATA_HIGH LATBbits.LATB6 = 1
#define AT_DATA_LOW LATBbits.LATB6 = 0

#define AT_STATE_F0 0x01
#define AT_STATE_E0 0x02
#define AT_STATE_E1 0x04

unsigned char AT_state;

#define AT_FLAG_LCTRL 0x01
#define AT_FLAG_RCTRL 0x02
#define AT_FLAG_CTRL (AT_FLAG_LCTRL|AT_FLAG_RCTRL)
#define AT_FLAG_LSHIFT 0x04
#define AT_FLAG_RSHIFT 0x08
#define AT_FLAG_SHIFT (AT_FLAG_LSHIFT|AT_FLAG_RSHIFT)
#define AT_FLAG_LALT 0x10
#define AT_FLAG_RALT 0x20
#define AT_FLAG_ALT (AT_FLAG_LALT|AT_FLAG_RALT)

unsigned char AT_flags;

unsigned char AT_input();
void AT_output(unsigned char code);
unsigned char AT_command(unsigned char code);
void AT_process(unsigned char code);

#endif	/* AT_H */

