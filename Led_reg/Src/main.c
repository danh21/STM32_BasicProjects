#include<stdint.h>
#include<stm32f401xe.h>



#define led_on 	GPIOD->ODR |= (1<<13)
#define led_off	GPIOD->ODR &= ~(1<<13);



void GPIO_init(void);
void delay(int a);
void SystemClock_config();



int main()
{
	SystemClock_config();
	GPIO_init();

	while(1)
	{
		// use ODR
		led_on;
		delay(5000);
		led_off;
		delay(5000);

		// use BSRR
		/* GPIOD->BSRR |= (1<<13);
		delay(5000);
		GPIOD->BSRR |= (1<<29);
		delay(5000); */
	}
}



void SystemClock_config()
{
	RCC->AHB1ENR |= (1<<3);		// IO Port D clock enable
}



void GPIO_init(void)
{
	GPIOD->MODER |= (1<<26);	// output mode for PD13
//	GPIOD->OTYPER &= ~(1<<13);	// reset state
}



void delay(int a)
{
	int i, j;
	for (i = 0; i < a; i++)
		for (j = 0; j < 123; j++);
}
