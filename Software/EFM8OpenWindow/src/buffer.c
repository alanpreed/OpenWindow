/*
 * buffer.c
 *
 *  Created on: 29 Sep 2020
 *      Author: alan
 */

#include "buffer.h"

uint8_t buffer_count(buffer_t *buffer) {
  if (buffer == NULL) {
    return 0;
  }

  return buffer->write_index - buffer->read_index;
}

bool buffer_put(buffer_t *buffer, uint8_t value) {
  if (buffer == NULL || buffer_count(buffer) == BUFFER_SIZE) {
      return false;
  }

  buffer->values[buffer->write_index % BUFFER_SIZE] = value;
  buffer->write_index++;

  return true;
}

bool buffer_get(buffer_t *buffer, uint8_t *value) {
  if (buffer == NULL || buffer_count(buffer) == 0 ) {
      return false;
  }

  *value = buffer->values[buffer->read_index % BUFFER_SIZE];
  buffer->read_index++;

  return false;
}
