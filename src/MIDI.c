//Copyright 2018 George Rennie
#include "Settings.h"
#include "MIDI.h"
#include "MIDI_defs.h"
#include "MIDI_message.h"
#include <avr/io.h>

static char read_byte(void) {
  while (!(UCSR0A & (1 << RXC0))) {} //Wait until receive is ready
  return UDR0; //Return receive buffer
}

void MIDI_setup() {
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

char MIDI_read() { //Constant polling for new midi bytes
  return read_byte();
}