//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8BB2_Register_Enums.h>
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library Includes]
// [Library Includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void
enter_DefaultMode_from_RESET (void)
{
  // $[Config Calls]
  // Save the SFRPAGE
  uint8_t SFRPAGE_save = SFRPAGE;
  WDT_0_enter_DefaultMode_from_RESET ();
  PORTS_0_enter_DefaultMode_from_RESET ();
  PORTS_1_enter_DefaultMode_from_RESET ();
  PBCFG_0_enter_DefaultMode_from_RESET ();
  CMP_0_enter_DefaultMode_from_RESET ();
  CMP_1_enter_DefaultMode_from_RESET ();
  CLOCK_0_enter_DefaultMode_from_RESET ();
  UARTE_1_enter_DefaultMode_from_RESET ();
  INTERRUPT_0_enter_DefaultMode_from_RESET ();
  // Restore the SFRPAGE
  SFRPAGE = SFRPAGE_save;
  // [Config Calls]$

}

extern void
WDT_0_enter_DefaultMode_from_RESET (void)
{
  // $[Watchdog Timer Init Variable Declarations]
  uint32_t i;
  bool ea;
  // [Watchdog Timer Init Variable Declarations]$

  // $[WDTCN - Watchdog Timer Control]
  // Deprecated
  // [WDTCN - Watchdog Timer Control]$

  // $[WDTCN_2 - Watchdog Timer Control]
  SFRPAGE = 0x00;

  // Feed WDT timer before disabling (Erratum WDT_E102)
  WDTCN = 0xA5;

  // Add 2 LFO cycle delay before disabling WDT (Erratum WDT_E102)
  for (i = 0; i < (2 * 3062500UL) / (80000 * 3); i++)
    {
      NOP ();
    }

  // Disable WDT
  ea = IE_EA;
  IE_EA = 0;
  WDTCN = 0xDE;
  WDTCN = 0xAD;
  IE_EA = ea;

  // [WDTCN_2 - Watchdog Timer Control]$

}

extern void
PBCFG_0_enter_DefaultMode_from_RESET (void)
{
  // $[XBR2 - Port I/O Crossbar 2]
  /***********************************************************************
   - Weak Pullups enabled 
   - Crossbar enabled
   - UART1 TX1 RX1 routed to Port pins
   - UART1 RTS1 unavailable at Port pin
   - UART1 CTS1 unavailable at Port pin
   ***********************************************************************/
  XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED
      | XBR2_URT1E__ENABLED | XBR2_URT1RTSE__DISABLED | XBR2_URT1CTSE__DISABLED;
  // [XBR2 - Port I/O Crossbar 2]$

  // $[PRTDRV - Port Drive Strength]
  // [PRTDRV - Port Drive Strength]$

  // $[XBR0 - Port I/O Crossbar 0]
  // [XBR0 - Port I/O Crossbar 0]$

  // $[XBR1 - Port I/O Crossbar 1]
  // [XBR1 - Port I/O Crossbar 1]$

}

extern void
UARTE_1_enter_DefaultMode_from_RESET (void)
{
  // $[SBCON1 - UART1 Baud Rate Generator Control]
  /***********************************************************************
   - Enable the baud rate generator
   - Prescaler = 1
   ***********************************************************************/
  SFRPAGE = 0x20;
  SBCON1 = SBCON1_BREN__ENABLED | SBCON1_BPS__DIV_BY_1;
  // [SBCON1 - UART1 Baud Rate Generator Control]$

  // $[SMOD1 - UART1 Mode]
  // [SMOD1 - UART1 Mode]$

  // $[UART1FCN0 - UART1 FIFO Control 0]
  // [UART1FCN0 - UART1 FIFO Control 0]$

  // $[SBRLH1 - UART1 Baud Rate Generator High Byte]
  /***********************************************************************
   - UART1 Baud Rate Reload High = 0xFF
   ***********************************************************************/
  SBRLH1 = (0xFF << SBRLH1_BRH__SHIFT);
  // [SBRLH1 - UART1 Baud Rate Generator High Byte]$

  // $[SBRLL1 - UART1 Baud Rate Generator Low Byte]
  /***********************************************************************
   - UART1 Baud Rate Reload Low = 0x96
   ***********************************************************************/
  SBRLL1 = (0x96 << SBRLL1_BRL__SHIFT);
  // [SBRLL1 - UART1 Baud Rate Generator Low Byte]$

  // $[UART1LIN - UART1 LIN Configuration]
  // [UART1LIN - UART1 LIN Configuration]$

  // $[SCON1 - UART1 Serial Port Control]
  /***********************************************************************
   - UART1 reception enabled
   ***********************************************************************/
  SCON1 |= SCON1_REN__RECEIVE_ENABLED;
  // [SCON1 - UART1 Serial Port Control]$

  // $[UART1FCN1 - UART1 FIFO Control 1]
  // [UART1FCN1 - UART1 FIFO Control 1]$

}

