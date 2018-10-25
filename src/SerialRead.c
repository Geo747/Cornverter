//Copyright 2018 George Rennie
#include "SerialRead.h"

byte mRxBuffer[RX_BUFFER_SIZE];
byte mRxBufferHead = 0;
byte mRxBufferTail = 0;

//Reads from ring buffer
int serialReadByte(void) {
  if (mRxBufferHead == mRxBufferTail) {
    return -1
  } else {
    byte data = mRxBuffer[mRxBufferTail];
    mRxBufferTail = (byte)((mRxBufferTail + 1) % RX_BUFFER_SIZE);
    return data;
  }
}

byte serialAvailable(void) {
  //returns 0 only when the buffer pointers are the same value
  //i.e. whenever there is data in the buffer the pointers are at dif places
  return (byte)(RX_BUFFER_SIZE + mRxBufferHead - mRxBufferTail) % RX_BUFFER_SIZE;
}

void serialSetup(void) {
  #include <util/setbaud.h>

  UBRR0H = UBRRH_VALUE; //Set serial prescalers from util/setbaud
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
  UCSR0A |= (1 << U2X0);
  #else
  UCSR0A &= ~(1 << U2X0);
  #endif

  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //use 8 bit serial
  UCSR0C &= ~((1 << UMSEL00) |(1 << UMSEL01)); //Use Asynch USART
  UCSR0C &= ~((1 << UPM00) |(1 << UPM01)); //Use no parity
  UCSR0C &= ~(1 << USBS0); //Use 1 Stop Bit
  UCSR0B |= (1 << RXEN0); //enable serial rx

  UCSR0B |= (1 << RXCIE0); //Enable rx intterupt
  sei(); //allow global interrupts
}

//Called on new data in rx buffer interrupt
static void rxComplete(void) {
  //Standard cyclic buffer
  byte data = UDR0;
  byte nextIndex = (byte)(mRxBufferHead + 1) % RX_BUFFER_SIZE;

  //Dont let the head (i.e. position of latest data) catch the tail (i.e pos of earliest unread data)
  if (nextIndex != mRxBufferTail) {
    mRxBuffer[mRxBufferHead] = data;
    mRxBufferHead = nextIndex;
  }
}

ISR(USART_RX_vect) {
  rxComplete();
}