/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx.h"

void OutputMCO() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Output clock on MCO pin ---------------------------------------------*/

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_MCO);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	// pick one of the clocks to spew

	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_4); // Put on MCO pin the: System clock selected
	RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_4); // Put on MCO pin the: System clock selected
//	RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1); // Put on MCO pin the: System clock selected
//	RCC_MCO1Config(RCC_MCO1Source_HSI, RCC_MCO1Div_1); // Put on MCO pin the: System clock selected
}



/* End of file */
