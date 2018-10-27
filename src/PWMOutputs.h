//Copyright 2018 George Rennie
#ifndef PWMOUTPUTS_H
#define PWMOUTPUTS_H

#include "Settings.h"

void pwmSetup(void);
void pwmWrite(byte value, byte channel, byte output); //Set the corresponding one of the 2 outputs for that channel with that byte

#endif