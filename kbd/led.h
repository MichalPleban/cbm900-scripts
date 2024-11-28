
#ifndef LED_H
#define	LED_H

#define LED_INIT TRISC = LATC = 0

#define LED0_ON LATCbits.LATC0 = 1
#define LED0_OFF LATCbits.LATC0 = 0

#define LED1_ON LATCbits.LATC1 = 1
#define LED1_OFF LATCbits.LATC1 = 0

#define LED2_ON LATCbits.LATC2 = 1
#define LED2_OFF LATCbits.LATC2 = 0

#define LED3_SET(a) CCPR2L = (a)

void LED_init();

#endif	/* LED_H */

