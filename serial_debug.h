/*
 * serial_debug.h
 *
 *      Author: YOUR NAME
 */

#ifndef SERIAL_DEBUG_H_
#define SERIAL_DEBUG_H_

#include "circular_buffer.h"
#include "msp.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

extern volatile char Rx_String[];
extern volatile uint16_t Rx_Char_Count;
extern volatile bool ALERT_STRING;
extern Circular_Buffer* Tx_Buffer;

//****************************************************************************
// Initializes the circular buffers used to transmit and receive data from the
// serial debug interface. It will also initialize the UART interface to enable
// interrupts.
// ****************************************************************************/
void serial_debug_init(void);

//****************************************************************************
// Prints a string to the serial debug UART
// ****************************************************************************/
void serial_debug_put_string(char* s);

//****************************************************************************
// By implementing putchar(), puts(), printf(), etc will now work.
// ****************************************************************************/
int fputc(int c, FILE* stream);

#endif /* SERIAL_DEBUG_H_ */
