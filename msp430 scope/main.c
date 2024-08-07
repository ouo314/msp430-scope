#include <msp430.h> 

void initADC() {
    ADCCTL0 &= ~ADCENC;
    ADCCTL0 = ADCSHT_2 | ADCON;
    ADCCTL1 = ADCSHP;
    ADCCTL2 = ADCRES_2;
    ADCMCTL0 = ADCINCH_0;
}

void initTimer() {
    TA0CCR0 = 1024;
    TA0CCTL0 = CCIE;
    TA0CTL = TASSEL_2 | MC_1;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A_ISR(void) {
    ADCCTL0 |= ADCENC | ADCSC;
}

void initUART() {
    UCA0CTLW0 |= UCSSEL__SMCLK;
    UCA0BR0 = 104;
    UCA0BR1 = 0;
    UCA0MCTLW |= UCOS16 | UCBRF_2 | 0xD600;
    UCA0CTLW0 &= ~UCSWRST;
}

void sendUART(uint16_t data) {
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = data & 0xFF;
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = (data >> 8) & 0xFF;
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    uint16_t adcValue = ADCMEM0;
    sendUART(adcValue);
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;
    initADC();
    initTimer();
    initUART();

    __bis_SR_register(GIE);

    while (1) {
        __low_power_mode_0();
    }
}
