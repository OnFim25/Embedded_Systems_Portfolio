#include "main.h"
//millisecond counter
volatile unsigned long msec = 0;
volatile unsigned long msDelay = 0;//A delay counter for delay_ms() function

void __interrupt(irq(TMR0), high_priority) TMRINT(){
    TMR0IF = 0;
    msec++;
    if(msDelay) msDelay--;
}

//ISR for all unused interrupt sources
void __interrupt(irq(default), low_priority) otherISR(){
    return;
}
