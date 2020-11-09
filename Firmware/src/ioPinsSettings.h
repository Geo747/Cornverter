// Copyright 2019 George Rennie

// NOTE: To add a new pin, add it in the following places:
//   -ioPinsStruct declaration
//   -ioPins definition
//   -ioPinsSetup function

#ifndef IOPINSSETTINGS_H
#define IOPINSSETTINGS_H
#include <inttypes.h>
#include <avr/io.h>

// Struct to store register mapping for each used pin
typedef struct {
  char portLetter;
  uint8_t bit;
  uint8_t direction;
} ioPinStruct;

// Struct to store register mapping for all used pins
typedef struct {
  ioPinStruct gate1;
  ioPinStruct gate2;

  ioPinStruct digi1ch1;
  ioPinStruct digi2ch1;
  ioPinStruct digi3ch1;
  ioPinStruct digi1ch2;
  ioPinStruct digi2ch2;
  ioPinStruct digi3ch2;

  ioPinStruct ana1ch1;
  ioPinStruct ana2ch1;
  ioPinStruct ana1ch2;
  ioPinStruct ana2ch2;

  ioPinStruct clockOut;
  ioPinStruct resetOut;

  ioPinStruct MCP4822CS;
  ioPinStruct MCP4822MOSI;
  ioPinStruct MCP4822SCK;

} ioPinsStruct;

// Struct with pin data in. Pin data is defined in ioPinsSettings.c
extern const ioPinsStruct ioPins;

// Returns a pointer to the port register for a given pin
volatile uint8_t* ioPinsGetPORT(ioPinStruct ioPin);

// Returns a pointer to the data direction register for a given pin
volatile uint8_t* ioPinsGetDDR(ioPinStruct ioPin);

// Returns a pointer to the pin register for a given pin
volatile uint8_t* ioPinsGetPIN(ioPinStruct ioPin);

// Writes a state to a given io pin
void ioPinsWrite(ioPinStruct ioPin, uint8_t state);

// Calls initPin() on all pins defined in function
// This sets the data direction and writes outputs to 0 for each pin
void ioPinsSetup(void);

#endif // IOPINSSETTINGS_H
