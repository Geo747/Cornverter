//Copyright 2019 George Rennie
#include "DigitalOutputs.h"

void digitalOutputsUpdateGate(uint8_t state, uint8_t channel) {
  ioPinStruct ioPin;

  if      (channel == 0) { ioPin = ioPins.gate1; }
  else if (channel == 1) { ioPin = ioPins.gate2; }

  ioPinsWrite(ioPin, state);
}

void digitalOutputsUpdateDigi(uint8_t state, uint8_t channel, uint8_t output) {
  ioPinStruct possibleIoPins[2][3] = {
    {ioPins.digi1ch1, ioPins.digi2ch1, ioPins.digi3ch1},
    {ioPins.digi1ch2, ioPins.digi2ch2, ioPins.digi3ch2}
  };

  ioPinStruct ioPin = possibleIoPins[channel][output];

  ioPinsWrite(ioPin, state);
}

void digitalOutputsUpdateClock(uint8_t state) {
  ioPinsWrite(ioPins.clockOut, state);
}

void digitalOutputsUpdateReset(uint8_t state) {
  ioPinsWrite(ioPins.resetOut, state);
}