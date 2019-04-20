//Copyright 2019 George Rennie
#ifndef VOCT_H
#define VOCT_H

#include "Settings.h"
#include "MCP4822.h"

void VoctSetup(void);

//Accept notes from 12 (C-1) up to 108 (C7) for accuracy = 1
//and from 36 (C1) up to 84 (C5) for accuracy = 0
void VoctWriteNote(uint8_t note, uint8_t channel);
void VoctWritePitchBend(uint8_t lsb, uint8_t msb, uint8_t channel);
void VoctSetAccuracy(uint8_t accuracy, uint8_t channel);
void VoctSetPitchBendRange(uint8_t range, uint8_t channel);

#endif