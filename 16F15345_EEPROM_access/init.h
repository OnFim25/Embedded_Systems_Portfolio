/* 
 * File:   init.h
 * Author: PC
 *
 * Created on 15 August, 2025, 12:30 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
    
    void INIT_SYSTEM(void);
    
    void INIT_OSC(void);
    void INIT_TIMER0(void);
    void INIT_INTERRUPTS(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

