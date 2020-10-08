/*
 * switch.c
 *
 *  Created on: 8 Oct 2020
 *      Author: alan
 */

#include "switch.h"
#include <SI_EFM8BB2_Register_Enums.h>

#define CMP_SFR_PAGE 0x00

void switch_init(void) {
  uint8_t old_page = SFRPAGE;

  SFRPAGE = CMP_SFR_PAGE;

  // Clear all interrupt flags
  CMP0CN0 &= ~CMP0CN0_CPRIF__BMASK;
  CMP0CN0 &= ~CMP0CN0_CPFIF__BMASK;
  CMP1CN0 &= ~CMP1CN0_CPRIF__BMASK;
  CMP1CN0 &= ~CMP1CN0_CPFIF__BMASK;

  // Enable rising and falling edge interrupst for CMP0 and CMP1
  CMP0MD |= CMP0MD_CPFIE__FALL_INT_ENABLED | CMP0MD_CPRIE__RISE_INT_ENABLED;
  CMP1MD |= CMP1MD_CPFIE__FALL_INT_ENABLED | CMP1MD_CPRIE__RISE_INT_ENABLED;

  SFRPAGE = old_page;
}


