#include "main.h"

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
    
    /*Enable global interrupts*/
    INTCON0bits.GIE = 1;
    
}

void INIT_UART5(){
    //U5BRG = Fosc/[16(BaudRate)]-1; if BRGS = 0
    U5BRG = 416; //BaudRate = 9600
    
    //Baud rate generator works in normal speed
    U5CON0bits.BRGS = 0;
    
    //Transmission is enabled
    U5CON0bits.TXEN = 1;
    
    //Asynchronous 8-bit UART mode
    U5CON0bits.MODE = 0b0000;
    
    //Output data are not inverted, TX output is high in Idle state
    U5CON2bits.TXPOL = 0;
    
    //Enable UART5 module
    U5CON1bits.ON = 1;
}

/*For correct manchester encoding, PWM should have twice the data frequency*/
void INIT_PWM(){
    //No PWM external trigger sources
    PWM1ERS = 0b11111;
    
    //PWM clock source = FOSC
    PWM1CLK = 0b00010;
    
    //PWM1PR = (Fpwmclk * Period / 2) - 1
    PWM1PR = 1665;  //PWM freq = 1/Period = 19200Hz
    
    //Reload PWM period register
    PWM1CONbits.LD = 1;
}

//Initialize CLC for XOR operation (Manchester encoding)
void INIT_CLC1(){
    //CLC registers of instance CLCSELECT+1 are selected ie; CLC1
    CLCSELECT = 0;
    
    //CLC cell is in OR_XOR
    CLCnCONbits.MODE = 0b001;
    
    //CLC output is not inverted
    CLCnPOLbits.POL = 0;
    
    //D1S MUX input => PWM1S1P1_OUT
    CLCnSEL0 = 0b01000010;
    
    //D2S MUX input => UART5 TX
    CLCnSEL1 = 0b01111111;
    
    //Only gates 1&3 output the data for OR_XOR cell inputs inputs are selected
    //Other gates must output 0 so that they won't interfere at the OR gate of the Cell
    CLCnGLS0 = 0b00000010;
    CLCnGLS1 = 0b00000000;
    
    CLCnGLS2 = 0b00001000;
    CLCnGLS3 = 0b00000000;
    
    
    
    //Enable CLC1
    CLCnCONbits.EN = 1;
}