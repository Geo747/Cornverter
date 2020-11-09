// Copyright 2019 George Rennie
#ifndef MIDIDEFS_H
#define MIDIDEFS_H

typedef enum {
  // Only uncommented message types are implemented at the moment, and only in
  // receive. Adding other methods requires some editing of the code in MIDI.c
  InvalidType             = 0x00, // For notifying errors
  NoteOff                 = 0x80, // Note Off
  NoteOn                  = 0x90, // Note On
  // AfterTouchPoly       = 0xA0, // Polyphonic AfterTouch
  ControlChange           = 0xB0, // Control Change / Channel Mode
  // ProgramChange        = 0xC0, // Program Change
  // AfterTouchChannel    = 0xD0, // Channel (monophonic) AfterTouch
  PitchBend               = 0xE0, // Pitch Bend
  // SystemExclusive      = 0xF0, // Sys Exclusive
  // TimeCodeQuarterFrame = 0xF1, // Sys Common - MIDI Time Code Quarter Frame
  // SongPosition         = 0xF2, // Sys Common - Song Position Pointer
  // SongSelect           = 0xF3, // Sys Common - Song Select
  // TuneRequest          = 0xF6, // Sys Common - Tune Request
  Clock                   = 0xF8, // Sys Real Time - Timing Clock
  Start                   = 0xFA, // Sys Real Time - Start
  Continue                = 0xFB, // Sys Real Time - Continue
  Stop                    = 0xFC, // Sys Real Time - Stop
  // ActiveSensing        = 0xFE, // Sys Real Time - Active Sensing
  // SystemReset          = 0xFF, // Sys Real Time - System Reset
} MIDIType;

#endif // MIDIDEFS_H
