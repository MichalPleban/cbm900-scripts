

#include "main.h"
#include "c900.h"
#include "led.h"

void LED_init()
{
    CCP2CON = 0b00001100; 
    PR2 = 255;
    CCPTMRSbits.C2TSEL = 0b00;
    T2CONbits.T2CKPS = 0b00;
    T2CONbits.TMR2ON = 1;
    CCP2CONbits.DC2B = 0;
}
