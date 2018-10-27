//Copyright 2018 George Rennie
#include "Settings.h"
#include "MIDI.h"
#include "PolyToMono.h"
#include "DigitalOutputs.h"
#include "PWMOutputs.h"

void noteOnHandler(MIDIMessage message) {
  polyToMonoNoteOn(message.data1, message.data2, message.channel);

  digitalOutputsUpdateGate(1, message.channel);
}

void noteOffHandler(MIDIMessage message) {
  polyToMonoNoteOff(message.data1, message.channel);

  digitalOutputsUpdateGate(polyToMonoIsNoteOn(message.channel), message.channel);
}

void controlChangeHandler(MIDIMessage message) {
  switch(message.data1) {
    case 80:
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 0);
      break;

    case 81:
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 1);
      break;

    case 82:
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 2);
      break;

    case 1:
      pwmWrite(message.data2, message.channel, 0);
      break;

    case 16:
      pwmWrite(message.data2, message.channel, 1);
      break;

    default:
      return;
  }
}

void pitchBendHandler(MIDIMessage message) {
  
}

void setMIDICallbacks(void) {
  setMIDICallback(noteOffHandler, NoteOff);
  setMIDICallback(noteOnHandler, NoteOn);
  setMIDICallback(controlChangeHandler, ControlChange);
  setMIDICallback(pitchBendHandler, PitchBend);
}

void setup(void) {
  ioPinsSetup();
  MIDISetup();
  polyToMonoSetup();
  setMIDICallbacks();
  pwmSetup();
}

int main(void) {
  setup();
  while (1) {
    MIDIRead();
  }
  return 0;
}