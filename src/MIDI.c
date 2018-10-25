//Copyright 2018 George Rennie
#include "MIDI.h"

//Data for the library, not declared in .h so just visible in this file
struct dataStruct{
  MIDIMessage mMessage;
  StatusByte mRunningStatus;
  byte mPendingMessage[3];
  uint8_t mPendingMessageExpectedLength;
  uint8_t mPendingMessageIndex;
};

//Instance and initialisation of this struct to provide data to the file
//Not accessible outside this file
struct dataStruct data = {
  .mMessage.channel = 16,
  .mMessage.type = InvalidType,
  .mMessage.data1 = 0,
  .mMessage.data2 = 0,
  .mMessage.valid = 0,

  .mRunningStatus = InvalidType,
  .mPendingMessage = {0, 0, 0},
  .mPendingMessageExpectedLength = 0,
  .mPendingMessageIndex = 0,
};


//TODO: Implement external serial read lib with message buffer to replace readByte and serialAvailable functions using Interrupts
static byte readByte(void) {
  while (!(UCSR0A & (1 << RXC0))) {} //Wait until receive is ready
  return UDR0; //Return receive buffer
}

static byte serialAvailable(void) {
  return (UCSR0A & (1 << RXC0));
}

static byte parser(void) {
  if (!serialAvailable()) { return 0; }

  const byte extracted = readByte();

}

void MIDISetup() {
  #include <util/setbaud.h>

  UBRR0H = UBRRH_VALUE; //Set serial prescalers from util/setbaud
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
  UCSR0A |= (1 << U2X0);
  #else
  UCSR0A &= ~(1 << U2X0);
  #endif

  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //use 8 bit serial
  UCSR0C &= ~((1 << UMSEL00) |(1 << UMSEL01)); //Use Asynch USART
  UCSR0C &= ~((1 << UPM00) |(1 << UPM01)); //Use no parity
  UCSR0C &= ~(1 << USBS0); //Use 1 Stop Bit
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //enable serial rx and tx
}

inline void MIDIRead() { //Constant polling for new midi bytes
  if (!parse())
      return;

  // handleNullVelocityNoteOnAsNoteOff();

  // launchCallback();
  return;
}