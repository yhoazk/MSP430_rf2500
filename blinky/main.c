/*
 * La board con el RF transciever tiene el micro MSP430F2274
 * */
#include <msp430f2274.h>
//#include <msp430.h>


void wait(void);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= 0x01;
    P1OUT = 0X01;

    for(;;){
        P1OUT ^= 0x01;
        wait();
    }
}



void wait(void)
{
    volatile int i;
    for(i=0; i < 32000; i++);
}
