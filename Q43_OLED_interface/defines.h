/* 
 * File:   defines.h
 * Author: PC
 *
 * Created on 31 July, 2025, 12:05 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif

    //64MHz HFINTOSC
    #define _XTAL_FREQ 64E6 
    
    //SA0 is pulled Low and defult address is in write mode
    #define OLED_ADDRESS 0b01111000 



#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */

