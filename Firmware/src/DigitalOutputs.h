//Copyright 2019 George Rennie
#ifndef DIGITALOUTPUTS_H
#define DIGITALOUTPUTS_H

#include "Settings.h"

//Write a state to the gate pin corresponding to that channel
void digitalOutputsUpdateGate(uint8_t state, uint8_t channel);

/*Write a state to a digital output pin.
  The output is selected by output number and channel
*/
void digitalOutputsUpdateDigi(uint8_t state, uint8_t channel, uint8_t output);

//Write a state to the clock output pin
void digitalOutputsUpdateClock(uint8_t state);

//Write a state to the reset output pin
void digitalOutputsUpdateReset(uint8_t state);
#endif