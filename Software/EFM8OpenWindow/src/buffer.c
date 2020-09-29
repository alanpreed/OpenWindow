/*
 * buffer.c
 *
 *  Created on: 29 Sep 2020
 *      Author: alan
 */

#include "buffer.h"
#include <SI_EFM8BB2_Register_Enums.h>

uint8_t buffer_count(buffer_t *buffer) {
  uint8_t interrupt_status = IE_EA;
  IE_EA = 0;

  if (buffer == NULL) {
      IE_EA = interrupt_status;
    return 0;
  }
  IE_EA = interrupt_status;
  return buffer->write_index - buffer->read_index;
}

bool buffer_put(buffer_t *buffer, uint8_t value) {
  uint8_t interrupt_status = IE_EA;
  IE_EA = 0;

  if (buffer == NULL || buffer_count(buffer) == BUFFER_SIZE) {
      IE_EA = interrupt_status;
      return false;
  }

  buffer->values[buffer->write_index % BUFFER_SIZE] = value;
  buffer->write_index++;
  IE_EA = interrupt_status;
  return true;
}

bool buffer_get(buffer_t *buffer, uint8_t *value) {
  uint8_t interrupt_status = IE_EA;
  IE_EA = 0;

  if (buffer == NULL || buffer_count(buffer) == 0 ) {
      IE_EA = interrupt_status;
      return false;
  }

  *value = buffer->values[buffer->read_index % BUFFER_SIZE];
  buffer->read_index++;

  IE_EA = interrupt_status;
  return true;
}
