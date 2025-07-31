#include "main.h"

int I2C_start(char R_nW){
    uint8_t addr = 0;
    
    //Format the address for read or write
    if(R_nW == 'r')
        addr = OLED_ADDRESS | 0x01;
    else
        addr = OLED_ADDRESS & 0xFE;
    
    //Reset the I2C counter
    I2C1CNT = 2;
    
    I2C1TXB = addr;
    //Wait for bus to get Idle
    while(!I2C1STAT0bits.BFRE);

    //Send start bit
    I2C1CON0bits.S = 1;
    
    //Set when host asserts a Start condition
    while(!I2C1STAT0bits.MMA);
    
    delay_ms(1); //delay for 
    
    if(!I2C1CON1bits.ACKSTAT)
        return 0;
    else
        return 1;
}

void I2C_send(uint8_t addr){
    
    
}

void I2C_stop(){
    
}