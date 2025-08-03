#include "main.h"

//Send a byte of manchester encoded data
void UART_SendByte(char byte){
    //wait for the transmit buffer to get empty
    while(!U5ERRIRbits.TXMTIF);
    
    //load data to transmit buffer
    U5TXB = byte;
    
    //wait till the byte is transfered
    while(!U5ERRIRbits.TXMTIF);
    
}

void UART_SendString(char* str, unsigned size){
    for(unsigned i = 0; i < size; i++){
        UART_SendByte(str[i]);
    }
}
