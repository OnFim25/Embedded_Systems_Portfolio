#include"main.h"


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
    while(!OSCSTATbits.HFOR); 
}


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
    /*Timer0 interrupt*/
    TMR0IE = 1;
    INTCON0bits.GIE = 1;
}

void INIT_I2C(){
    
    //I2C module disabled
    I2C1CON0bits.EN = 0;
    
    //I2C clock source is MFINTOSC(500KHz)
    I2C1CLK = 0b00011;
    
    //I2C Host mode, 7-bit address
    I2C1CON0bits.MODE = 0b100;
    
    //SCL frequency (FSCL) = (i2c clock source)/5
    I2C1CON2bits.FME = 0;
    
    //checks 64 I2CxCLK pulses to check bus idle state
    I2C1CON2bits.BFRET = 0b11;
    
    //Reset TX and RX i2c buffers and their IF flags
    I2C1STAT1bits.CLRBF = 1;
    
    //I2C module enabled
    I2C1CON0bits.EN = 1;
}