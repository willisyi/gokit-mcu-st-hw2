#include "delay.h"


static uint8_t  fac_us=0;																		//us��ʱ������
static uint16_t fac_ms=0;																		//ms��ʱ������

void Delay_Init(uint8_t SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8; //Ӳ��8��Ƶ,fac_us�ó���ֵ��Ҫ�������ʱ�Ӻ����õ�  
	fac_ms =(u16)fac_us*1000; 	
}	

		    								   
void Delay_us(uint32_t nus)
{		
		uint32_t temp;  
		SysTick->LOAD = nus*fac_us;  //��ʱ10us�Ļ�����  10*9=90,װ��load�Ĵ�����  
		SysTick->VAL=0x00;//��������0,��Ϊcurrrent�ֶα��ֶ�����ʱ,load���Զ���װ��VAL��  
		SysTick->CTRL = 0x01;//����ʹ�쳣��Ч,Ҳ���Ǽ�����������0ʱ�������쳣֪ͨ  
		do  
		{  
			 temp = SysTick->CTRL;  //ʱ�䵽��֮��,��λ����Ӳ����1,������ѯ���Զ���0  
		}  
		while(temp & 0x01 && !(temp &(1<<16))); //��ѯ  	
		SysTick->CTRL = 0x00;  //�رռ�����  
		SysTick->VAL = 0x00;   //���val      																//��ռ�����	 
}


void Delay_ms(uint16_t nms)
{	 		  	  
		uint32_t temp;  
		SysTick->LOAD = nms*fac_ms;  //��ʱ10us�Ļ�����  10*9=90,װ��load�Ĵ�����  
		SysTick->VAL=0x00;//��������0,��Ϊcurrrent�ֶα��ֶ�����ʱ,load���Զ���װ��VAL��  
		SysTick->CTRL = 0x01;//����ʹ�쳣��Ч,Ҳ���Ǽ�����������0ʱ�������쳣֪ͨ  
		do  
		{  
			 temp = SysTick->CTRL;  //ʱ�䵽��֮��,��λ����Ӳ����1,������ѯ���Զ���0  
		}  
		while(temp & 0x01 && !(temp &(1<<16))); //��ѯ  
	
		SysTick->CTRL = 0x00;  //�رռ�����  
		SysTick->VAL = 0x00;   //���val   	  	    
} 
void Delay_s(uint16_t sec)
{
	uint16_t i;
	for(i=0;i<10*sec;i++)
	{
		Delay_ms(100);
	}
}
