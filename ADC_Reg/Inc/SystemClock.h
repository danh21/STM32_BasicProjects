/*
 * SystemClock.h
 *
 *  Created on: Mar 3, 2024
 *      Author: danh21
 */

#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_



/*
 * Initialize system clock
 * */
void SystemClock_config()
{
	RCC->CR |= RCC_CR_HSION;				// enable HSI
	while (!(RCC->CR & RCC_CR_HSIRDY));		// see that HSI is ready or not

	// Power regulator
	PWR->CR |= (1<<15);

	// Flash latency setup
	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

	// Clock configuration register for setting
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while ( (RCC->CFGR & (1<<2)) || (RCC->CFGR & (1<<3)) );
}



#endif /* SYSTEMCLOCK_H_ */
