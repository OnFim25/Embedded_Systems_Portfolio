#include "main.h"

void __interrupt() ISR(){
    if(TMR0IF){
        TMR0IF = 0;
    }
}
