//Copyright 2018 George Rennie
#include "Settings.h"
#include "MIDI.h"
#include "PolyToMono.h"
#include "DigitalOutputs.h"
#include "PWMOutputs.h"

byte clockCounter = 0;
byte resetState = 0;

static inline byte channelInRange(byte channel) {
  if (channel < MIDI_CHANNELS) { return 1; }
  return 0;
}

void noteOnHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
  polyToMonoNoteOn(message.data1, message.data2, message.channel);

  digitalOutputsUpdateGate(1, message.channel);
}

void noteOffHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
  polyToMonoNoteOff(message.data1, message.channel);

  digitalOutputsUpdateGate(polyToMonoIsNoteOn(message.channel), message.channel);
}

void controlChangeHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
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

    case 120:
    case 123:
      //Midi all notes off messages
      digitalOutputsUpdateGate(0, message.channel); //Turn off gate
      polyToMonoAllNotesOff(message.channel); //Turn off notes
      //Leave other controllers as they are
      break;

    default:
      return;
  }
}

void pitchBendHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
  
}

void clockHandler(MIDIMessage message) {
  if (clockCounter == 0) { digitalOutputsUpdateClock(1); }
  else if (clockCounter == 2) {
    if (resetState) { 
      digitalOutputsUpdateReset(0);
      resetState = 0;
    }
    digitalOutputsUpdateClock(0); 
  }
  clockCounter = (clockCounter + 1) % 4; //Outputs a clock pulse every 12th of a quarter note
}

void startContinueHandler(MIDIMessage message) {
  digitalOutputsUpdateReset(1);
  resetState = 1;
  clockCounter = 0;
}

void stopHandler(MIDIMessage message) {
  digitalOutputsUpdateClock(0);
  digitalOutputsUpdateReset(0);
  resetState = 0;
}

void setMIDICallbacks(void) {
  setMIDICallback(noteOffHandler,       NoteOff);
  setMIDICallback(noteOnHandler,        NoteOn);
  setMIDICallback(controlChangeHandler, ControlChange);
  setMIDICallback(pitchBendHandler,     PitchBend);
  setMIDICallback(clockHandler,         Clock);
  setMIDICallback(startContinueHandler, Start);
  setMIDICallback(startContinueHandler, Continue);
  setMIDICallback(stopHandler,          Stop);
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