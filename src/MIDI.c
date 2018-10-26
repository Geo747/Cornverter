//Copyright 2018 George Rennie
#include "MIDI.h"

//Struct containing function pointers to callback functions
struct callbackStruct{
  void (*mNoteOff)(MIDIMessage message);
  void (*mNoteOn)(MIDIMessage message);
  void (*mControlChange)(MIDIMessage message);
  void (*mPitchBend)(MIDIMessage message);
};

//Initialise callbacks to disconnected
struct callbackStruct callbacks = {
  .mNoteOff = 0,
  .mNoteOn = 0,
  .mControlChange = 0,
  .mPitchBend = 0,
};

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
struct dataStruct d = {
  .mMessage.channel = 16,
  .mMessage.type = InvalidType,
  .mMessage.data1 = 0,
  .mMessage.data2 = 0,

  .mRunningStatus = InvalidType,
  .mPendingMessage = {0, 0, 0},
  .mPendingMessageExpectedLength = 0,
  .mPendingMessageIndex = 0,
};

//Returns true if MIDIType input can have a channel
//Needs modifying if capability for more channel type messages is added to library
static byte isChannelMessage(MIDIType input) {
  return (input == NoteOff ||
          input == NoteOff ||
          input == NoteOff ||
          input == NoteOff);
}

static MIDIType getTypeFromStatusByte(byte input) {
  if ((input  < 0x80) ||
      (input == 0xA0) ||
      (input == 0xC0) ||
      (input == 0xD0) ||
      (input >= 0xF0))
  {
      // input is either a data byte or undefined with current setup (see MIDIType in MIDIDefs.h)
      return InvalidType;
  }

  if (input < 0xF0)
  {
      // Channel message, remove channel nibble.
      return (input & 0xF0);
  }

  //Should automatically be cast to MIDIType cos typedef enum I yhink
  return input;
}

static Channel getChannelFromStatusByte(StatusByte input) {
  return (input & 0x0f);
}

static void handleNullVelocityNoteOnAsNoteOff(void) {
  if (NULL_VELOCITY_AS_NOTE_OFF && d.mMessage.type == NoteOn && d.mMessage.data2 == 0)
  {
    d.mMessage.type = NoteOff;
  }
}

//Byte by byte parsing of incoming data
static byte parse(void) {
  if (!serialAvailable()) { return 0; }

  const byte extracted = serialReadByte();

  //If there is no message already in progress
  if (d.mPendingMessageIndex == 0) {
    d.mPendingMessage[0] = extracted;

    //Check for running status messages
    //only channel messages can do running status
    if (isChannelMessage(getTypeFromStatusByte(d.mRunningStatus))) {
      //If the byte is < 0x80 then it cant be status byte it must be data so assume running status, therefore making the status byte of the message the same as the previous message and the first data byte the byte just read
      if (extracted < 0x80)
        {
          d.mPendingMessage[0]   = d.mRunningStatus;
          d.mPendingMessage[1]   = extracted;
          d.mPendingMessageIndex = 1;
        }
    }

    switch (getTypeFromStatusByte(d.mPendingMessage[0]))
    {
      //If defining more types of MIDI messages, how they are handled can be modified here

      // 3 bytes messages
      case NoteOn:
      case NoteOff:
      case ControlChange:
      case PitchBend:
        d.mPendingMessageExpectedLength = 3;
        break;

      case InvalidType:
      default:
        // All unsupported message types just get ignored and runningstatus byte set to invalid and index and length reset
        d.mPendingMessageIndex = 0;
        d.mPendingMessageExpectedLength = 0;
        d.mRunningStatus = InvalidType;
        return 0;
        break;
    }

    //Put code for dealing with 1 byte messages here if using 1 byte messages

    //Increment index in preparation for more data for this message
    d.mPendingMessageIndex++;

    //Message is not yet complete so MIDIread() shouldnt go any further yet
    return 0;
  }

  else
  {
    // First, test if this is a status byte
    if (extracted >= 0x80)
    {
      // Reception of status bytes in the middle of an uncompleted message
      // are allowed only for interleaved Real Time message or EOX
      // Write code to handle rt messages here if you want them

      // Exit out as we dont care about this byte in this implementation
      return 0;
    }

    // Add extracted data byte to pending message
    // Need some code here for handling sysex if using it
    d.mPendingMessage[d.mPendingMessageIndex] = extracted;

    // Now we are going to check if we have reached the end of the message
    if (d.mPendingMessageIndex >= (d.mPendingMessageExpectedLength - 1))
    {
      d.mMessage.type = getTypeFromStatusByte(d.mPendingMessage[0]);

      //If using non channel specific commands add stuff here
      d.mMessage.channel = getChannelFromStatusByte(d.mPendingMessage[0]);

      d.mMessage.data1 = d.mPendingMessage[1];

      // If also using 2 bit messages change some stuff here
      d.mMessage.data2 = d.mPendingMessage[2];

      // Reset local variables
      d.mPendingMessageIndex = 0;
      d.mPendingMessageExpectedLength = 0;

      // Activate running status (if enabled for the received type)
      switch (d.mMessage.type)
      {
        case NoteOff:
        case NoteOn:
        case ControlChange:
        case PitchBend:
          // Running status enabled: store it from received message
          d.mRunningStatus = d.mPendingMessage[0];
          break;

        default:
          // No running status
          d.mRunningStatus = InvalidType;
          break;
      }
      return 1;
    }
    //Otherwise we are not at the final byte yet
    else
    {
      // Then update the index of the pending message.
      d.mPendingMessageIndex++;

      // Message is not complete
      return 0;
    }
  }

  return 0;
}

//Launches callbacks from MIDIread() according to message type and if a callback is implemented
static void launchCallback(void) {
  switch (d.mMessage.type) {
    case NoteOff: if(callbacks.mNoteOff != 0) { callbacks.mNoteOff(d.mMessage); } break;
    case NoteOn: if(callbacks.mNoteOn != 0) { callbacks.mNoteOn(d.mMessage); } break;
    case ControlChange: if(callbacks.mControlChange != 0) { callbacks.mControlChange(d.mMessage); } break;
    case PitchBend: if(callbacks.mPitchBend != 0) { callbacks.mPitchBend(d.mMessage); } break;
    default: break;
  }
}

void MIDISetup() {
  serialSetup();
}

void MIDIRead() { //Constant polling for new midi bytes
  if (!parse()){
    return;
  }

  handleNullVelocityNoteOnAsNoteOff();

  launchCallback();

  return;
}

//Allows user to set callback by giving target function and midi message type
void setMIDICallback(void (*fptr)(MIDIMessage message), MIDIType type) {
  switch (type) {
    case NoteOff: callbacks.mNoteOff = fptr; break;
    case NoteOn: callbacks.mNoteOn = fptr; break;
    case ControlChange: callbacks.mControlChange = fptr; break;
    case PitchBend: callbacks.mPitchBend = fptr; break;
    default: break;
  }
}