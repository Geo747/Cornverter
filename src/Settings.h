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

#endif