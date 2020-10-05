//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8BB2_Register_Enums.h>
#include "UART1.h"
#include "ADC.h"
#include "safe_print.h"

//-----------------------------------------------------------------------------
// UART1_ISR
//-----------------------------------------------------------------------------
//
// UART1 ISR Content goes here. Remember to clear flag bits:
// SCON1::RI (Receive Interrupt Flag)
// SCON1::TI (Transmit Interrupt Flag)
// UART1FCN1::RFRQ (Receive FIFO Request)
// UART1FCN1::TFRQ (Transmit FIFO Request)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (UART1_ISR, UART1_IRQn)
  {
    if (SCON1_TI)
      {
        SCON1_TI = 0;
        UART1_tx_callback();
      }
    if (SCON1_RI)
      {
        SCON1_RI = 0;
        UART1_rx_callback();
      }
  }

//-----------------------------------------------------------------------------
// CMP0_ISR
//-----------------------------------------------------------------------------
//
// CMP0 ISR Content goes here. Remember to clear flag bits:
// CMP0CN0::CPFIF (Comparator Falling-Edge Flag)
// CMP0CN0::CPRIF (Comparator Rising-Edge Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (CMP0_ISR, CMP0_IRQn)
  {
    if(CMP0CN0 & CMP0CN0_CPRIF__BMASK)
      {
        // Rising edge flag
        CMP0CN0 = CMP0CN0 ^ CMP0CN0_CPRIF__BMASK;

        // Pull P1.4 high when CMP0 is high
        P1 = (P1 & ~P1_B4__BMASK) + P1_B4__BMASK;

        safe_printf("CMP0 rising\r\n");

      }

    if(CMP0CN0 & CMP0CN0_CPFIF__BMASK)
      {
        // Falling edge flag
        CMP0CN0 = CMP0CN0 ^ CMP0CN0_CPFIF__BMASK;

        // Pull P1.4 low when CMP0 is low
        P1 = P1 & ~P1_B4__BMASK;
        safe_printf("CMP0 falling\r\n");
      }
  }

//-----------------------------------------------------------------------------
// CMP1_ISR
//-----------------------------------------------------------------------------
//
// CMP1 ISR Content goes here. Remember to clear flag bits:
// CMP1CN0::CPFIF (Comparator Falling-Edge Flag)
// CMP1CN0::CPRIF (Comparator Rising-Edge Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (CMP1_ISR, CMP1_IRQn) {
  if(CMP1CN0 & CMP1CN0_CPRIF__BMASK)
    {
      // Rising edge flag
      CMP1CN0 = CMP1CN0 ^ CMP1CN0_CPRIF__BMASK;

      // Pull P1.5 high when CMP1 is high
      P1 = (P1 & ~P1_B5__BMASK) + P1_B5__BMASK;


      safe_printf("CMP1 rising\r\n");

    }

  if(CMP1CN0 & CMP1CN0_CPFIF__BMASK)
    {
      // Falling edge flag
      CMP1CN0 = CMP1CN0 ^ CMP1CN0_CPFIF__BMASK;

      // Pull P1.5 low when CMP1 is low
      P1 = P1 & ~P1_B5__BMASK;

      safe_printf("CMP1 falling\r\n");
    }
}

//-----------------------------------------------------------------------------
// ADC0EOC_ISR
//-----------------------------------------------------------------------------
//
// ADC0EOC ISR Content goes here. Remember to clear flag bits:
// ADC0CN0::ADINT (Conversion Complete Interrupt Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (ADC0EOC_ISR, ADC0EOC_IRQn)
  {
    ADC0CN0_ADINT = 0;
    ADC_callback();
  }

