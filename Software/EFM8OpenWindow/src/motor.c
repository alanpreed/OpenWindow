/*
 * motor.c
 *
 *  Created on: 7 Oct 2020
 *      Author: alan
 */

#include "motor.h"
#include <SI_EFM8BB2_Register_Enums.h>


// Motor control pins: P1.4, P1.5

void motor_start_raising(void) {
  // Pull P1.4 high and P1.5 low
  P1 |= P1_B4__BMASK;
  P1 &= ~P1_B5__BMASK;
}

void motor_start_lowering(void) {
  // Pull P1.4 low and P1.5 high
  P1 &= ~P1_B4__BMASK;
  P1 |= P1_B5__BMASK;
}

void motor_stop(void) {
  // Pull both pins low
  P1 &= ~P1_B4__BMASK;
  P1 &= ~P1_B5__BMASK;
}
