//Copyright 2018 George Rennie
#include "Settings.h"
#include <avr/io.h>
#include "MIDI.h"
#include "PolyToMono.h"

byte channelIsUsed(byte channel) {
  if (channel < MIDI_CHANNELS) { return 1; }
  return 0;
}

void noteOffHandler(MIDIMessage message) {
  if (!channelIsUsed(message.channel)) { return; }
  polyToMonoNoteOff(message.data1, message.channel);
}

void noteOnHandler(MIDIMessage message) {
  if (!channelIsUsed(message.channel)) { return; }
  polyToMonoNoteOn(message.data1, message.data2, message.channel);
}

void controlChangeHandler(MIDIMessage message) {
  if (!channelIsUsed(message.channel)) { return; }
  
}

void pitchBendHandler(MIDIMessage message) {
  if (!channelIsUsed(message.channel)) { return; }
  
}

void setupMIDIHandlers(void) {
  setMIDICallback(noteOffHandler, NoteOff);
  setMIDICallback(noteOnHandler, NoteOn);
  setMIDICallback(controlChangeHandler, ControlChange);
  setMIDICallback(pitchBendHandler, PitchBend);
}

void setup(void) {
  MIDISetup();
  polyToMonoSetup();
  setupMIDIHandlers();
}

int main(void) {
  setup();
  while (1) {
    MIDIRead();
  }
  return 0;
}