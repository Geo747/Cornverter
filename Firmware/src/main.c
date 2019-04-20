//Copyright 2018 George Rennie
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
uint8_t RPNNRPNMode[] = {2, 2}; //determines whether RPN or NRPN was set last

uint8_t Ana2Mode[] = {0, 0};

static inline uint8_t channelInRange(uint8_t channel) {
  return (channel < MIDI_CHANNELS);
}

void noteOnHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
  polyToMonoNoteOn(message.data1, message.data2, message.channel);

  VoctWriteNote(message.data1, message.channel);
  if (Ana2Mode[message.channel] == 1) { pwmWrite(message.data2, message.channel, 1); }
  digitalOutputsUpdateGate(polyToMonoIsNoteOn(message.channel), message.channel);
}

void noteOffHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
  polyToMonoNoteOff(message.data1, message.channel);

  uint8_t noteOn = polyToMonoIsNoteOn(message.channel);
  digitalOutputsUpdateGate(noteOn, message.channel);
  if (noteOn) {
    VoctWriteNote(polyToMonoCurrentNote(message.channel), message.channel);
    if (Ana2Mode[message.channel] == 1) { pwmWrite(polyToMonoCurrentVelocity(message.channel), message.channel, 1); }
  }
  else {
    if (Ana2Mode[message.channel] == 1) { pwmWrite(0, message.channel, 1); }
  }
}

void RPNNRPNHandler(uint8_t channel, uint8_t value) {
  if (RPNNRPNMode[channel] == 0) { //If RPN not NRPN
    uint16_t address = (RPNMSB[channel] << 7) | RPNLSB[channel]; //14 bit RPN address
    switch (address) {
      case 0: //Pitchbend range RPN
        VoctSetPitchBendRange(value, channel);
        break;
      
      default:
        break;
    }
  }
}

void controlChangeHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
  switch(message.data1) {
    case 6: //RPN and NRPN Data entry (technically only MSB but currently nothing is implemented that needs LSB)
      RPNNRPNHandler(message.channel, message.data2);
      break;

    case 80: //Digi 1 output
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 0);
      break;

    case 81: //Digi 2 output
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 1);
      break;

    case 82: //Digi 3 output
      digitalOutputsUpdateDigi((message.data2 >= 64), message.channel, 2);
      break;

    case 1: //Analog 1 output
      pwmWrite(message.data2, message.channel, 0);
      break;

    case 16: //Analog 2 output - only active if Ana2Mode[channel] == 0 (i.e in CC mode not velocity mode)
      if (Ana2Mode[message.channel] == 0) { pwmWrite(message.data2, message.channel, 1); }
      break;

    case 17: //V/Oct accuracy setting - 0-4v for data2 < 64 and 0-8v for data2 >= 64
      VoctSetAccuracy((message.data2 >= 64), message.channel);
      break;

    case 18: //Set mode for Analog 2 output - Controlled by CC 16 for data2 < 64 and by velocity for data2 >= 64
      Ana2Mode[message.channel] = (message.data2 >= 64);
      break;

    case 98: //NRPN LSB and MSB(not currently used)
    case 99:
      RPNNRPNMode[message.channel] = 1;
      break;

    case 100: //RPN LSB
      RPNLSB[message.channel] = message.data2;
      RPNNRPNMode[message.channel] = 0;
      break;
    
    case 101: //RPN MSB
      RPNMSB[message.channel] = message.data2;
      RPNNRPNMode[message.channel] = 0;
      break;

    case 19: //Clock Divider
      clockDivision = message.data2;
      break;

    case 120:
    case 123: //Midi all notes off messages
      digitalOutputsUpdateGate(0, message.channel); //Turn off gate
      polyToMonoAllNotesOff(message.channel); //Turn off notes
      break;

    default:
      break;
  }
}

void pitchBendHandler(MIDIMessage message) {
  if (!channelInRange(message.channel)) { return; };
  VoctWritePitchBend(message.data1, message.data2, message.channel);
}

void clockHandler(MIDIMessage message) { //Creates clock with period  of 2 * clockDivision * MIDI tick rate
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

void startContinueHandler(MIDIMessage message) { //Called on start or continue midi messages
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
  VoctSetup();
}

int main(void) {
  setup();
  while (1) {
    MIDIRead();
  }
  return 0;
}