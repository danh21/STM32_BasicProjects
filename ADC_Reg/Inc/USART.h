/*
 * USART.h
 *
 *  Created on: Mar 6, 2024
 *      Author: danh21
 */

#ifndef USART_H_
#define USART_H_



#define f_PCLK 16000000
#define baudrate 9600



/* Initializing USART */
void USART1_init()
{
	uint32_t USART_DIV, DIV_Mantissa, DIV_Fraction;

	RCC->APB2ENR |= (1<<4); 					// USART1 clock enable

	USART1->CR1 |= (1<<3); 						// transmit enable
	USART1->CR1 |= (1<<13);						// USART enable
	USART1->CR1 &= ~(1<<12);					// 1 Start bit, 8 Data bits, n Stop bit
	USART1->CR1 &= ~(1<<10);					// no parity
	USART1->CR2 &= ~(2<<12);					// 1 stop bit

	/*
	 * USART_DIV = PCLK1 / (baud * 16)
	 * 			 = 16,000,000 / (9600 * 16)
	 * 			 = 104.16667
	 * */
	USART_DIV = f_PCLK / (baudrate * 16);
	DIV_Mantissa = USART_DIV;
	DIV_Fraction = (USART_DIV - DIV_Mantissa) * 16;
	USART1->BRR |= (DIV_Mantissa<<4) | (DIV_Fraction);
}



/* transmit sequence data */
void USART1_sendData(char *p)
{
	while (*p != '\0')
	{
		USART1->DR = *p;						// load data
		while ((USART1->SR & (1<<6)) == 0);		// wait until Transmission is complete
		p++;
	}
}



#endif /* USART_H_ */
