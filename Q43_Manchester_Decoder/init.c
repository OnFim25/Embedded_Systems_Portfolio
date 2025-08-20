#include "main.h"


//All essensial module initialisation
void INIT_SYSTEM(){
    INIT_OSC();
    
    CONFIGURE_PINS();
    
    INIT_TIMER0();
    
    
    INIT_INTERRUPTS();
}

/*FOSC = 64MHz (HFINTOSC)*/
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
 * FOSC = 64MHz
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
    //Configure RC0 as digital pin
    ANSELCbits.ANSELC0 = 0; 
    TRISCbits.TRISC0 = 1;//Tris must be set to high impedence mode when no data is sending
    
    //RC0 is selected as the CLC1 output
    RC0PPS = 0x01;
}

void INIT_INTERRUPTS(){
    /*Setting Priorities for the interrupts*/
    
    //Disable global interrupts
    INTCON0bits.GIE = 0;

    /*Timer0 interrupt*/
    TMR0IE = 1;
    TMR0IF = 0;
    
    /*Enable global interrupts*/
    INTCON0bits.GIE = 1;
    
}

#error "CLC is not complete nor correct yet"
void INIT_CLC1(){
    //CLC registers of instance CLCSELECT+1 are selected ie; CLC1
    CLCSELECT = 0;
    
    //CLC cell is in 1-Input D Flip-Flop with S and R
    CLCnCONbits.MODE = 0b100;
    
    //CLC output is not inverted
    CLCnPOLbits.POL = 0;
    
    //D1S MUX input => CLCIN0PPS
    CLCnSEL0 = 0b00000000;
    
    //D2S MUX input => NCO1
    CLCnSEL1 = 0b00101010;
    
    //Only gates 1&2 output the data for D Flip-Flop  cell 
    //Other gates is output 0 so that they won't interfere at the OR gate of the Cell
    CLCnGLS0 = 0b00000010;  //UART TX buffer
    CLCnGLS1 = 0b00001000;
    
    CLCnGLS2 = 0b00000000;  //PWM output
    CLCnGLS3 = 0b00000000;
    
    
    
    //Enable CLC1
    CLCnCONbits.EN = 1;
}