#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1)
		{
			KeyNum = 1;
		}
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 1)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 1)
		{
			KeyNum = 2;
		}
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 1)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 1)
		{
			KeyNum = 3;
		}
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 1)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 1)
		{
			KeyNum = 4;
		}
	}
	return KeyNum;
}
