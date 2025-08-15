#include "main.h"

//A waiting delay in milli seconds
void delay_msec(unsigned long ms){
    delayCount = ms;
    while(delayCount);
}
