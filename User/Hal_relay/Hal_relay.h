#ifndef _HAL_RELAY_H_
#define _HAL_RELAY_H_
#include "stm32f10x.h"

/* 接口定义 */
#define GPIO_RELAY1_PORT   GPIOB       // use PB1 mux with led4, ardunio A4 port
#define GPIO_RELAY1_PIN    GPIO_Pin_1

typedef enum _relay_status
{
	kStatus_Relay_Low = 0,
	kStatus_Relay_High
}relay_stat_t;

void Relay_Init(void);
void Relay_PowerOnOff(uint16_t instance, uint16_t cmd);
void Relay_Deinit(void);

#endif
