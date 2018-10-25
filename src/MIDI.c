//Copyright 2018 George Rennie
#include "MIDI.h"

//Data for the library, not declared in .h so just visible in this file
struct dataStruct{
  MIDIMessage mMessage;
  StatusByte mRunningStatus;
  byte mPendingMessage[3];
  uint8_t mPendingMessageExpectedLength;
  uint8_t mPendingMessageIndex;
};

//Instance and initialisation of this struct to provide data to the file
//Not accessible outside this file
struct dataStruct data = {
  .mMessage.channel = 16,
  .mMessage.type = InvalidType,
  .mMessage.data1 = 0,
  .mMessage.data2 = 0,
  .mMessage.valid = 0,

  .mRunningStatus = InvalidType,
  .mPendingMessage = {0, 0, 0},
  .mPendingMessageExpectedLength = 0,
  .mPendingMessageIndex = 0,
};

static byte parse(void) {
  if (!serialAvailable()) { return 0; }

  const byte extracted = serialReadByte();
  return 0;
}

void MIDISetup() {
  serialSetup();
}

void MIDIRead() { //Constant polling for new midi bytes
  if (!parse())
      return;

  // handleNullVelocityNoteOnAsNoteOff();

  // launchCallback();
  return;
}