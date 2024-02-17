#include "benchmark_util.h"
#include "msp430fr5994.h"

#include <msp430.h>
#include <stdio.h>

#ifdef USE_DUMMY_DATA
#include "test_data.h"
#endif

void timer_initialize()
{
    TA0EX0 = TAIDEX__8;                                 // divide clock by 8 (total will be 64)
    TA0CTL |= TASSEL__SMCLK | MC__CONTINUOUS | ID__8;   // Use 8MHz SMCLK, Continuous mode, divide clock by 8
}

void timer_reset()
{
    TA0R = 0;
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
    return TA0R;
}

void delay_10000us()
{
    __delay_cycles(160000);
}

void uart_initialize()
{
    UCA0CTLW0 |= UCSWRST;                           // Hold UART module in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;                     // Use SMCLK as clk source
                                                    // Set baudrate to 115200 8-N-1
    UCA0BRW = 4;                                    // UCBRx = 8
    UCA0MCTLW = UCBRF_5 | UCOS16_1 | 0x5500;        // UCBRSx = 0xF7 UCBRFx = 10, UCOS16 = 1
    P2SEL1 |= BIT0 | BIT1;                          // Configure port for USCI_A0 UART operation
    P2SEL0 &= ~BIT0 & ~BIT1;
    UCA0CTLW0 &= ~UCSWRST;                          // Start UART module
}

char buffer[32];

void uart_write_string(char* s)
{
    while (*s)
    {
        while (!(UCA0IFG & UCTXIFG));
        UCA0TXBUF = *s;
        s++;
    }
}

void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime)
{
    sprintf(buffer, "%d %uus\r\n", result, runtime);    // timer resolution = 8us (8MHz / 64 = 125Khz)
    uart_write_string(buffer);
}

void uart_send_debug_p(MICROVSA_ACC_DTYPE arr[], uint8_t len)
{
    uint8_t i;
    for (i=0; i<len; i++)
    {
        sprintf(buffer, "%d\r\n", arr[i]);
        uart_write_string(buffer);
    }
}

void get_inference_data(uint8_t arr[], uint16_t len)
{
#ifdef USE_DUMMY_DATA
    uint16_t i;
    for (i=0; i<len; i++)
    {
        arr[i] = test_data_sample[i];
    }
#else
    uint16_t i;
    for (i=0; i<len; i++)
    {
        while (!(UCA0IFG & UCRXIFG));
        arr[i] = UCA0RXBUF_L;
    }
#endif
}
