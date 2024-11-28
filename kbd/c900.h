#include <htc.h>
#include "main.h"
#include "led.h"

#ifndef C900_H
#define	C900_H

#define C900_INIT TRISBbits.TRISB5 = TRISBbits.TRISB4 = LATBbits.LATB5 = LATBbits.LATB4 = 1

#define C900_DELAY __delay_ms(1)

#define C900_DATA_OUTPUT TRISBbits.TRISB4 = 0
#define C900_CLOCK_OUTPUT TRISBbits.TRISB5 = 0

#define C900_DATA_INPUT TRISBbits.TRISB4 = 1
#define C900_CLOCK_INPUT TRISBbits.TRISB5 = 1

#define C900_CLOCK_HIGH LATBbits.LATB5 = 1
#define C900_CLOCK_LOW LATBbits.LATB5 = 0

#define C900_DATA_HIGH LATBbits.LATB4 = 1
#define C900_DATA_LOW LATBbits.LATB4 = 0

unsigned char C900_hex_codes[];

void C900_output(unsigned char code);
void C900_hex(unsigned char code);

#endif	/* C900_H */

