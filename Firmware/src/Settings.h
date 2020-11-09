// Copyright 2019 George Rennie
// Settings included below

#ifndef SETTINGS_H
#define SETTINGS_H

#include <inttypes.h>
#include <avr/io.h>

// This defines all the iopins and iopin structs, use it to define io pins
#include "ioPinsSettings.h"

// CPU Freq
#define F_CPU 16000000
// MIDI Baudrate
#define BAUD 31250

// Treat note on messages with 0 velocity as note off messages (advised)
#define NULL_VELOCITY_AS_NOTE_OFF 1

// Serial rx buffer size in bytes (works best as powers of 2).
#define RX_BUFFER_SIZE 64

// Number of channels (starting from channel 0) that polytomono and main use
#define MIDI_CHANNELS 2
// MIDI.c moves midi channels down by this offset to allow different
// midi ranges
#ifndef MIDI_CHANNEL_OFFSET
  #define MIDI_CHANNEL_OFFSET 0
#endif

// Define MIDI notes for different accuracies
static const uint8_t __attribute__ ((unused)) NOTE_RANGE[] = {48, 96};
static const uint8_t __attribute__ ((unused)) LOWEST_NOTE[] = {24, 24};
static const uint8_t __attribute__ ((unused)) HIGHEST_NOTE[] = {72, 120};

#endif // SETTINGS_H
