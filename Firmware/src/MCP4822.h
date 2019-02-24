//Copyright 2018 George Rennie
#ifndef MCP4822_H
#define MCP4822_H

#include "Settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void MCP4822Setup(void);
void MCP4822Write(uint16_t value, uint8_t channel); //Set the corresponding one of the 2 outputs for that channel with that value
void MCP4822SetAccuracy(uint8_t accuracy); //0 = 0 - 2.048V, 1 = 0 - 4.096V

#endif