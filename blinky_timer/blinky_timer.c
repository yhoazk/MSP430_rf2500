/*
 * Blink led w/o wating cycles 
 * */
#include <msp430f2274.h>
#include <msp430.h>


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= 0x03;
    P1OUT = 0x03;
    BCSCTL3 |= LFXT1S_2;
    TACCTL0 = CCIE;
    TACCR0 = 1000;
    TACTL = MC_1 + TASSEL_1;
    __bis_SR_register(GIE + LPM3_bits);
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void){
  P1OUT ^= 0x03;
}
