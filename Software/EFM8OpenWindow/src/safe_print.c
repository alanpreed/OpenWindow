/*
 * safe_print.c
 *
 *  Created on: 5 Oct 2020
 *      Author: alan
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <SI_EFM8BB2_Register_Enums.h>

void safe_printf( const char* format, ... ) {
  uint8_t interrupt_status;
  va_list args;

  interrupt_status = IE_EA;
  IE_EA = 0;
  va_start( args, format );
  vprintf(format, args );
  va_end( args );
  IE_EA = interrupt_status;
}
