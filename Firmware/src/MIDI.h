//Copyright 2019 George Rennie
#ifndef MIDI_H
#define MIDI_H

#include "Settings.h"
#include "MIDIDefs.h"
#include "MIDIMessage.h"
#include "SerialRead.h"

//If not otherwise specified accept data from all 16 MIDI channels
#ifndef MIDI_CHANNELS
#define MIDI_CHANNELS 16
#endif

//If not otherwise specified treat null velocity as a note off
#ifndef NULL_VELOCITY_AS_NOTE_OFF
#define NULL_VELOCITY_AS_NOTE_OFF 1
#endif

//Allows serial port to begin reading in MIDI bytes
void MIDISetup(void);

/*Proccesses a new MIDI byte from the serial buffer.
  This function should be called frequently
*/
void MIDIRead(void);

/*Links reception of a MIDI message with a certain type to
  a callback handler function that should return void
  and have a MIDIMessage argument
*/
void setMIDICallback(void (*fptr)(MIDIMessage message), MIDIType type);
#endif