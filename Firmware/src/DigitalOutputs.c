//Copyright 2018 George Rennie
#include "DigitalOutputs.h"

void digitalOutputsUpdateGate(uint8_t state, uint8_t channel) { //Logic to update the output state of the corresponding pin for that gate
  ioPinStruct ioPin;
  
  switch (channel) {
    case 0:
      ioPin = ioPins.gate1;
      break;
    case 1:
      ioPin = ioPins.gate2;
      break;
    default:
      return;
  }
  
  switch (state) {
    case 0:
      *ioPinsGetPORT(ioPin) &= ~(1 << ioPin.bit);
      break;
    case 1:
      *ioPinsGetPORT(ioPin) |= (1 << ioPin.bit);
      break;
    default:
      return;
  }
}

void digitalOutputsUpdateDigi(uint8_t state, uint8_t channel, uint8_t output) { //Logic to update the output state of the corresponding pin for that digi out
  ioPinStruct ioPin;

  switch (channel) {
    case 0:
      switch (output) {
        case 0:
          ioPin = ioPins.digi1ch1;
          break;

        case 1:
          ioPin = ioPins.digi2ch1;
          break;

        case 2:
          ioPin = ioPins.digi3ch1;
          break;

        default:
          return;
      }
      break;

    case 1:
      switch (output) {
        case 0:
          ioPin = ioPins.digi1ch2;
          break;

        case 1:
          ioPin = ioPins.digi2ch2;
          break;

        case 2:
          ioPin = ioPins.digi3ch2;
          break;

        default:
          return;
      }
      break;

    default:
      return;
  }

  switch (state) {
    case 0:
      *ioPinsGetPORT(ioPin) &= ~(1 << ioPin.bit);
      break;
    case 1:
      *ioPinsGetPORT(ioPin) |= (1 << ioPin.bit);
      break;
    default:
      return;
  }
}

void digitalOutputsUpdateClock(uint8_t state) {
  ioPinStruct ioPin = ioPins.clockOut;
  switch (state) {
    case 0:
      *ioPinsGetPORT(ioPin) &= ~(1 << ioPin.bit);
      break;
    case 1:
      *ioPinsGetPORT(ioPin) |= (1 << ioPin.bit);
      break;
    default:
      return;
  }
}

void digitalOutputsUpdateReset(uint8_t state) {
  ioPinStruct ioPin = ioPins.resetOut;
  switch (state) {
    case 0:
      *ioPinsGetPORT(ioPin) &= ~(1 << ioPin.bit);
      break;
    case 1:
      *ioPinsGetPORT(ioPin) |= (1 << ioPin.bit);
      break;
    default:
      return;
  }
}