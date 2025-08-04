/* 
 * File:   ISR.h
 * Author: PC
 *
 * Created on 1 August, 2025, 5:37 PM
 */

#ifndef ISR_H
#define	ISR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "main.h"
    void __interrupt() ISR(void);
    extern volatile unsigned long ticks;
    extern volatile unsigned long delayCount;


#ifdef	__cplusplus
}
#endif

#endif	/* ISR_H */

