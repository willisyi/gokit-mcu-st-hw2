#include "System_time.h"



static uint8_t  fac_us=0;//us��ʱ������
static uint16_t fac_ms=0;//ms��ʱ������

/*******************************************************************************
* Function Name  : SystemTime_Init
* Description    : ϵͳ��ѯʱ���ʼ������ʹ��UCosʱ���δ�ʱ��
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SystemTime_Init(uint8_t SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick->CTRL &= ~(1<<0);          //ʹ��Systick��ʱ��
	SysTick->LOAD  = SYSCLK /8;   //ϵͳʱ�ӵ�1/8;
	SysTick->VAL   = 0x00;   						 //��ռ�����
	SysTick->CTRL |= (1<<0);          //ʹ��Systick��ʱ��
	SystemTimeNVICConfig();
}

 void SystemTimeNVICConfig(void)
 {
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);	
 }