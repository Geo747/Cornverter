//Copyright 2018 George Rennie
#include "Settings.h"
#include "ioPinsSettings.h"

//Remember to define every pin in this
const ioPinsStruct ioPins = {
  .gate1.portLetter     = 'D',
  .gate1.bit            =  7 ,
  .gate1.direction      =  1 ,

  .gate2.portLetter     = 'B',
  .gate2.bit            =  0 ,
  .gate2.direction      =  1 ,

  .digi1ch1.portLetter  = 'C',
  .digi1ch1.bit         =  5 ,
  .digi1ch1.direction   =  1 ,

  .digi2ch1.portLetter  = 'C',
  .digi2ch1.bit         =  4 ,
  .digi2ch1.direction   =  1 ,

  .digi3ch1.portLetter  = 'C',
  .digi3ch1.bit         =  3 ,
  .digi3ch1.direction   =  1 ,

  .digi1ch2.portLetter  = 'C',
  .digi1ch2.bit         =  2 ,
  .digi1ch2.direction   =  1 ,

  .digi2ch2.portLetter  = 'C',
  .digi2ch2.bit         =  1 ,
  .digi2ch2.direction   =  1 ,

  .digi3ch2.portLetter  = 'C',
  .digi3ch2.bit         =  0 ,
  .digi3ch2.direction   =  1 ,

  .ana1ch1.portLetter   = 'D',
  .ana1ch1.bit          =  6 ,
  .ana1ch1.direction    =  1 ,

  .ana2ch1.portLetter   = 'B',
  .ana2ch1.bit          =  1 ,
  .ana2ch1.direction    =  1 ,

  .ana1ch2.portLetter   = 'D',
  .ana1ch2.bit          =  5 ,
  .ana1ch2.direction    =  1 ,

  .ana2ch2.portLetter   = 'B',
  .ana2ch2.bit          =  2 ,
  .ana2ch2.direction    =  1 ,

  .clockOut.portLetter  = 'D',
  .clockOut.bit         =  2 ,
  .clockOut.direction   =  1 ,

  .resetOut.portLetter  = 'D',
  .resetOut.bit         =  3 ,
  .resetOut.direction   =  1 ,

  .MCP4822CS.portLetter = 'D',
  .MCP4822CS.bit        =  4 ,
  .MCP4822CS.direction  =  1 ,

  .MCP4822MOSI.portLetter='B',
  .MCP4822MOSI.bit      =  3 ,
  .MCP4822MOSI.direction=  1 ,

  .MCP4822SCK.portLetter= 'B',
  .MCP4822SCK.bit       =  5 ,
  .MCP4822SCK.direction =  1 ,
  
};

volatile uint8_t* ioPinsGetPORT(ioPinStruct ioPin) {
  char letter = ioPin.portLetter;
  if      (letter == 'B') { return &PORTB; }
  else if (letter == 'C') { return &PORTC; }
  else                    { return &PORTD; }
}

volatile uint8_t* ioPinsGetDDR(ioPinStruct ioPin) {
  char letter = ioPin.portLetter;
  if      (letter == 'B') { return &DDRB; }
  else if (letter == 'C') { return &DDRC; }
  else                    { return &DDRD; }
}

volatile uint8_t* ioPinsGetPIN(ioPinStruct ioPin) {
  char letter = ioPin.portLetter;
  if      (letter == 'B') { return &PINB; }
  else if (letter == 'C') { return &PINC; }
  else                    { return &PIND; }
}

void ioPinsWrite(ioPinStruct ioPin, uint8_t state) {
  if (state == 0) { *ioPinsGetPORT(ioPin) &= ~(1 << ioPin.bit); }
  else            { *ioPinsGetPORT(ioPin) |= (1 << ioPin.bit); }
}

static void initPin(ioPinStruct ioPin) {
  volatile uint8_t* DDR = ioPinsGetDDR(ioPin);
  switch (ioPin.direction) {
    case 0:
      *DDR &= ~(1 << ioPin.bit);
      break;
    case 1:
      *DDR |= (1 << ioPin.bit);
      ioPinsWrite(ioPin, 0);
      break;
    default:
      return;
  }
}

//Include every pin in this
void ioPinsSetup(void) {
  initPin(ioPins.gate1);
  initPin(ioPins.gate2);
  initPin(ioPins.digi1ch1);
  initPin(ioPins.digi2ch1);
  initPin(ioPins.digi3ch1);
  initPin(ioPins.digi1ch2);
  initPin(ioPins.digi2ch2);
  initPin(ioPins.digi3ch2);
  initPin(ioPins.ana1ch1);
  initPin(ioPins.ana2ch1);
  initPin(ioPins.ana1ch2);
  initPin(ioPins.ana2ch2);
  initPin(ioPins.clockOut);
  initPin(ioPins.resetOut);
  initPin(ioPins.MCP4822CS);
  initPin(ioPins.MCP4822MOSI);
  initPin(ioPins.MCP4822SCK);
}