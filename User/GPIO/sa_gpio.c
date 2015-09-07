/**
  ******************************************************************************
  * @file    sa_gpio.c
  * @author  sa
  * @version V0.1
  * @date    2013/10/15
  * @brief   sa_STM32���GPIOģ��Դ�ļ�
  *			 ��STM32�̼���V3.5����һ�η�װ
  *         
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "include.h"


/*******************************************************************************
  * @brief  GPIO��ʼ��
  * @param  GPIOx: ��ʼ����GPIO�˿� 					
  *			GPIOx		x:(A..G) 	��:GPIOA
  * @param  GPIO_Pin: ѡ������õ� GPIO �ܽţ�ʹ�ò�������|������һ��ѡ�ж���ܽ� 	
  *			GPIO_Pin_x	x:(0..15)	��:GPIO_Pin_1 | GPIO_Pin_2
  * @param	GPIO_Mode:ѡ���ʼ��ģʽ
  *			GPIO_Mode_AIN 			ģ������ 
  *			GPIO_Mode_IN_FLOATING 	�������� 
  *			GPIO_Mode_IPD 			�������� 
  *			GPIO_Mode_IPU 			�������� 
  *			GPIO_Mode_Out_OD 		��©��� 
  *			GPIO_Mode_Out_PP 		������� 
  *			GPIO_Mode_AF_OD 		���ÿ�©��� 
  *			GPIO_Mode_AF_PP 		�����������
  * @param  GPIO_Speed:��������ѡ�йܽŵ�����
  *			GPIO_Speed_10MHz 		���������� 10MHz 
  *			GPIO_Speed_2MHz 		���������� 2MHz 
  *			GPIO_Speed_50MHz 		���������� 50MHz  		
  * @retval None
*******************************************************************************/
void SA_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOSpeed_TypeDef GPIO_Speed)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	if (GPIOx == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if (GPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if (GPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if (GPIOx == GPIOD)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
	}    
	else if (GPIOx == GPIOE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	} 
	else if (GPIOx == GPIOF)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	}
	else
	{
		if (GPIOx == GPIOG)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		}
	}
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin;				
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode; 		 
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed;		 
	GPIO_Init(GPIOx, &GPIO_InitStructure);					 
}
 
