//Copyright 2018 George Rennie
#ifndef DIGITALOUTPUTS_H
#define DIGITALOUTPUTS_H

#include "Settings.h"

void digitalOutputsUpdateGate(uint8_t state, uint8_t channel);
void digitalOutputsUpdateDigi(uint8_t state, uint8_t channel, uint8_t output);
void digitalOutputsUpdateClock(uint8_t state);
void digitalOutputsUpdateReset(uint8_t state);
#endif