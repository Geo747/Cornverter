//Copyright 2018 George Rennie
#ifndef MCP4822_H
#define MCP4822_H

#include "Settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void MCP4822Setup(void);

//Set the corresponding one of the 2 outputs for that channel with that value
//Accuracy values: 0 = 0 - 4V, 1 = 0 - 8V
void MCP4822Write(uint16_t value, uint8_t channel, uint8_t accuracy);

#endif