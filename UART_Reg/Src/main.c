#include <stdint.h>
#include <stm32f401xe.h>
#include "SystemClock.h"
#include "Timer.h"
#include "USART.h"



void GPIO_init();



int main()
{
	SystemClock_config();
	GPIO_init();
	Timer1_init();
	USART1_init();

	while(1)
	{
		USART1_sendData("danh21\r\n");
		delay_ms(1000);
	}
}



/* Initializing GPIO */
void GPIO_init(void)
{
	RCC->AHB1ENR |= (1<<0);		// IO port A clock enable

	GPIOA->MODER |= (2<<18);	// alternate function for PA9

	GPIOA->OSPEEDR |= (2<<18);	// high speed for PA9

	GPIOA->AFR[1] |= (7<<4);	// USART mode for PA9
}
