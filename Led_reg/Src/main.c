#include<stdint.h>
#include<stm32f401xe.h>



#define led_on 		GPIOD->ODR |= 1<<13
#define led_off		GPIOD->ODR &= ~(1<<13)
#define led_is_off	(GPIOD->ODR & 1<<13) == 0

#define toggle_led 					led_is_off ? led_on : (led_off)
//#define button_is_pressed			(GPIOA->IDR & 1) == 1
//#define waiting_button_is_released 	while (button_is_pressed)



void SystemClock_config();
void GPIO_init();
void Timer_init();
void delay_ms(int ms);



int main()
{
	SystemClock_config();
	GPIO_init();
	Timer_init();

	while(1)
	{
		toggle_led;
		delay_ms(500);
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
	RCC->AHB1ENR |= (1<<3);		// IO port D clock enable

	GPIOD->MODER |= (1<<26);	// General purpose output mode
	GPIOD->MODER &= ~(1<<27);

	GPIOD->OTYPER &= ~(1<<13);	// Output push-pull (reset state)
}



void Timer_init()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; 		// TIM1 clock enable

	TIM1->PSC |= 15999;
	// F_timer = F_system / (PSC + 1) = 16,000,000 / 16,000 = 1KHz
	// => T_timer = 1ms

	TIM1->ARR = 65535;							// Auto-reload value

	TIM1->CR1 |= TIM_CR1_CEN;					// Counter enable
	TIM1->CR1 &= ~(1<<4);						// Counter used as up counter

	//	while (!(TIM1->SR & (1<<0)));			// reset
}



void delay_ms(int ms)
{
	TIM1->CNT = 0;
	while (TIM1->CNT < ms);
}
