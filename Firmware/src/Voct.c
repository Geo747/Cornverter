//Copyright 2018 George Rennie
#include "Voct.h"

static uint16_t mCurrentKeyValue[] = {0, 0};
static uint16_t mCurrentPitchBendShift[] = {0, 0};
static uint8_t mPitchBendRange[] = {2, 2};
static uint8_t mAccuracy[] = {1, 1};

static const uint8_t noteRange[] = {48, 96};
static const uint8_t lowestNote[] = {36, 12};
static const uint8_t highestNote[] = {84, 108};

void VoctSetup(void) {
  MCP4822Setup();
  MCP4822Write(0, 0, mAccuracy[0]);
  MCP4822Write(0, 1, mAccuracy[1]);
}

void VoctWriteNote(uint8_t note, uint8_t channel) {
  if (channel > 1) { return; }

  if ((note < lowestNote[mAccuracy[channel]])
  || (note > highestNote[mAccuracy[channel]])) { return; }

  uint32_t outputValue = ((uint32_t)4095 * (uint32_t)(note - lowestNote[mAccuracy[channel]]));

  uint16_t modValue = outputValue % noteRange[mAccuracy[channel]];

  outputValue /= (uint32_t)noteRange[mAccuracy[channel]];

  if (modValue >= noteRange[mAccuracy[channel]] / 2) { outputValue += 1; };

  MCP4822Write(outputValue, channel, mAccuracy[channel]);
}

void VoctWritePitchBend(uint16_t value, uint8_t channel) {
  
}

void VoctSetAccuracy(uint8_t accuracy, uint8_t channel) {
  if (channel <= 1) {
    mAccuracy[channel] = accuracy;
  }
}

void VoctSetPitchBendRange(uint8_t range, uint8_t channel){

}