extern void
PORTS_0_enter_DefaultMode_from_RESET (void)
{
  // $[P0 - Port 0 Pin Latch]
  // [P0 - Port 0 Pin Latch]$

  // $[P0MDOUT - Port 0 Output Mode]
  /***********************************************************************
   - P0.0 output is open-drain
   - P0.1 output is open-drain
   - P0.2 output is open-drain
   - P0.3 output is open-drain
   - P0.4 output is push-pull
   - P0.5 output is open-drain
   - P0.6 output is open-drain
   - P0.7 output is open-drain
   ***********************************************************************/
  P0MDOUT = P0MDOUT_B0__OPEN_DRAIN | P0MDOUT_B1__OPEN_DRAIN
      | P0MDOUT_B2__OPEN_DRAIN | P0MDOUT_B3__OPEN_DRAIN | P0MDOUT_B4__PUSH_PULL
      | P0MDOUT_B5__OPEN_DRAIN | P0MDOUT_B6__OPEN_DRAIN
      | P0MDOUT_B7__OPEN_DRAIN;
  // [P0MDOUT - Port 0 Output Mode]$

  // $[P0MDIN - Port 0 Input Mode]
  /***********************************************************************
   - P0.0 pin is configured for analog mode
   - P0.1 pin is configured for digital mode
   - P0.2 pin is configured for digital mode
   - P0.3 pin is configured for digital mode
   - P0.4 pin is configured for digital mode
   - P0.5 pin is configured for digital mode
   - P0.6 pin is configured for digital mode
   - P0.7 pin is configured for digital mode
   ***********************************************************************/
  P0MDIN = P0MDIN_B0__ANALOG | P0MDIN_B1__DIGITAL | P0MDIN_B2__DIGITAL
      | P0MDIN_B3__DIGITAL | P0MDIN_B4__DIGITAL | P0MDIN_B5__DIGITAL
      | P0MDIN_B6__DIGITAL | P0MDIN_B7__DIGITAL;
  // [P0MDIN - Port 0 Input Mode]$

  // $[P0SKIP - Port 0 Skip]
  /***********************************************************************
   - P0.0 pin is skipped by the crossbar
   - P0.1 pin is skipped by the crossbar
   - P0.2 pin is skipped by the crossbar
   - P0.3 pin is skipped by the crossbar
   - P0.4 pin is not skipped by the crossbar
   - P0.5 pin is not skipped by the crossbar
   - P0.6 pin is not skipped by the crossbar
   - P0.7 pin is not skipped by the crossbar
   ***********************************************************************/
  P0SKIP = P0SKIP_B0__SKIPPED | P0SKIP_B1__SKIPPED | P0SKIP_B2__SKIPPED
      | P0SKIP_B3__SKIPPED | P0SKIP_B4__NOT_SKIPPED | P0SKIP_B5__NOT_SKIPPED
      | P0SKIP_B6__NOT_SKIPPED | P0SKIP_B7__NOT_SKIPPED;
  // [P0SKIP - Port 0 Skip]$

  // $[P0MASK - Port 0 Mask]
  // [P0MASK - Port 0 Mask]$

  // $[P0MAT - Port 0 Match]
  // [P0MAT - Port 0 Match]$

}

extern void
CLOCK_0_enter_DefaultMode_from_RESET (void)
{
  // $[HFOSC1 Setup]
  // [HFOSC1 Setup]$

  // $[CLKSEL - Clock Select]
  /***********************************************************************
   - Clock derived from the Internal High Frequency Oscillator 0
   - SYSCLK is equal to selected clock source divided by 1
   ***********************************************************************/
  CLKSEL = CLKSEL_CLKSL__HFOSC0 | CLKSEL_CLKDIV__SYSCLK_DIV_1;
  while ((CLKSEL & CLKSEL_DIVRDY__BMASK) == CLKSEL_DIVRDY__NOT_READY)
    ;
  // [CLKSEL - Clock Select]$

}

