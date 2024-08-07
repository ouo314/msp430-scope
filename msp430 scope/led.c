#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               
    PM5CTL0 &= ~LOCKLPM5;                   
                                            
    P1DIR |= 0x01;                          

    for(;;) {
        volatile unsigned int i;           

        P1OUT ^= 0x01;                    

        i = 10000;                         
        do i--;
        while(i != 0);
    }
}
