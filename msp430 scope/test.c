#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   

    UCA0CTLW0 |= UCSSEL__SMCLK;
    UCA0BR0 = 104;   
    UCA0BR1 = 0;
    UCA0MCTLW = UCOS16 | UCBRF_2 | 0xD600;  
    UCA0CTLW0 &= ~UCSWRST;  

    while (1) {
        while (!(UCA0IFG & UCTXIFG)); 
        UCA0TXBUF = 'A';  
        __delay_cycles(1000000);  
    }
}
