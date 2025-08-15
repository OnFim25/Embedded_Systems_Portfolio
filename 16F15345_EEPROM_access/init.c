#include "main.h"

void INIT_SYSTEM(){
    INIT_OSC();
}

void INIT_OSC(){
    
    //Clock source = HFINTOSC
    OSCCON1bits.NOSC = 0b110;
    
    //Clock divider = 1
    OSCCON1bits.NDIV = 0b0000;
    
    //Oscillator Nominal frequency is 32MHz
    OSCFRQ = 0b110;
    
    //Enable HFINTOSC
    OSCENbits.HFOEN = 1;
    
    //Wait for oscillator to start
    while(!OSCSTATbits.HFOR);
    
}
/*
 *  Name: INIT_TIMER0
 *  Purpose: milli second timer for system tick counts
 *  calculation: Clock source = 32MHz(HFINTOSC)
 *               pre_scalar = 32, post_scalar = 4, max_count = 250
 *               timer0_delay = (pre_scalar * post_scalar * max_count)/HFINTOSC = 1mS
 */
void INIT_TIMER0(){
        
    //HFINTOSC as clock source
    T0CON1bits.T0CS = 0b011;
    
    //Timer0 Pre scalar 1:32
    T0CON1bits.T0CKPS = 0b0101;
    
    //Timer0 Post scalar 1:4
    T0CON0bits.T0OUTPS = 0b0011;
    
    //Timer0 max count
    TMR0H = 250;
    
    //Start timer 0
    T0CON0bits.T0EN = 1;
}

void INIT_INTERRUPTS(){
    /*Timer 0 interrupts*/
    
    //Timer0 interrupt enabled
    PIE0bits.TMR0IE = 1;
    
    
    /*Global interrupt enable*/
    
    INTCONbits.GIE = 1;
}