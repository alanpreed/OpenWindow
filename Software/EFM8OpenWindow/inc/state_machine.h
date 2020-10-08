/*
 * state_machine.h
 *
 *  Created on: 8 Oct 2020
 *      Author: alan
 */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

typedef enum {
  SM_EVENT_NONE,
  SM_EVENT_SWITCH_TO_IDLE,
  SM_EVENT_SWITCH_TO_RAISE,
  SM_EVENT_SWITCH_TO_LOWER,
  SM_EVENT_CURRENT_LIMIT,
  SM_EVENT_ERROR,
} sm_event_t;

void sm_init(void);

void sm_run(void);

void sm_raise_event(sm_event_t event) reentrant;


#endif /* INC_STATE_MACHINE_H_ */
