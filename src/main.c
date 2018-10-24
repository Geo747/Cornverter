//Copyright 2018 George Rennie
#include "Settings.h"
#include <avr/io.h>
#include "MIDI.h"

void setup(void){
  DDRB = 0xFF;
}

int main(void)
{
  setup();
  MIDI_setup();
  while (1) {
    char a = MIDI_read();
    if (a == 0x90) {
      PORTB = 0xFF;
    }
    else if (a == 0x80) {
      PORTB = 0x00;
    }
  }
  return 0;
}