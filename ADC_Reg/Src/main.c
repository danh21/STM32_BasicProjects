#include <stdint.h>
#include <stm32f401xe.h>
#include <stdio.h>
#include "SystemClock.h"
#include "Timer.h"
#include "USART.h"
#include "ADC.h"



#define Vref 5		// Volt

uint32_t ADC1_data;
float Voltage = 0;
char result[20];



void GPIO_init();



int main()
{
	SystemClock_config();
	GPIO_init();
	Timer1_init();
	USART1_init();
	ADC1_Init();

	while(1)
	{
		ADC1_Start_Polling();
		ADC1_data = ADC1_Read();
//		Voltage = ADC1_data * Vref / max_ADC1;
		sprintf(result, "ADC value = %d\r\n", ADC1_data);
		USART1_sendData(result);
		delay_ms(1000);
//		printf("The value of ADC is %d \n", ADC_data);
		//printf("the value of ADC is\n");
		//printf("the value of ADC is %f 'C \n",Degree);
	}
}



/* Initializing GPIO */
void GPIO_init(void)
{
	RCC->AHB1ENR |= (1<<0);				// IO port A clock enable

	GPIOA->MODER |= (2<<18) | (3<<2);	// alternate function for PA9, analog for PA1
	GPIOA->OSPEEDR |= (2<<18) | (2<<2);	// high speed for PA1, PA9
	GPIOA->AFR[1] |= (7<<4);			// USART mode for PA9
}
