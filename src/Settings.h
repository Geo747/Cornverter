//Copyright 2018 George Rennie
//Settings included below

#ifndef SETTINGS_H
#define SETTINGS_H
  #include <inttypes.h>
  typedef uint8_t byte;

  //This code makes vscode play ball with libc but doesnt affect production
  //Set the define to the correct processor as in avr/io.h
  #if !defined (__AVR__)
    #define __AVR_ATmega328P__
  #endif

  //CPU Freq
  #define F_CPU 16000000
  //MIDI Baudrate
  #define BAUD 38400

  //Treat note on messages with 0 velocity as note off messages (advised)
  #define NULL_VELOCITY_AS_NOTE_OFF 1

  //Serial rx buffer size in bytes (works best as powers of 2) cant be more than 8 bit
  #define RX_BUFFER_SIZE 32

  //Number of channels (starting from channel 0) that polytomono and main use
  #define MIDI_CHANNELS 2

  #include <avr/io.h>

  //Define all ports and pins for outputs/inputs
  #define PORT_GATE_1       PORTD
  #define  BIT_GATE_1       7
  #define PORT_GATE_2       PORTB
  #define  BIT_GATE_2       0

  #define PORT_DIGI_1_CH_1  PORTC
  #define  BIT_DIGI_1_CH_1  5
  #define PORT_DIGI_2_CH_1  PORTC
  #define  BIT_DIGI_2_CH_1  4
  #define PORT_DIGI_3_CH_1  PORTC
  #define  BIT_DIGI_3_CH_1  3
  
  #define PORT_DIGI_1_CH_2  PORTC
  #define  BIT_DIGI_1_CH_2  2
  #define PORT_DIGI_2_CH_2  PORTC
  #define  BIT_DIGI_2_CH_2  1
  #define PORT_DIGI_3_CH_2  PORTC
  #define  BIT_DIGI_3_CH_2  0

  //TODO:Add PWM outs and SPI outs here later and update data dir regs below

  #define DATA_DIR_REG_B 0x01
  #define DATA_DIR_REG_C 0x3F
  #define DATA_DIR_REG_D 0x80
#endif