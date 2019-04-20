//Copyright 2019 George Rennie
//Settings included below

#ifndef SETTINGS_H
#define SETTINGS_H
  #include <inttypes.h>

  //This code makes vscode play ball with libc but doesnt affect production
  //Set the define to the correct processor as in avr/io.h
  #if !defined (__AVR__)
    #define __AVR_ATmega328P__
  #endif
  
  #include <avr/io.h>
  #include "ioPinsSettings.h" //This defines all the iopins and iopin structs, use it to define io pins

  //CPU Freq
  #define F_CPU 16000000
  //MIDI Baudrate
  #define BAUD 31250

  //Treat note on messages with 0 velocity as note off messages (advised)
  #define NULL_VELOCITY_AS_NOTE_OFF 1

  //Serial rx buffer size in bytes (works best as powers of 2) cant be more than 8 bit
  #define RX_BUFFER_SIZE 32

  //Number of channels (starting from channel 0) that polytomono and main use
  #define MIDI_CHANNELS 2

  static const uint8_t NOTE_RANGE[] = {48, 96}; //Define notes for different accuracies
  static const uint8_t LOWEST_NOTE[] = {24, 24};
  static const uint8_t HIGHEST_NOTE[] = {72, 120};
#endif