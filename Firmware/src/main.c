// Copyright 2019 George Rennie
#include "Settings.h"
#include "MIDI.h"
#include "PolyToMono.h"
#include "DigitalOutputs.h"
#include "PWMOutputs.h"
#include "Voct.h"

uint8_t clockCounter = 0;
uint8_t resetState = 0;
uint8_t clockDivision = 12;

uint8_t RPNMSB[] = {128, 128};
uint8_t RPNLSB[] = {128, 128};
// Determines whether RPN or NRPN was set last
uint8_t RPNNRPNMode[] = {2, 2};

uint8_t Ana2Mode[] = {0, 0};

void noteOnHandler(MIDIMessage message) {
  polyToMonoNoteOn(message.data1, message.data2, message.channel);

  VoctWriteNote(message.data1, message.channel);
  if (Ana2Mode[message.channel] == 1) {
    pwmWrite(message.data2, message.channel, 1);
  }

  uint8_t isNoteOn = polyToMonoIsNoteOn(message.channel);
  digitalOutputsUpdateGate(isNoteOn, message.channel);
}

void noteOffHandler(MIDIMessage message) {
  polyToMonoNoteOff(message.data1, message.channel);

  uint8_t noteOn = polyToMonoIsNoteOn(message.channel);
  digitalOutputsUpdateGate(noteOn, message.channel);
  if (noteOn) {
    VoctWriteNote(polyToMonoCurrentNote(message.channel), message.channel);
    if (Ana2Mode[message.channel] == 1) {
      uint8_t currentVelocity = polyToMonoCurrentVelocity(message.channel);
      pwmWrite(currentVelocity, message.channel, 1);
    }
  }
  else {
    if (Ana2Mode[message.channel] == 1) { pwmWrite(0, message.channel, 1); }
  }
}

// Called whenever Data Entry MSB CC 6 is changed.
// Handles RPNs or NRPNs depending on which last had addresses sent
void RPNNRPNHandler(uint8_t channel, uint8_t value) {
  // If the mode of the channel is RPN not NRPN
  if (RPNNRPNMode[channel] == 0) {
    // 14 bit RPN address
    uint16_t address = (RPNMSB[channel] << 7) | RPNLSB[channel];

    switch (address) {
      case 0: // Pitchbend range RPN
        VoctSetPitchBendRange(value, channel);
        break;

      default:
        break;
    }
  }
}

void controlChangeHandler(MIDIMessage message) {
  switch(message.data1) {

    // RPN and NRPN Data entry.
    //   This is technically only the MSB
    //   however currently nothing is implemented that needs the LSB
    case 6:
      RPNNRPNHandler(message.channel, message.data2);
      break;

    case 80: // Digi 1 output
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 0);
      break;

    case 81: // Digi 2 output
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 1);
      break;

    case 82: // Digi 3 output
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 2);
      break;

    case 1: // Analog 1 output
      pwmWrite(message.data2, message.channel, 0);
      break;

    // Analog 2 output - Only active if Ana2Mode[channel] == 0
    // (i.e in CC mode not velocity mode)
    case 16:
      if (Ana2Mode[message.channel] == 0) {
        pwmWrite(message.data2, message.channel, 1);
      }
      break;

    // V/Oct accuracy setting - 0-4v for data2 < 64 and 0-8v for data2 >= 64
    case 17:
      polyToMonoSetAccuracy(message.data2 >= 64, message.channel);
      VoctSetAccuracy((message.data2 >= 64), message.channel);
      break;

    // Set mode for Analog 2 output - It is controlled by CC 16 for data2 < 64
    // and by velocity for data2 >= 64
    case 18:
      Ana2Mode[message.channel] = (message.data2 >= 64);
      break;

    case 98: // NRPN LSB and MSB(not currently used)
    case 99:
      RPNNRPNMode[message.channel] = 1;
      break;

    case 100: // RPN LSB
      RPNLSB[message.channel] = message.data2;
      RPNNRPNMode[message.channel] = 0;
      break;

    case 101: // RPN MSB
      RPNMSB[message.channel] = message.data2;
      RPNNRPNMode[message.channel] = 0;
      break;

    case 19: // Clock Divider
      clockDivision = message.data2;
      break;

    // Midi all notes off messages
    case 120:
    case 123:
      digitalOutputsUpdateGate(0, message.channel);
      polyToMonoAllNotesOff(message.channel);
      break;

    default:
      break;
  }
}

void pitchBendHandler(MIDIMessage message) {
  VoctWritePitchBend(message.data1, message.data2, message.channel);
}

// Creates clock with period  of 2 * clockDivision * MIDI tick period
void clockHandler(MIDIMessage message) {
  if (clockCounter == 0) { digitalOutputsUpdateClock(1); }
  else if (clockCounter == clockDivision) {
    if (resetState) {
      digitalOutputsUpdateReset(0);
      resetState = 0;
    }
    digitalOutputsUpdateClock(0);
  }
  clockCounter = (clockCounter + 1) % (2 * clockDivision);
}

// Called on start or continue MIDI messages
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

// Assigns callback handler functions to be
// triggered from different types of MIDI message
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
  VoctSetup();
}

int main(void) {
  setup();
  while (1) {
    MIDIRead();
  }
  return 0;
}
