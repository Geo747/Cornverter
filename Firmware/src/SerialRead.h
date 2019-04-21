//Copyright 2019 George Rennie
#ifndef SERIALREAD_H
#define SERIALREAD_H

#include "Settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*Read a single byte from the serial buffer if available.
  Returns -1 if there is no byte in the buffer
*/
int serialReadByte(void);

/*Returns non zero if there is at least one byte in the
  serial buffer to be read
*/
uint8_t serialAvailable(void);

//Intialises registers for serial reading at baud rate defined by BAUD_RATE 
void serialSetup(void);
#endif