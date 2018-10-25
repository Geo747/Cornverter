//Copyright 2018 George Rennie
#ifndef MIDI_H
#define MIDI_H

#include "Settings.h"
#include "MIDIDefs.h"
#include "MIDIMessage.h"
#include "SerialRead.h"

void MIDISetup(void);
void MIDIRead(void);
#endif