extern void
INTERRUPT_0_enter_DefaultMode_from_RESET (void)
{
  // $[EIE1 - Extended Interrupt Enable 1]
  /***********************************************************************
   - Disable ADC0 Conversion Complete interrupt
   - Disable ADC0 Window Comparison interrupt
   - Enable interrupt requests generated by the comparator 0 CPRIF or CPFIF
   flags
   - Enable interrupt requests generated by the comparator 1 CPRIF or CPFIF
   flags
   - Disable all Port Match interrupts
   - Disable all PCA0 interrupts
   - Disable all SMB0 interrupts
   - Disable Timer 3 interrupts
   ***********************************************************************/
  SFRPAGE = 0x00;
  EIE1 = EIE1_EADC0__DISABLED | EIE1_EWADC0__DISABLED | EIE1_ECP0__ENABLED
      | EIE1_ECP1__ENABLED | EIE1_EMAT__DISABLED | EIE1_EPCA0__DISABLED
      | EIE1_ESMB0__DISABLED | EIE1_ET3__DISABLED;
  // [EIE1 - Extended Interrupt Enable 1]$

  // $[EIE2 - Extended Interrupt Enable 2]
  /***********************************************************************
   - Disable all I2C0 slave interrupts
   - Disable Timer 4 interrupts
   - Enable UART1 interrupts
   ***********************************************************************/
  SFRPAGE = 0x10;
  EIE2 = EIE2_EI2C0__DISABLED | EIE2_ET4__DISABLED | EIE2_ES1__ENABLED;
  // [EIE2 - Extended Interrupt Enable 2]$

  // $[EIP1H - Extended Interrupt Priority 1 High]
  // [EIP1H - Extended Interrupt Priority 1 High]$

  // $[EIP1 - Extended Interrupt Priority 1 Low]
  // [EIP1 - Extended Interrupt Priority 1 Low]$

  // $[EIP2 - Extended Interrupt Priority 2]
  // [EIP2 - Extended Interrupt Priority 2]$

  // $[EIP2H - Extended Interrupt Priority 2 High]
  // [EIP2H - Extended Interrupt Priority 2 High]$

  // $[IE - Interrupt Enable]
  /***********************************************************************
   - Enable each interrupt according to its individual mask setting
   - Disable external interrupt 0
   - Disable external interrupt 1
   - Disable all SPI0 interrupts
   - Disable all Timer 0 interrupt
   - Disable all Timer 1 interrupt
   - Disable Timer 2 interrupt
   - Disable UART0 interrupt
   ***********************************************************************/
  SFRPAGE = 0x00;
  IE = IE_EA__ENABLED | IE_EX0__DISABLED | IE_EX1__DISABLED | IE_ESPI0__DISABLED
      | IE_ET0__DISABLED | IE_ET1__DISABLED | IE_ET2__DISABLED
      | IE_ES0__DISABLED;
  // [IE - Interrupt Enable]$

  // $[IP - Interrupt Priority]
  // [IP - Interrupt Priority]$

  // $[IPH - Interrupt Priority High]
  // [IPH - Interrupt Priority High]$

}

extern void
CMP_0_enter_DefaultMode_from_RESET (void)
{
  // $[CMP0MX - Comparator 0 Multiplexer Selection]
  /***********************************************************************
   - External pin CMP0P.0
   - External pin CMP0N.15
   ***********************************************************************/
  uint8_t delay;

  CMP0MX = CMP0MX_CMXP__CMP0P0 | CMP0MX_CMXN__CMP0N15;
  // Delay to allow the comparator inputs to settle
  for (delay = 0; delay < 0x20; delay++)
    ;
  // [CMP0MX - Comparator 0 Multiplexer Selection]$

  // $[CMP0CN1 - Comparator 0 Control 1]
  /***********************************************************************
   - Internal Comparator DAC Reference Level = 0x27
   - The comparator output will always reflect the input conditions
   ***********************************************************************/
  SFRPAGE = 0x10;
  CMP0CN1 = (0x27 << CMP0CN1_DACLVL__SHIFT) | CMP0CN1_CPINH__DISABLED;
  // [CMP0CN1 - Comparator 0 Control 1]$

  // $[CMP0MD - Comparator 0 Mode]
  /***********************************************************************
   - Connect the CMP- input to the internal DAC output, and CMP+ is
   selected by CMXP
   - Comparator falling-edge interrupt enabled
   - Comparator rising-edge interrupt enabled
   ***********************************************************************/
  SFRPAGE = 0x00;
  CMP0MD |= CMP0MD_INSL__CMXP_DAC | CMP0MD_CPFIE__FALL_INT_ENABLED
      | CMP0MD_CPRIE__RISE_INT_ENABLED;
  // [CMP0MD - Comparator 0 Mode]$

  // $[CMP0CN0 - Comparator 0 Control 0]
  /***********************************************************************
   - Comparator enabled
   - Positive Hysteresis = Hysteresis 3 
   - Negative Hysteresis = Hysteresis 3 
   ***********************************************************************/
  CMP0CN0 |= CMP0CN0_CPEN__ENABLED | CMP0CN0_CPHYP__ENABLED_MODE3
      | CMP0CN0_CPHYN__ENABLED_MODE3;
  // [CMP0CN0 - Comparator 0 Control 0]$

}

