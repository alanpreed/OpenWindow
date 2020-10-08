/*
 * buffer.h
 *
 *  Created on: 29 Sep 2020
 *      Author: alan
 */

#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#define BUFFER_SIZE 200
#include <si_toolchain.h>

typedef struct {
  int read_index;
  int write_index;
  int values[BUFFER_SIZE];
} buffer_t;

uint8_t buffer_count(buffer_t *buffer) reentrant;

bool buffer_put(buffer_t *buffer, uint8_t value) reentrant;

bool buffer_get(buffer_t *buffer, uint8_t *value) reentrant;


#endif /* INC_BUFFER_H_ */
