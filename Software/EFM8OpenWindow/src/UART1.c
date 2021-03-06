/*
 * UART1.c
 *
 *  Created on: 29 Sep 2020
 *      Author: alan
 */

#include "UART1.h"
#include "buffer.h"
#include <SI_EFM8BB2_Register_Enums.h>


#define UART1_SFR_PAGE 0x20

static buffer_t transmit_buffer;
static buffer_t receive_buffer;
static bool transmitting;

// Private functions
static char UART1_read(void);
static void UART1_write(char c);

char UART1_read(void) {
  uint8_t value;
  uint8_t old_page = SFRPAGE;

  SFRPAGE = UART1_SFR_PAGE;
  value = SBUF1;
  SFRPAGE = old_page;

  return value;
}

void UART1_write(char c) {
  uint8_t old_page = SFRPAGE;

  SFRPAGE = UART1_SFR_PAGE;
  SBUF1 = c;
  SFRPAGE = old_page;
}

// Public functions
void UART1_init(void) {
  // Enable transmit completion interrupt
  uint8_t old_page = SFRPAGE;
  int i;
  SFRPAGE = UART1_SFR_PAGE;
  UART1FCN1_TIE = 1;
  SFRPAGE = old_page;

  transmit_buffer.read_index = 0;
  transmit_buffer.write_index = 0;
  receive_buffer.read_index = 0;
  receive_buffer.read_index = 0;

  for(i = 0; i < BUFFER_SIZE; i++) {
      transmit_buffer.values[i] = -1;
      receive_buffer.values[i] = -1;
  }

  transmitting = false;
}

char putchar(char c) {
  uint8_t value;
  bool success;

  success = buffer_put(&transmit_buffer, c);

  if (!transmitting && success) {
    success = buffer_get(&transmit_buffer, &value);

    if (success) {
      transmitting = true;
      UART1_write(value);
    }
  }
  return c;
}

// ISR callbacks
void UART1_tx_callback(void) {
  uint8_t value;
  bool success;
  uint8_t interrupt_status = IE_EA;
  IE_EA = 0;

  success = buffer_get(&transmit_buffer, &value);

  if (success) {
    UART1_write(value);
  }
  else {
    transmitting = false;
  }
  IE_EA = interrupt_status;
}

void UART1_rx_callback(void) {
}


