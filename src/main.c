//Copyright 2018 George Rennie
#include "Settings.h"
#include "MIDI.h"
#include "PolyToMono.h"
#include "DigitalOutputs.h"

void noteOffHandler(MIDIMessage message) {
  polyToMonoNoteOff(message.data1, message.channel);

  digitialOutputsUpdateGate(polyToMonoIsNoteOn(message.channel), message.channel);
}

void noteOnHandler(MIDIMessage message) {
  polyToMonoNoteOn(message.data1, message.data2, message.channel);

  digitialOutputsUpdateGate(1, message.channel);
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
  ioPinsSetup();
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