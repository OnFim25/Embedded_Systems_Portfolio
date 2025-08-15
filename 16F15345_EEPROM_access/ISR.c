#include "main.h"

volatile unsigned long msCount = 0;
volatile unsigned long delayCount = 0;

void __interrupt()ISR(){
    if(TMR0IF){
        TMR0IF = 0;
        msCount++;
        if(delayCount) delayCount--;
    }
}
