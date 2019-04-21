//Copyright 2019 George Rennie
#ifndef PWMOUTPUTS_H
#define PWMOUTPUTS_H

#include "Settings.h"

/*Write to the registers to allow timer 0 and 1 PWM to work in the
  correct mode of operation
*/
void pwmSetup(void);

//Write a value from 0 - 127 to a PWM output for a given channel
void pwmWrite(uint8_t value, uint8_t channel, uint8_t output);

#endif