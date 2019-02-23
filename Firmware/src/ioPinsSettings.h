//Copyright 2018 George Rennie

//NOTE: To add a new pin, add it in the ioPinsStruct declaration, ioPins definition and ioPinsSetup

#ifndef IOPINSSETTINGS_H
#define IOPINSSETTINGS_H
#include <inttypes.h>
#include <avr/io.h>
//Struct to store relevant data for each pin type
typedef struct {
  char portLetter;
  uint8_t bit;
  uint8_t direction;
} ioPinStruct;

//Struct to store all pins
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

//Struct with pin data in, defined in .c
extern const ioPinsStruct ioPins;

//Helpful function
volatile uint8_t* ioPinsGetPORT(ioPinStruct ioPin);
volatile uint8_t* ioPinsGetDDR(ioPinStruct ioPin);
volatile uint8_t* ioPinsGetPIN(ioPinStruct ioPin);

void ioPinsSetup(void);

#endif