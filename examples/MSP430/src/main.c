#include "msp430fr5994.h"
#include "user_main.h"
#include <msp430.h>

void initClockTo16MHz()
{
    PJSEL0 |= BIT4 | BIT5;                  // For XT1
    
    // Configure one FRAM waitstate as required by the device datasheet for MCLK
    // operation beyond 8MHz _before_ configuring the clock system.
    FRCTL0 = FRCTLPW | NWAITS_1;

    // Clock System Setup
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_0;                     // Set DCO to 1MHz
    // Set SMCLK = MCLK = DCO, ACLK = LFXTCLK (VLOCLK if unavailable)
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
    // Per Device Errata set divider to 4 before changing frequency to
    // prevent out of spec operation from overshoot transient
    CSCTL3 = DIVA__4 | DIVS__4 | DIVM__4;   // Set all corresponding clk sources to divide by 4 for errata
    CSCTL1 = DCOFSEL_4 | DCORSEL;           // Set DCO to 16MHz
    // Delay by ~10us to let DCO settle. 60 cycles = 20 cycles buffer + (10us / (1/4MHz))
    __delay_cycles(60);
    CSCTL3 = DIVA__1 | DIVS__2 | DIVM__1;   // Set MCLK to 16MHz SMCLK to 8 MHz

    CSCTL4 &= ~LFXTOFF;
    do
    {
        CSCTL5 &= ~LFXTOFFG;                      // Clear XT1 fault flag
        SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

    CSCTL0_H = 0;                             // Lock CS registerss
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT

    // // Use 8MHz
    // CSCTL0 = CSKEY;
    // CSCTL3 &= ~DIVS & ~DIVM;

    // // Use MCLK = 16MHz SMCLK = 8MHz
    // FRCTL0 = FRCTLPW | NWAITS_1;            // Set FRAM wait state
    // CSCTL0 = CSKEY;
    // CSCTL3 = DIVS__2 | DIVM__1;             
    // CSCTL1_L = DCORSEL | DCOFSEL_4;         // set DSO to 16MHz

    initClockTo16MHz();

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    // Configure GPIO
    // P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    // P1DIR |= BIT0;                          // Set P1.0 to output direction

    user_main();
}
