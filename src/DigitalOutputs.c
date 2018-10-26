//Copyright 2018 George Rennie
#include "DigitalOutputs.h"

void digitalOutputsSetup(void) {
  //Set all pins low
  PORT_GATE_1 &= ~(1 << BIT_GATE_1);
  PORT_GATE_2 &= ~(1 << BIT_GATE_2);
  
  PORT_DIGI_1_CH_1 &= ~(1 << BIT_DIGI_1_CH_1);
  PORT_DIGI_2_CH_1 &= ~(1 << BIT_DIGI_2_CH_1);
  PORT_DIGI_3_CH_1 &= ~(1 << BIT_DIGI_3_CH_1);
  PORT_DIGI_1_CH_2 &= ~(1 << BIT_DIGI_1_CH_2);
  PORT_DIGI_2_CH_2 &= ~(1 << BIT_DIGI_2_CH_2);
  PORT_DIGI_3_CH_2 &= ~(1 << BIT_DIGI_3_CH_2);
}

void digitialOutputsUpdateGate(byte state, byte channel) { //Logic to update the output state of the corresponding pin for that gate
  volatile uint8_t *port;
  byte bit;

  switch (channel) {
    case 0:
      port = &PORT_GATE_1;
      bit = BIT_GATE_1;
      break;
    case 1:
      port = &PORT_GATE_2;
      bit = BIT_GATE_2;
      break;
    default:
      return;
  }
  
  switch (state) {
    case 0:
      *port &= ~(1 << bit);
      break;
    case 1:
      *port |= (1 << bit);
      break;
    default:
      return;
  }
}

void digitialOutputsUpdateDigi(byte state, byte channel, byte output) { //Logic to update the output state of the corresponding pin for that digi out
  volatile uint8_t *port;
  byte bit;

  switch (channel) {
    case 0:
      switch (output) {
        case 0:
          port = &PORT_DIGI_1_CH_1;
          bit  =   BIT_DIGI_1_CH_1;
          break;

        case 1:
          port = &PORT_DIGI_2_CH_1;
          bit  =   BIT_DIGI_2_CH_1;
          break;

        case 2:
          port = &PORT_DIGI_2_CH_1;
          bit  =   BIT_DIGI_2_CH_1;
          break;

        default:
          break;
      }
      break;

    case 1:
      switch (output) {
        case 0:
          port = &PORT_DIGI_1_CH_2;
          bit  =   BIT_DIGI_1_CH_2;
          break;

        case 1:
          port = &PORT_DIGI_2_CH_2;
          bit  =   BIT_DIGI_2_CH_2;
          break;

        case 2:
          port = &PORT_DIGI_2_CH_2;
          bit  =   BIT_DIGI_2_CH_2;
          break;

        default:
          break;
      }
      break;

    default:
      return;
  }

  switch (state) {
    case 0:
      *port &= ~(1 << bit);
      break;
    case 1:
      *port |= (1 << bit);
      break;
    default:
      return;
  }
}