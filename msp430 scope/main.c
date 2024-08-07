

void initADC() {
    ADCCTL0 &= ~ADCENC;
    ADCCTL0 = ADCSHT_2 | ADCON;
    ADCCTL1 = ADCSHP;
    ADCCTL2 = ADCRES_2;
    ADCMCTL0 = ADCINCH_0;
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


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

	return 0;
}
