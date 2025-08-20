#include "main.h"

//milli second waiting delay
void delay_msec(unsigned long ms){
    delayCount = ms;
    while(delayCount);
}
