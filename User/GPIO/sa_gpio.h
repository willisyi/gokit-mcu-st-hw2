/**
  ******************************************************************************
  * @file    sa_gpio.h
  * @author  sa
  * @version V0.1
  * @date    2013/10/15
  * @brief   sa_STM32���GPIOģ��ͷ�ļ�
  *			 ��STM32�̼���V3.5����һ�η�װ
  *         
  ******************************************************************************
  * @stm32f10x_gpio.h �ӿ�����
  *	GPIO_DeInit 					������ GPIOx �Ĵ�������Ϊȱʡֵ 
  * GPIO_AFIODeInit 				�����ù��ܣ���ӳ���¼����ƺ� EXTI ���ã�����Ϊȱʡֵ 
  * GPIO_Init 						���� GPIO_InitStruct ��ָ���Ĳ�����ʼ������ GPIOx �Ĵ��� 
  * GPIO_StructInit 				�� GPIO_InitStruct �е�ÿһ��������ȱʡֵ���� 
  * GPIO_ReadInputDataBit 			��ȡָ���˿ڹܽŵ����� 
  * GPIO_ReadInputData 				��ȡָ���� GPIO �˿����� 
  * GPIO_ReadOutputDataBit 			��ȡָ���˿ڹܽŵ���� 
  * GPIO_ReadOutputData 			��ȡָ���� GPIO �˿���� 
  * GPIO_SetBits 					����ָ�������ݶ˿�λ 
  * GPIO_ResetBits 					���ָ�������ݶ˿�λ 
  * GPIO_WriteBit 					���û������ָ�������ݶ˿�λ 
  * GPIO_Write 						��ָ�� GPIO ���ݶ˿�д������ 
  * GPIO_PinLockConfig 				���� GPIO �ܽ����üĴ��� 
  * GPIO_EventOutputConfig 			ѡ�� GPIO �ܽ������¼���� 
  * GPIO_EventOutputCmd 			ʹ�ܻ���ʧ���¼���� 
  * GPIO_PinRemapConfig 			�ı�ָ���ܽŵ�ӳ�� 
  * GPIO_EXTILineConfig 			ѡ�� GPIO �ܽ������ⲿ�ж���· 
  ******************************************************************************
  */
#ifndef _SA_GPIO_H_
#define _SA_GPIO_H_

#include "stm32f10x.h"


void SA_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOSpeed_TypeDef GPIO_Speed);


#endif
