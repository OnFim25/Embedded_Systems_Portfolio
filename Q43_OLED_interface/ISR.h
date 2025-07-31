/* 
 * File:   ISR.h
 * Author: PC
 *
 * Created on July 29, 2025, 9:34 PM
 */

#ifndef ISR_H
#define	ISR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "main.h"
    
    extern volatile unsigned long msec;
    extern volatile unsigned long msDelay;
    
    void __interrupt(irq(TMR0), high_priority) ISR(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ISR_H */

