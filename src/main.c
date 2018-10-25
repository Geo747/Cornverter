//Copyright 2018 George Rennie
#include "Settings.h"
#include <avr/io.h>
#include "MIDI.h"

void setup(void){
  MIDISetup();
}

int main(void)
{
  setup();
  while (1) {
  }
  return 0;
}