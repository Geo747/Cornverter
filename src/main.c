//Copyright 2018 George Rennie
#include "Settings.h"
#include <avr/io.h>
#include "MIDI.h"

void setup(void){
  MIDISetup();
  DDRB = 0xFF;
}

int main(void)
{
  setup();
  while (1) {
    MIDIRead();
  }
  return 0;
}