/*
 * ADC.c
 *
 *  Created on: 29 Sep 2020
 *      Author: alan
 */

#include "ADC.h"
#include <si_toolchain.h>
#include <SI_EFM8BB2_Register_Enums.h>
#include "safe_print.h"

#define ADC_SFR_PAGE 0x10

void ADC_start(uint16_t min_val, uint16_t max_val) {

  // Set window interrupt values
  uint8_t old_page = SFRPAGE;

  SFRPAGE = ADC_SFR_PAGE;

  ADC0GT = max_val;
  ADC0LT = min_val;

  SFRPAGE = old_page;

  // Start timer 0
   TCON |= TCON_TR0__RUN;
}

void ADC_stop(void) {
  // Stop timer 0
  TCON &= ~TCON_TR0__RUN;
}

void ADC_callback(void) {
  uint8_t low_byte = ADC0L;
  uint8_t high_byte = ADC0H;
  uint16_t result = (uint16_t)low_byte + ((uint16_t)high_byte << 8);

  safe_printf("ADC result: %d\r\n", result);
}
