
#include <htc.h>

#include "main.h"
#include "led.h"
#include "c900.h"
#include "at.h"
#include "trans.h"

//config bits that are part-specific for the PIC16F1829
__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_ON & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
__CONFIG(WRT_OFF & PLLEN_ON & STVREN_OFF & LVP_OFF);

void key(short int key)
{
    C900_output(0x0D);
    C900_hex(key);
    C900_output(0x0D);
    C900_output(0x2A);
    C900_output(key);
    C900_output(0xAA);
    C900_output(0x1C);
}

void main(void)
{
    while(1)
    {
        trans_main();
    }
    short int c;


    // Port A input = switch
    TRISAbits.TRISA2 = 1;                             //switch as input
    ANSELAbits.ANSA2 = 0;                             //digital switch

    __delay_ms(10000);
    LED0_ON;

    /*
    while(1)
    {
        __delay_ms(100000);
        AT_output(0xFF);
        C900_hex(AT_input());
    }
    */

//    AT_output(0xED);
//    AT_output(0x07);

    while(1)
    {
        C900_hex(AT_input());
    }
    c = 0x3B;
    while(1)
    {
        while (1)
        {
            if (PORTAbits.RA2== 0)
                break;
        }

//        key(c);
        C900_output(0x22);
        c++;
        __delay_ms(100);

        while (1)
        {
            if (PORTAbits.RA2== 1)
                break;
        }
    }
                                                      //setup switch (SW1)
}