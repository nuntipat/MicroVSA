#include "stm8s.h"
#include "stdio.h"
#include "user_main.h"

void main(void)
{
    // Run at 16MHz
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    user_main();
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
int putchar(int c)
{
    /* Write a character to the UART3 */
    UART3_SendData8(c);
    /* Loop until the end of transmission */
    while (UART3_GetFlagStatus(UART3_FLAG_TXE) == RESET);

    return (c);
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval char Character to Read
  */
int getchar(void)
{
    int c = 0;
    /* Loop until the Read data register flag is SET */
    while (UART3_GetFlagStatus(UART3_FLAG_RXNE) == RESET);
    c = UART3_ReceiveData8();
    return (c);
}