extern void
PORTS_1_enter_DefaultMode_from_RESET (void)
{
  // $[P1 - Port 1 Pin Latch]
  // [P1 - Port 1 Pin Latch]$

  // $[P1MDOUT - Port 1 Output Mode]
  // [P1MDOUT - Port 1 Output Mode]$

  // $[P1MDIN - Port 1 Input Mode]
  /***********************************************************************
   - P1.0 pin is configured for digital mode
   - P1.1 pin is configured for analog mode
   - P1.2 pin is configured for digital mode
   - P1.3 pin is configured for digital mode
   - P1.4 pin is configured for digital mode
   - P1.5 pin is configured for digital mode
   - P1.6 pin is configured for digital mode
   - P1.7 pin is configured for digital mode
   ***********************************************************************/
  P1MDIN = P1MDIN_B0__DIGITAL | P1MDIN_B1__ANALOG | P1MDIN_B2__DIGITAL
      | P1MDIN_B3__DIGITAL | P1MDIN_B4__DIGITAL | P1MDIN_B5__DIGITAL
      | P1MDIN_B6__DIGITAL | P1MDIN_B7__DIGITAL;
  // [P1MDIN - Port 1 Input Mode]$

  // $[P1SKIP - Port 1 Skip]
  /***********************************************************************
   - P1.0 pin is not skipped by the crossbar
   - P1.1 pin is skipped by the crossbar
   - P1.2 pin is not skipped by the crossbar
   - P1.3 pin is not skipped by the crossbar
   - P1.4 pin is not skipped by the crossbar
   - P1.5 pin is not skipped by the crossbar
   - P1.6 pin is not skipped by the crossbar
   - P1.7 pin is not skipped by the crossbar
   ***********************************************************************/
  P1SKIP = P1SKIP_B0__NOT_SKIPPED | P1SKIP_B1__SKIPPED | P1SKIP_B2__NOT_SKIPPED
      | P1SKIP_B3__NOT_SKIPPED | P1SKIP_B4__NOT_SKIPPED | P1SKIP_B5__NOT_SKIPPED
      | P1SKIP_B6__NOT_SKIPPED | P1SKIP_B7__NOT_SKIPPED;
  // [P1SKIP - Port 1 Skip]$

  // $[P1MASK - Port 1 Mask]
  // [P1MASK - Port 1 Mask]$

  // $[P1MAT - Port 1 Match]
  // [P1MAT - Port 1 Match]$

}

extern void
CMP_1_enter_DefaultMode_from_RESET (void)
{
  // $[CMP1MX - Comparator 1 Multiplexer Selection]
  /***********************************************************************
   - External pin CMP1P.1
   - External pin CMP1N.15
   ***********************************************************************/
  uint8_t delay;

  CMP1MX = CMP1MX_CMXP__CMP1P1 | CMP1MX_CMXN__CMP1N15;
  // Delay to allow the comparator inputs to settle
  for (delay = 0; delay < 0x20; delay++)
    ;
  // [CMP1MX - Comparator 1 Multiplexer Selection]$

  // $[CMP1CN1 - Comparator 1 Control 1]
  /***********************************************************************
   - Internal Comparator DAC Reference Level = 0x13
   - The comparator output will always reflect the input conditions
   ***********************************************************************/
  SFRPAGE = 0x10;
  CMP1CN1 = (0x13 << CMP1CN1_DACLVL__SHIFT) | CMP1CN1_CPINH__DISABLED;
  // [CMP1CN1 - Comparator 1 Control 1]$

  // $[CMP1MD - Comparator 1 Mode]
  /***********************************************************************
   - Connect the CMP- input to the internal DAC output, and CMP+ is
   selected by CMXP
   - Comparator falling-edge interrupt enabled
   - Comparator rising-edge interrupt enabled
   ***********************************************************************/
  SFRPAGE = 0x00;
  CMP1MD |= CMP1MD_INSL__CMXP_DAC | CMP1MD_CPFIE__FALL_INT_ENABLED
      | CMP1MD_CPRIE__RISE_INT_ENABLED;
  // [CMP1MD - Comparator 1 Mode]$

  // $[CMP1CN0 - Comparator 1 Control 0]
  /***********************************************************************
   - Comparator enabled
   - Positive Hysteresis = Hysteresis 3 
   - Negative Hysteresis = Hysteresis 3 
   ***********************************************************************/
  CMP1CN0 |= CMP1CN0_CPEN__ENABLED | CMP1CN0_CPHYP__ENABLED_MODE3
      | CMP1CN0_CPHYN__ENABLED_MODE3;
  // [CMP1CN0 - Comparator 1 Control 0]$

}

