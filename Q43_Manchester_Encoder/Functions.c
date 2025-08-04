#include "main.h"

void delay_msec(unsigned ms){
    delayCount = (unsigned long)ms;
    while(delayCount);
}

//Send a byte of manchester encoded data
void UART_SendByte(char byte){
    //wait for the transmit buffer to get empty
    while(!U5ERRIRbits.TXMTIF);
    
    //RC0 is set to output for data transmission
    TRISCbits.TRISC0 = 0;
    
    //Reload PWM period and parameters and enable pwm module
    PWM1CONbits.LD = 1;
    PWM1CONbits.EN = 1;
    
    //load data to transmit buffer
    U5TXB = byte;
    
    //wait till the byte is transfered
    while(!U5ERRIRbits.TXMTIF);
    
    //Reset TRIS bit
    TRISCbits.TRISC0 = 1;
    
    //Disable PWM module
    PWM1CONbits.EN = 0;
    
}

void UART_SendString(char* str, unsigned size){
    for(unsigned i = 0; i < size; i++){
        UART_SendByte(str[i]);
    }
}
