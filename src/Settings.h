//Copyright 2018 George Rennie
//Settings included below

#ifndef SETTINGS_H
#define SETTINGS_H

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

#endif