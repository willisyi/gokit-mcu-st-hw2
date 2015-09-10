#include "hal_relay.h"
void Relay_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_RELAY1_PIN;
	GPIO_Init(GPIO_RELAY1_PORT, &GPIO_InitStructure);	
	
	Relay_PowerOnOff(0,kStatus_Relay_High);
}
void Relay_PowerOnOff(uint16_t instance, uint16_t cmd)
{
	if(instance == 0)
	{
		switch(cmd)
		{
			case kStatus_Relay_Low: GPIO_ResetBits(GPIO_RELAY1_PORT,GPIO_RELAY1_PIN);
						break;
			case kStatus_Relay_High:GPIO_SetBits(GPIO_RELAY1_PORT,GPIO_RELAY1_PIN);
						break;
			default:
						break;
		}		
  }
}
void Relay_Deinit()
{
	GPIO_DeInit(GPIO_RELAY1_PORT);
}
