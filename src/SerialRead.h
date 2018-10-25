//Copyright 2018 George Rennie
#ifndef SERIAL_READ_H
#define SERIAL_READ_H

#include "Settings.h"
#include "MIDIDefs.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int serialReadByte(void);
byte serialAvailable(void);
void serialSetup(void);
#endif