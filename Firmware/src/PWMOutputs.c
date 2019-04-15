//Copyright 2018 George Rennie
#include "PWMOutputs.h"

void pwmWrite(byte value, byte channel, byte output) { //Input value is 7 bit
  volatile uint8_t* OCR;
  ioPinStruct ioPin;
  volatile uint8_t* timerReg;
  uint8_t timerRegBit;

  switch (channel) {
    case 0:
      switch(output) {
        case 0:
          OCR = &OCR0A;
          ioPin = ioPins.ana1ch1;
          timerReg = &TCCR0A;
          timerRegBit = COM0A1;
          break;
        case 1:
          OCR = &OCR1AL;
          ioPin = ioPins.ana2ch1;
          timerReg = &TCCR1A;
          timerRegBit = COM1A1;
          break;
        default:
          return;
      }
      break;

    case 1:
      switch(output) {
        case 0:
          OCR = &OCR0B;
          ioPin = ioPins.ana1ch2;
          timerReg = &TCCR0A;
          timerRegBit = COM0B1;
          break;
        case 1:
          OCR = &OCR1BL;
          ioPin = ioPins.ana2ch2;
          timerReg = &TCCR1A;
          timerRegBit = COM1B1;
          break;
        default:
          return;
      }
      break;

    default:
      return;
  }

  value = value << 1;
  *OCR = value;

  if (value == 0) {
    *ioPinsGetPORT(ioPin) &= ~(1 << ioPin.bit);
    *timerReg &= ~(1 << timerRegBit);
  }
  else {
    *ioPinsGetPORT(ioPin) |= (1 << ioPin.bit);
    *timerReg |= (1 << timerRegBit);
  }
}

void pwmSetup(void) {
  //Pins PD5, PD6 use timer 0B and 0A respectively (Ana1Ch2 and Ana1Ch1)
  //Pins PB1, PB2 use timer 1A and 1B respectively (Ana2Ch1 and Ana2Ch2)

  TCCR0A &= ~(1 << COM0A0) & ~(1 << COM0B0);
  TCCR1A &= ~(1 << COM1A0) & ~(1 << COM1B0); //set compare output mode to non inverting

  TCCR0A |= (1 << WGM00) | (1 << WGM01); //Set timer 0 to Fast PWM
  TCCR0B &= ~(1 << WGM02); 

  TCCR1A |= (1 << WGM10); //Set Timer 1 to 8 bit Fast PWM
  TCCR1A &= ~(1 << WGM11);
  TCCR1B |= (1 << WGM12);
  TCCR1B &= ~(1 << WGM13);

  TCCR0B |= (1 << CS00); //Set Timer 0 prescaler to clkio/1 i.e. 16Mhz
  TCCR0B &= ~(1 << CS01) & ~(1 << CS02);

  TCCR1B |= (1 << CS10); //Set Timer 1 prescaler to clkio/1 i.e. 16Mhz
  TCCR1B &= ~(1 << CS11) & ~(1 << CS12);

  OCR1AH = 0x00; //Timer 1 is 16 bit so has two ocr registers but as this program uses 8 bit pwm only so only the low byte should need to be written to
  OCR1BH = 0x00;

  pwmWrite(0, 0, 0);
  pwmWrite(0, 0, 1);
  pwmWrite(0, 1, 0);
  pwmWrite(0, 1, 1);
}