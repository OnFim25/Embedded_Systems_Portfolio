#include "main.h"

void INIT_SYSTEM(){
    INIT_OSC();
    
    CONFIGURE_PINS();
    
    INIT_TIMER0();
    INIT_INTERRUPTS();
}

void INIT_OSC(){
    //Clock source is HFINOSC
    OSCCON1bits.NOSC = 0b110;
    
    //Clock divider is 1
    OSCCON1bits.NDIV= 0b0000;
    
    //Oscillator works in nominal frequency
    OSCTUNE = 0b000000;
    
    //Oscillator frequency is 64MHz
    OSCFRQ = 0b1000;
    
    //HFINTOSC explicitly enabled
    OSCENbits.HFOEN = 1;
    
    //Wait for Oscillator to begin
    while(!OSCSTATbits.HFOR);   //HFINTOSC ready flag
}

/*
 * clock source : FOSC/4
 * Post scalar  : 4
 * pre scalar   : 16
 * millisecond timer  
 */
void INIT_TIMER0(){
    
    //Clock source FOSC/4 
    T0CON1bits.CS = 0b010;
    
    //1:16 Pre scalar
    T0CON1bits.CKPS = 0b0100;
    
    // 1:4 Post scaler
    T0CON0bits.OUTPS = 0b0011;
    
    //Timer0 8-bit mode max count value
    TMR0H = 250;
    
    //Timer0 enabled
    T0CON0bits.EN = 1;
    
}

void CONFIGURE_PINS(){
    
}

void INIT_INTERRUPTS(){
    /*Setting Priorities for the interrupts*/
    
    //Disable global interrupts
    INTCON0bits.GIE = 0;

    
    
    /*Timer0 interrupt*/
    TMR0IE = 1;
    TMR0IF = 0;
    INTCON0bits.GIE = 1;
    
}
