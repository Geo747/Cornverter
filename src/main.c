//Copyright 2018 George Rennie
//This code makes vscode play ball with libc but doesnt affect production
//Set the define to the correct processor as in avr/io.h
#if !defined (__AVR__)
  #define __AVR_ATmega328P__
#endif

#include <avr/io.h>

int main(void)
{
  return 0;
}