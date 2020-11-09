// Copyright 2019 George Rennie
#ifndef POLYTOMONO_H
#define POLYTOMONO_H

#include "Settings.h"

// Defining MIDI_CHANNELS allows you to choose
// the number of midi channels used

#ifndef MIDI_CHANNELS
#define MIDI_CHANNELS 16
#endif

// Initialise data arrays used by polyToMono
void polyToMonoSetup(void);

// Set the DAC accuracy mode currently being used. This affects the range of
// notes available
void polyToMonoSetAccuracy(uint8_t accuracy, uint8_t channel);

// Adds a new note on message to the mono note list
void polyToMonoNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);

// Removes a note from the mono note list
void polyToMonoNoteOff(uint8_t note, uint8_t channel);

// Turns all notes currently in the list off
void polyToMonoAllNotesOff(uint8_t channel);


// Returns the current note at the top of the list
uint8_t polyToMonoCurrentNote(uint8_t channel);

// Returns the current velocity of the note at the top of the list
uint8_t polyToMonoCurrentVelocity(uint8_t channel);

// Returns 1 if there are any notes currently in the list
uint8_t polyToMonoIsNoteOn(uint8_t channel);

#endif // POLYTOMONO_H
