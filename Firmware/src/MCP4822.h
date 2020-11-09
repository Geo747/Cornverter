// Copyright 2019 George Rennie
#ifndef MCP4822_H
#define MCP4822_H

#include "Settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Setup and enable SPI.
// This sets all the bits in the appropriate registers to enable SPI
void MCP4822Setup(void);

// Write a value at a given accuracy to the DAC.
// Accuracy values: 0 = 0 - 2.048V, 1 = 0 - 4.096V
void MCP4822Write(uint16_t value, uint8_t channel, uint8_t accuracy);

#endif // MCP4822_H
