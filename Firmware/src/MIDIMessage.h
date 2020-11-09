// Copyright 2019 George Rennie
#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

#include "MIDIDefs.h"
#include <inttypes.h>

typedef struct {
  // The MIDI channel on which the message was recieved
  // Value goes from 0 to 15. 16 represenents an unknown channel
  uint8_t channel;

  // The type of the message (see the MIDIType enum for types reference)
  MIDIType type;

  // The first data byte. Value goes from 0 to 127
  uint8_t data1;

  // The second data byte. If the message is only 2 bytes long, this one is null
  // Value goes from 0 to 127
  uint8_t data2;
} MIDIMessage;

#endif // MIDIMESSAGE_H
