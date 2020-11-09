// Copyright 2019 George Rennie
#include "SerialRead.h"

uint8_t mRxBuffer[RX_BUFFER_SIZE];
uint8_t mRxBufferHead = 0;
uint8_t mRxBufferTail = 0;
uint8_t mDataInBuffer = 0;

// Reads a byte from the ring buffer
int serialReadByte(void) {
  if (!mDataInBuffer) {
    return -1;
  } else {
    uint8_t data = mRxBuffer[mRxBufferTail];
    mRxBufferTail = (uint8_t)((mRxBufferTail + 1) % RX_BUFFER_SIZE);
    if (mRxBufferHead == mRxBufferTail) { mDataInBuffer = 0; };
    return data;
  }
}

uint8_t serialAvailable(void) {
  // Returns 0 only when the buffer pointers are the same value
  // i.e. whenever there is data in the buffer the pointers are at dif places
  // therefore it returns the number of bytes in buffer
  return (uint8_t)(RX_BUFFER_SIZE + mRxBufferHead - mRxBufferTail)
    % RX_BUFFER_SIZE;
}

void serialSetup(void) {
  #include <util/setbaud.h>

  UBRR0H = UBRRH_VALUE; // Set serial prescalers from util/setbaud
  UBRR0L = UBRRL_VALUE;
  #if USE_2X
  UCSR0A |= (1 << U2X0);
  #else
  UCSR0A &= ~(1 << U2X0);
  #endif

  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Use 8 bit serial
  UCSR0C &= ~((1 << UMSEL00) |(1 << UMSEL01)); // Use Asynch USART
  UCSR0C &= ~((1 << UPM00) |(1 << UPM01)); // Use no parity
  UCSR0C &= ~(1 << USBS0); // Use 1 Stop Bit
  UCSR0B |= (1 << RXEN0); // Enable serial rx

  UCSR0B |= (1 << RXCIE0); // Enable rx intterupt
  sei(); // Allow global interrupts
}

// Called on new data in rx buffer interrupt
static void rxComplete(void) {
  // Standard cyclic buffer
  uint8_t data = UDR0;

  // Dont let the head (i.e. position of latest data)
  // catch the tail (i.e pos of earliest unread data)
  if ((mRxBufferHead != mRxBufferTail) || !mDataInBuffer) {
    mRxBuffer[mRxBufferHead] = data;
    mRxBufferHead = (mRxBufferHead + 1) % RX_BUFFER_SIZE;
    mDataInBuffer = 1;
  }
}

ISR(USART_RX_vect) {
  rxComplete();
}
