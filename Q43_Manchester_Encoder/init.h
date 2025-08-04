/* 
 * File:   init.h
 * Author: PC
 *
 * Created on 1 August, 2025, 5:29 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
    
    void INIT_SYSTEM(void);
    void INIT_OSC(void);
    
    void CONFIGURE_PINS(void);
    
    void INIT_TIMER0(void);
    void INIT_INTERRUPTS(void);
    
    void INIT_CLC1(void);
    void INIT_UART5(void);
    void INIT_PWM(void);




#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

