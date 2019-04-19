//Copyright 2018 George Rennie
#include "MCP4822.h"

static void sendByte(uint8_t byteToSend) { //TODO: Change this to use a ring buffer and interrupts
  SPDR = byteToSend;
  while (!(SPSR & (1 << SPIF)));
}

void MCP4822Setup(void) {
  *ioPinsGetPORT(ioPins.MCP4822CS) |= (1 << (ioPins.MCP4822CS.bit));
  
  SPCR &= ~((1 << DORD) | (1 << CPOL) | (1 << CPHA)); //Use MSB First and hold sck low when idle and sample on leading edge
  SPCR |= (1 << MSTR); //Act as master
  SPCR |= ((1 << SPR1) | (1 << SPR0)); //Use Fosc/2 prescaler
  SPSR &= ~(1 << SPI2X);
  SPCR |= (1 << SPE); //Enable SPI
}

void MCP4822Write(uint16_t value, uint8_t channel, uint8_t accuracy){
  if (accuracy > 1) { accuracy = 1; }
  if (value > 4095) { value = 4095; }

  *ioPinsGetPORT(ioPins.MCP4822CS) &= ~(1 << (ioPins.MCP4822CS.bit));
  sendByte(
    ((value >> 8) & 0x0F)
    | ((channel << 7) & 0x80)
    | ((~accuracy & 0x01) << 5)
    | 0x10
  );

  sendByte(value & 0xFF);
  *ioPinsGetPORT(ioPins.MCP4822CS) |= (1 << (ioPins.MCP4822CS.bit));
}