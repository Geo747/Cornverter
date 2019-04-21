//Copyright 2019 George Rennie
#ifndef VOCT_H
#define VOCT_H

#include "Settings.h"
#include "MCP4822.h"

//Setup the SPI for the DAC and initialise values to it
void VoctSetup(void);

/*Write a value to the DAC corresponding to that note if it is in the
  range currently allowed by the accuracy setting
*/
void VoctWriteNote(uint8_t note, uint8_t channel);

/*Write a 14 bit pitchbend change such that lsb = 0x00 and msb = 0x40
  when no pitchbend is applied
*/
void VoctWritePitchBend(uint8_t lsb, uint8_t msb, uint8_t channel);

/*Sets the accuracy of the output. When accuracy is 0 the precision is
  doubled but the available note range is halved compared to when the
  accuracy is set to 1
*/
void VoctSetAccuracy(uint8_t accuracy, uint8_t channel);

/*Set the number of semitones in one direction the output pitch will be
  bent by when the pitchbend control is at its extreme
*/
void VoctSetPitchBendRange(uint8_t range, uint8_t channel);

#endif