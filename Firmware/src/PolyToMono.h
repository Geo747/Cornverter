//Copyright 2019 George Rennie
#ifndef POLYTOMONO_H
#define POLYTOMONO_H

#include "Settings.h"

void polyToMonoSetup(void);
void polyToMonoSetAccuracy(uint8_t accuracy, uint8_t channel);
void polyToMonoNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
void polyToMonoNoteOff(uint8_t note, uint8_t channel);
void polyToMonoAllNotesOff(uint8_t channel);

uint8_t polyToMonoCurrentNote(uint8_t channel);
uint8_t polyToMonoCurrentVelocity(uint8_t channel);
uint8_t polyToMonoIsNoteOn(uint8_t channel);
#endif