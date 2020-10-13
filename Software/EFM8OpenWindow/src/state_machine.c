/*
 * state_machine.c
 *
 *  Created on: 8 Oct 2020
 *      Author: alan
 */

#include <SI_EFM8BB2_Register_Enums.h>
#include "state_machine.h"
#include "buffer.h"
#include "safe_print.h"
#include "motor.h"
#include "ADC.h"

typedef enum {
  SM_STATE_IDLE,
  SM_STATE_RAISING,
  SM_STATE_LOWERING,
  SM_STATE_ERROR,
} sm_state_t;

typedef enum {
  SM_POSITION_TOP,
  SM_POSITION_MIDDLE,
  SM_POSITION_BOTTOM,
} sm_position_t;

static sm_state_t state;
static sm_position_t position;
static sm_event_t new_event;

// Transition functions
static void enter_error(char *error_string);
static void enter_idle(sm_position_t new_position);
static void enter_lowering(void);
static void enter_raising(void);
static void ignore_event(char *message);

void sm_init(void) {
  motor_stop();
  ADC_stop();
  state = SM_STATE_IDLE;
  position = SM_POSITION_MIDDLE;
  new_event = SM_EVENT_NONE;
}

void sm_run(void) {
  if(new_event != SM_EVENT_NONE) {
    switch (state) {
      case SM_STATE_IDLE:
        switch (new_event) {
          case SM_EVENT_SWITCH_TO_IDLE:
            if (position == SM_POSITION_MIDDLE) {
              enter_error("Switch should already be idle");
            }
            else {
              ignore_event("Motor already idle");
            }
            break;

          case SM_EVENT_SWITCH_TO_RAISE:
            if (position != SM_POSITION_TOP) {
              enter_raising();
            }
            else {
              ignore_event("Window already at top");
            }
            break;

          case SM_EVENT_SWITCH_TO_LOWER:
            if (position != SM_POSITION_BOTTOM) {
              enter_lowering();
            }
            else {
              ignore_event("Window already at bottom");
            }
            break;

          case SM_EVENT_CURRENT_LIMIT:
            enter_error("Current limit alert exceeded while idle");
            break;

          default:
            enter_error("Unhandled event type");
        }
        break;

      case SM_STATE_RAISING:
        switch (new_event) {
          case SM_EVENT_SWITCH_TO_IDLE:
            enter_idle(SM_POSITION_MIDDLE);
            break;

          case SM_EVENT_SWITCH_TO_RAISE:
            enter_error("Motor already raising");
            break;

          case SM_EVENT_SWITCH_TO_LOWER:
            enter_error("Can't switch from raise to lower directly");
            break;

          case SM_EVENT_CURRENT_LIMIT:
            enter_idle(SM_POSITION_TOP);
            break;

          default:
            enter_error("Unhandled event type");
        }
        break;

      case SM_STATE_LOWERING:
        switch (new_event) {
          case SM_EVENT_SWITCH_TO_IDLE:
            enter_idle(SM_POSITION_MIDDLE);
            break;

          case SM_EVENT_SWITCH_TO_RAISE:
            enter_error("Can't switch from lower to raise directly");
            break;

          case SM_EVENT_SWITCH_TO_LOWER:
            enter_error("Motor already lowering");
            break;

          case SM_EVENT_CURRENT_LIMIT:
            enter_idle(SM_POSITION_BOTTOM);
            break;

          default:
            enter_error("Unhandled event type");
        }
        break;

      case SM_STATE_ERROR:
        safe_printf("Event %d ignored in error state\r\n", (int)new_event);
        new_event = SM_EVENT_NONE;
        break;

      default:
        enter_error("Unknown state");
    }
  }
}

void sm_raise_event(sm_event_t event) reentrant {
  uint8_t interrupt_status = IE_EA;
  IE_EA = 0;
  if(new_event == SM_EVENT_NONE) {
    new_event = event;
  }
  else {
    safe_printf("Error: event overflow!\r\n");
    new_event = SM_EVENT_SWITCH_TO_IDLE;
  }
  IE_EA = interrupt_status;
}

// Transition functions

static void enter_error(char *error_string) {
  safe_printf("Error on event %d in state %d: ", (int)new_event, (int)state);
  safe_printf("%s\r\n", error_string);
//  motor_stop();
//  ADC_stop();
//  state = SM_STATE_ERROR;
//  new_event = SM_EVENT_NONE;

  enter_idle(SM_POSITION_MIDDLE);
}

static void enter_idle(sm_position_t new_position) {
  safe_printf("Returning to idle\r\n");
  motor_stop();
  ADC_stop();
  state = SM_STATE_IDLE;
  position = new_position;
  new_event = SM_EVENT_NONE;
}

static void enter_lowering(void) {
  safe_printf("Starting window lowering\r\n");
  motor_start_lowering();
  ADC_start(ADC_MIN_LOWER_VAL, ADC_MAX_LOWER_VAL);
  state = SM_STATE_LOWERING;
  new_event = SM_EVENT_NONE;
}

static void enter_raising(void) {
  safe_printf("Starting window raising\r\n");
  motor_start_raising();
  ADC_start(ADC_MIN_RAISE_VAL, ADC_MAX_RAISE_VAL);
  state = SM_STATE_RAISING;
  new_event = SM_EVENT_NONE;
}

static void ignore_event(char *message) {
  safe_printf("%s\r\n", message);
  new_event = SM_EVENT_NONE;
}

