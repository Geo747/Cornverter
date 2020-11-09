// Copyright 2019 George Rennie
#include "MCP4822.h"

// TODO: Change this to use a ring buffer and interrupts

// Send a single byte out over spi
static void sendByte(uint8_t byteToSend) {
  SPDR = byteToSend;
  while (!(SPSR & (1 << SPIF)));
}

void MCP4822Setup(void) {
  ioPinsWrite(ioPins.MCP4822CS, 1);

  // Use MSB First and hold sck low when idle and sample on leading edge
  SPCR &= ~((1 << DORD) | (1 << CPOL) | (1 << CPHA));
  SPCR |= (1 << MSTR);                  // Act as master
  SPCR |= ((1 << SPR1)  | (1 << SPR0)); // Use FOsc/2 prescaler
  SPSR &= ~(1 << SPI2X);
  SPCR |= (1 << SPE);                   // Enable SPI
}

void MCP4822Write(uint16_t value, uint8_t channel, uint8_t accuracy){
  accuracy = (accuracy != 0); // Accuracy can only be 1 or 0
  if (value > 4095) { value = 4095; }

  ioPinsWrite(ioPins.MCP4822CS, 0);
  sendByte(
    ((value >> 8) & 0x0F)
    | ((channel << 7) & 0x80)
    | ((~accuracy & 0x01) << 5)
    | 0x10
  );

  sendByte(value & 0xFF);
  ioPinsWrite(ioPins.MCP4822CS, 1);
}
