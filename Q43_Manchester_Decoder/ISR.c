#include "main.h"

volatile unsigned long ticks = 0;
volatile unsigned long delayCount = 0;



void __interrupt() ISR(){
    //Triggers every milli second
    if(TMR0IF){
        TMR0IF = 0;
        ticks++;
        if(delayCount) delayCount--;
    }
    
    //UART5 Receive interrupt
    else if(U5RXIF){
        U5RXIF = 0;
        
        //Received data is stored
        uartReceivedData = U5RXB;
    }
}
