/* 
 * File:   init.h
 * Author: PC
 *
 * Created on July 29, 2025, 5:04 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
    
    void INIT_SYSTEM(void);
    void CONFIGURE_PINS(void);
    void INIT_OSC(void);
    void INIT_TIMER0(void);
    void INIT_INTERRUPTS(void);
    void INIT_I2C(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

