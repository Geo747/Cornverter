//Copyright 2018 George Rennie
#ifndef POLYTOMONO_H
#define POLYTOMONO_H

#include "Settings.h"

void polyToMonoSetup(void);
void polyToMonoNoteOn(byte note, byte velocity, byte channel);
void polyToMonoNoteOff(byte note, byte channel);

byte polyToMonoCurrentNote(byte channel);
byte polyToMonoCurrentVelocity(byte channel);
byte polyToMonoIsNoteOn(byte channel);
#endif