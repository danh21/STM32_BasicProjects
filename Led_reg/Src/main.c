#include<stdint.h>
#include<stm32f401xe.h>



#define led_on 		GPIOD->ODR |= 1<<13
#define led_off		GPIOD->ODR &= ~(1<<13)
#define led_is_off	(GPIOD->ODR & 1<<13) == 0

#define toggle_led 					led_is_off ? led_on : (led_off)
#define button_is_pressed			(GPIOA->IDR & 1) == 1
#define waiting_button_is_released 	while (button_is_pressed)



void GPIO_init(void);
void delay(int a);
void SystemClock_config();



int main()
{
	SystemClock_config();
	GPIO_init();

	while(1)
	{
		if (button_is_pressed) {
			waiting_button_is_released;
			toggle_led;
		}
	}
}



void SystemClock_config()
{
	RCC->AHB1ENR |= (1<<0) | (1<<3);		// IO Port A & D clock enable
}



void GPIO_init(void)
{
	GPIOD->MODER |= (1<<26);	// output mode for PD13
	GPIOA->MODER &= ~(3<<0);	// input mode for PA0
	GPIOA->PUPDR |= (1<<1);		// pull down
}



void delay(int a)
{
	int i, j;
	for (i = 0; i < a; i++)
		for (j = 0; j < 123; j++);
}
