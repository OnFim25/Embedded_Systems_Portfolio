#include "main.h"


//All essensial module initialisation
void INIT_SYSTEM(){
    //FOSC = HFINTOSC 64MHz
    INIT_OSC();
    
    CONFIGURE_PINS();
    
    //millisecond timer
    INIT_TIMER0();
    
    /*Initialize all required modules for Decoder*/
    INIT_CLC1();
    INIT_CLC2();
    INIT_CLC3();
    INIT_NCO1();
    INIT_UART5();
    
    //Initialize interrupts
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
    //Configure pins
    ANSELCbits.ANSELC3 = 0; TRISCbits.TRISC3 = 1;   //CLCIN0PPS
    ANSELAbits.ANSELA5 = 0; TRISAbits.TRISA5 = 1;   //UART5RX
    
    //RC3 is selected as CLCIN0PPS
    CLCIN0PPS = 0b010011;
    
    //RA5 is selected as UART5RX pin
    U5RXPPS = 0b000101;
}

void INIT_INTERRUPTS(){


    /*Timer0 interrupt*/
    TMR0IE = 1;
    TMR0IF = 0;
    
    /*UART5 Receiver Interrupt enable*/
    PIE13bits.U5RXIE = 1;
    
    /*Enable global interrupts*/
    INTCON0bits.GIE = 1;
}


/*
 * CLC1 acts as the D Flip-Flop with S and R latch
 * Inputs => Manchester Encoded input and NCO output
*/
void INIT_CLC1(){
    //CLC registers of instance CLCSELECT+1 are selected ie; CLC1
    CLCSELECT = 0;
    
    //CLC cell is in 1-Input D Flip-Flop with S and R
    CLCnCONbits.MODE = 0b100;
    
    //CLC output is not inverted
    CLCnPOLbits.POL = 0;
    
    //D2S MUX input => CLCIN0PPS
    CLCnSEL1 = 0b00000000;
    
    //D1S MUX input => NCO1
    CLCnSEL0 = 0b00101010;
    
    //Only gates 1&2 output the data for D Flip-Flop  cell 
    //Other gates is output 0 so that they won't interfere at the OR gate of the Cell
    CLCnGLS0 = 0b00000010;  //NCO1 output
    CLCnGLS1 = 0b00001000;  //CLCIN0PPS
    
    CLCnGLS2 = 0b00000000;  
    CLCnGLS3 = 0b00000000;
    
    
    
    //Enable CLC1
    CLCnCONbits.EN = 1;
}


/*
 * CLC2 acts as the XOR gate
 * inputs => Manchester encoded input and CLC1 output
 */
void INIT_CLC2(){
    //CLC registers of instance CLCSELECT+1 are selected ie; CLC1
    CLCSELECT = 1;
    
    //CLC cell is in OR_XOR mode
    CLCnCONbits.MODE = 0b001;
    
    //CLC output is not inverted
    CLCnPOLbits.POL = 0;
    
    //D2S MUX input => CLCIN0PPS
    CLCnSEL1 = 0b00000000;
    
    //D1S MUX input => CLC1 output
    CLCnSEL0 = 0b00110011;
    
    //Only gates 1&3 output the data for OR_XOR function
    CLCnGLS0 = 0b00000010;  //CLC1 output
    CLCnGLS1 = 0b00000000;  
    
    CLCnGLS2 = 0b00001000;  //CLCIN0PPS
    CLCnGLS3 = 0b00000000;

    //Enable CLC2
    CLCnCONbits.EN = 1;
}


/*
 * CLC3 acts as AND_OR gate 
 * Inputs => CLC2 output, FOSC and NCO1 output
 */
void INIT_CLC3(){
    //CLC registers of instance CLCSELECT+1 are selected ie; CLC1
    CLCSELECT = 2;
    
    //CLC cell is in AND_OR mode
    CLCnCONbits.MODE = 0b000;
    
    //CLC output is not inverted
    CLCnPOLbits.POL = 0;
    
    //D1S MUX input => CLC2 output
    CLCnSEL0 = 0b00110100;
    
    //D2S MUX input => FOSC
    CLCnSEL1 = 0b00001000;
    
    //D3S MUX input => NCO1 output
    CLCnSEL2 = 0b00101010;
    
    //Gates 1 and 4 takes CLC1 output and NCO1 output respectively
    //Gates 2 and 3 takes FOSC as inputs
    CLCnGLS0 = 0b00000010;  //CLC1 output
    CLCnGLS1 = 0b00001000;  //FOSC 
    
    CLCnGLS2 = 0b00001000;  //FOSC
    CLCnGLS3 = 0b00100000;  //NCO1 output
    

    //Enable CLC3
    CLCnCONbits.EN = 1;
}

void INIT_NCO1(){
    
    //NCO1 works in pulse frequency mode (PFM)
    NCO1CONbits.PFM = 1;
    
    //NCO output is active low
    NCO1CONbits.POL = 1;
    
    //NCO output is active for 128 input clock periods
    NCO1CLKbits.PWS = 0b111;
    
    //NCO clock source is CLC3
    //The NCO period will be controlled by the input clock
    NCO1CLKbits.CKS = 0b10101;
    
    //Enable NCO1
    NCO1CONbits.EN = 1;
}

void INIT_UART5(){
    //U5BRG = Fosc/[16(BaudRate)]-1; if BRGS = 0
    U5BRG = 416; //BaudRate = 9600
    
    //Baud rate generator works in normal speed
    U5CON0bits.BRGS = 0;
    
    //Receiver is enabled
    U5CON0bits.RXEN = 1;
    
    //Asynchronous 8-bit UART mode
    U5CON0bits.MODE = 0b0000;
    
    //Output data are not inverted, RX input is high in Idle state
    U5CON2bits.RXPOL = 0;
    
    //Clear RX buffer
    U5FIFObits.RXBE = 1;
    
    //Enable UART5 module
    U5CON1bits.ON = 1;
}