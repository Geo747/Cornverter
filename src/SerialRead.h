//Copyright 2018 George Rennie
#ifndef SERIALREAD_H
#define SERIALREAD_H

#include "Settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int serialReadByte(void);
byte serialAvailable(void);
void serialSetup(void);
#endif