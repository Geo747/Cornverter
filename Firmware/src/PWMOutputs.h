//Copyright 2018 George Rennie
#ifndef PWMOUTPUTS_H
#define PWMOUTPUTS_H

#include "Settings.h"

void pwmSetup(void);
void pwmWrite(uint8_t value, uint8_t channel, uint8_t output); //Set the corresponding one of the 2 outputs for that channel with that byte

#endif