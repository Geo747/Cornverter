//Copyright 2018 George Rennie
#ifndef DIGITALOUTPUTS_H
#define DIGITALOUTPUTS_H

#include "Settings.h"

void digitalOutputsUpdateGate(byte state, byte channel);
void digitalOutputsUpdateDigi(byte state, byte channel, byte output);
void digitalOutputsUpdateClock(byte state);
void digitalOutputsUpdateReset(byte state);
#endif