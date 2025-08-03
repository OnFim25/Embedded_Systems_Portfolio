/* 
 * File:   Functions.h
 * Author: PC
 *
 * Created on 2 August, 2025, 1:05 PM
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"

void UART_SendByte(char);
void UART_SendString(char*, unsigned);

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTIONS_H */

