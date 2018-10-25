//Copyright 2018 George Rennie
#ifndef MIDI_H
#define MIDI_H

#include "Settings.h"
#include "MIDI_Defs.h"
#include "MIDI_Message.h"
#include <avr/io.h>

inline void MIDISetup(void);
inline void MIDIRead(void);
#endif