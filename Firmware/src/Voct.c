//Copyright 2018 George Rennie
#include "Voct.h"

static uint16_t mCurrentNote[] = {0, 0};
static uint16_t mCurrentPitchBend[] = {16384, 16384};
static uint8_t mPitchBendRange[] = {2, 2};
static uint8_t mAccuracy[] = {1, 1};

void VoctSetup(void) {
  MCP4822Setup();
  MCP4822Write(0, 0, mAccuracy[0]);
  MCP4822Write(0, 1, mAccuracy[1]);
}

void writeToDac(uint8_t channel) {
  int32_t outputValue = ((int32_t)4095 * (int32_t)(mCurrentNote[channel]));
  outputValue += ((int32_t)4095 * (mCurrentPitchBend[channel] - (int32_t)8192) * mPitchBendRange[channel]) / (int32_t)8192;

  uint16_t modValue = outputValue % NOTE_RANGE[mAccuracy[channel]];

  outputValue /= (int32_t)NOTE_RANGE[mAccuracy[channel]];

  if (modValue >= NOTE_RANGE[mAccuracy[channel]] / 2) { outputValue += 1; };

  if   (outputValue > 4095) { outputValue = 4095; }
  else if (outputValue < 0) { outputValue = 0; }

  MCP4822Write(outputValue, channel, mAccuracy[channel]);
}

void VoctWriteNote(uint8_t note, uint8_t channel) {
  if (channel > 1) { return; }

  if ((note < LOWEST_NOTE[mAccuracy[channel]])
  || (note > HIGHEST_NOTE[mAccuracy[channel]])) { return; }

  mCurrentNote[channel] = note - LOWEST_NOTE[mAccuracy[channel]];

  writeToDac(channel);
}

void VoctWritePitchBend(uint8_t lsb, uint8_t msb, uint8_t channel) {
  if (channel > 1) { return; }
  
  mCurrentPitchBend[channel] = msb << 7 | lsb;

  writeToDac(channel);
}

void VoctSetAccuracy(uint8_t accuracy, uint8_t channel) {
  if (channel <= 1) {
    mAccuracy[channel] = accuracy;
  }
}

void VoctSetPitchBendRange(uint8_t range, uint8_t channel){
  mPitchBendRange[channel] = range;
}