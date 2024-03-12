/*
 * ADC.h
 *
 *  Created on: Mar 11, 2024
 *      Author: danh21
 */

#ifndef ADC_H_
#define ADC_H_



#define max_ADC1 4095;



void ADC1_Init()
{
	RCC->APB2ENR |= (1<<8);		// ADC1 clock enable

	//ADC->CCR|=()//bit 17 and 16 set to 0 for prescaler to 2
	//ADC->CCR for same register bit 0 to 4 reset means all adc independent
	//ADC->CR1|=//Bits RES are 00 to select resolution to 12 bit in 15 clocks

	ADC1->CR1 |= (1<<5);		// Enable interrupt mode for EOC

	//ADC1->CR2|=(1<<1);
	ADC1->CR2 |= (1<<0);		// adc enable respectively

	//ADC->SMPR1|=()//SMP18 or SMP16 set to 000 which means 3 sample cycles
	//ADC->DR data to read register
	//FOr monitoring purpose read only register
	//ADC->CSR:going to read bits (5->ADC1overrun), 4->ADC1RegularStartsuccess
	//ADC->CSR:read bit (1->End of conversion for ADC1)

//	ADC1->CR2 |= (1<<30);		// start conversion of regular channels only with ADON=1

	//ALIGN in ADC->CR2 is 0 means right aligned
	//ADC->CR2 bit number 2 is EOC and this has to be with overrun
	//detection enable

//	ADC->CCR |= 2<<16;  		 // PCLK2 divide by 6
	ADC->CCR |= (1<<23);		// Temperature sensor enable and V_refint channel enabled
//	ADC1->CR2 |= (1<<0);		// ADON=1

	//ADC->CCR&=~((1<<16)|(1<<17));//bit 16,17=0 means prescaler is 2 ;same as 48L
	//ADC-CDR can be also used instead of DR
	//while(!(ADC1->SR & (1<<1)));//wait till end of conversion

	ADC1->CR1 &= ~(3<<24);		// resolution 12-bit
}



void ADC1_Start_Polling()
{
	ADC1->CR2 &= ~(1<<10);		// The EOC bit is set at the end of each sequence of regular conversions. Overrun detection is enabled only if DMA=1
	ADC1->SMPR1 |= (4<<18);		// 84 clock cycle polling, 16th channel
	ADC1->CR2 |= (1<<30);		// start regular conversion
	while(!(ADC1->SR & (1<<4)));// wait until conversion starts
	//delay is by sampling time only not interrupt
	//sampling time may be adjusted by select 16th channel for temperature sensor
}



uint32_t ADC1_Read()
{
	uint32_t ADC_data;
	ADC_data = ADC1->DR;
	return ADC_data;
}



void ADC1_End()
{
	ADC1->CR2 |= (1<<10); 		//bit is set at the end of each regular conversion.
}



#endif /* ADC_H_ */
