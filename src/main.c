//Copyright 2018 George Rennie
#include "Settings.h"
#include "MIDI.h"
#include "PolyToMono.h"
#include "DigitalOutputs.h"

byte channelIsUsed(byte channel) {
  if (channel < MIDI_CHANNELS) { return 1; }
  return 0;
}

void noteOffHandler(MIDIMessage message) {
  if (!channelIsUsed(message.channel)) { return; }
  polyToMonoNoteOff(message.data1, message.channel);

  digitialOutputsUpdateGate(polyToMonoIsNoteOn(message.channel), message.channel);
}

void noteOnHandler(MIDIMessage message) {
  if (!channelIsUsed(message.channel)) { return; }
  polyToMonoNoteOn(message.data1, message.data2, message.channel);

  digitialOutputsUpdateGate(1, message.channel);
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
  DDRB = DATA_DIR_REG_B;
  DDRC = DATA_DIR_REG_C;
  DDRD = DATA_DIR_REG_D;
  MIDISetup();
  polyToMonoSetup();
  setupMIDIHandlers();
  digitalOutputsSetup();
}

int main(void) {
  setup();
  while (1) {
    MIDIRead();
  }
  return 0;
}