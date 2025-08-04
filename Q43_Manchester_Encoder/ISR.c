#include "main.h"

volatile unsigned long ticks = 0;
volatile unsigned long delayCount = 0;

//Triggers every milli second
void __interrupt() ISR(){
    if(TMR0IF){
        TMR0IF = 0;
        ticks++;
        if(delayCount) delayCount--;
    }
}
