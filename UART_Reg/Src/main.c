#include <stdint.h>
#include <stm32f401xe.h>



#define f_PCLK 16000000
#define baudrate 9600



void SystemClock_config();
void GPIO_init();
void Timer1_init();
void USART1_init();
void USART1_sendData(char *p);
void delay_ms(int ms);



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



void GPIO_init(void)
{
	RCC->AHB1ENR |= (1<<0);		// IO port A clock enable

	GPIOA->MODER |= (2<<18);	// alternate function for PA9

	GPIOA->OSPEEDR |= (2<<18);	// high speed for PA9

	GPIOA->AFR[1] |= (7<<4);	// USART mode for PA9
}



void Timer1_init()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; 		// TIM1 clock enable

	TIM1->PSC |= 15999;
	// F_timer = F_system / (PSC + 1) = 16,000,000 / 16,000 = 1KHz
	// => T_timer = 1ms

	TIM1->ARR = 65535;							// Auto-reload value

	TIM1->CR1 |= TIM_CR1_CEN;					// Counter enable
	TIM1->CR1 &= ~(1<<4);						// Counter used as up counter
}



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



void USART1_sendData(char *p)
{
	while (*p != '\0')
	{
		USART1->DR = *p;						// load data
		while ((USART1->SR & (1<<6)) == 0);		// wait until Transmission is complete
		p++;
	}
}



void delay_ms(int ms)
{
	TIM1->CNT = 0;
	while (TIM1->CNT < ms);
}