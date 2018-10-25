//Copyright 2018 George Rennie
#include "Settings.h"
#include <avr/io.h>
#include "MIDI.h"

void noteOffHandler(MIDIMessage message) {
  PORTB = 0x00;
}

void noteOnHandler(MIDIMessage message) {
  PORTB = 0xFF;
}

void controlChangeHandler(MIDIMessage message) {
  
}

void pitchBendHandler(MIDIMessage message) {
  
}

void setupMIDIHandlers(void) {
  setMIDICallback(noteOffHandler, NoteOff);
  setMIDICallback(noteOnHandler, NoteOn);
  setMIDICallback(controlChangeHandler, ControlChange);
  setMIDICallback(pitchBendHandler, PitchBend);
}

void setup(void) {
  MIDISetup();
  setupMIDIHandlers();
  DDRB = 0xFF;
}

int main(void) {
  setup();
  while (1) {
    MIDIRead();
  }
  return 0;
}