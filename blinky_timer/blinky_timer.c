/*
 * Blink led w/o wating cycles
 * */
#include <msp430f2274.h>
#include <msp430.h>


// volatile register int *r asm ("R13");
int count = 1000;
void main(void) {
    /**
     * WDTCTL (16b): Watch dog control 16b, MSB is fix to WDTPW
     * WDTPW (0x5A00): Password needed to take the operation
     * WDTHOLD (0x0080): Stops the watch dog timer when set to 1
     */
    WDTCTL = WDTPW + WDTHOLD;
    /**
     * Set the direction of the IO in P1
     * and the out value
     * */
    P1DIR |= 0x03;
    // P1OUT = 0x00;
    /**
     * BCSCTL3 (8b): Basic Clock system control
     * LFXT1s_2(0x20): Low freq Xtal range select: Mode 2 for LFXT1: VL0
     * VLO internal very low power low freq oscillator typically 12khz
     * */
    BCSCTL3 |= LFXT1S_2; // set the clock src for VLO
    /** Timer A Capture Compare control
     * Timer A has 2 interrupt srcs
     * CCIE: Capture Compare Interrupt enable 1 == enabled
     */
    TACCTL0 = CCIE; // Enable the interrupt in timer a
    /**
     *
     */
    TACCR0 = count;
    // MC = 1 Mode up: timer counts from zero to TACCR0
    // TASSEL_1: clock src for timer a = ACLK
    // Divide input by 2**2
    TACTL = MC_1 + TASSEL_1 + ID_3;// + TAIE + ID_3;
    __bis_SR_register(GIE + LPM3_bits);
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void){
  P1OUT ^= 0x03;
  TA0CCR0 = count++;
  // *r++;
  //TACCR0 = 65535/2;
}
