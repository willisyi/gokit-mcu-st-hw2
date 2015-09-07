#include "delay.h"


static uint8_t  fac_us=0;																		//us延时倍乘数
static uint16_t fac_ms=0;																		//ms延时倍乘数

void Delay_Init(uint8_t SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SYSCLK/8; //硬件8分频,fac_us得出的值是要给下面的时钟函数用的  
	fac_ms =(u16)fac_us*1000; 	
}	

		    								   
void Delay_us(uint32_t nus)
{		
		uint32_t temp;  
		SysTick->LOAD = nus*fac_us;  //延时10us的话就是  10*9=90,装到load寄存器中  
		SysTick->VAL=0x00;//计数器清0,因为currrent字段被手动清零时,load将自动重装到VAL中  
		SysTick->CTRL = 0x01;//配置使异常生效,也就是计数器倒数到0时将发出异常通知  
		do  
		{  
			 temp = SysTick->CTRL;  //时间到了之后,该位将被硬件置1,但被查询后自动清0  
		}  
		while(temp & 0x01 && !(temp &(1<<16))); //查询  	
		SysTick->CTRL = 0x00;  //关闭计数器  
		SysTick->VAL = 0x00;   //清空val      																//清空计数器	 
}


void Delay_ms(uint16_t nms)
{	 		  	  
		uint32_t temp;  
		SysTick->LOAD = nms*fac_ms;  //延时10us的话就是  10*9=90,装到load寄存器中  
		SysTick->VAL=0x00;//计数器清0,因为currrent字段被手动清零时,load将自动重装到VAL中  
		SysTick->CTRL = 0x01;//配置使异常生效,也就是计数器倒数到0时将发出异常通知  
		do  
		{  
			 temp = SysTick->CTRL;  //时间到了之后,该位将被硬件置1,但被查询后自动清0  
		}  
		while(temp & 0x01 && !(temp &(1<<16))); //查询  
	
		SysTick->CTRL = 0x00;  //关闭计数器  
		SysTick->VAL = 0x00;   //清空val   	  	    
} 
void Delay_s(uint16_t sec)
{
	uint16_t i;
	for(i=0;i<10*sec;i++)
	{
		Delay_ms(100);
	}
}
