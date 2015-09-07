/**
  ******************************************************************************
  * @file    Hal_key.c
  * @author  jason
	* @Tel     18938045680
	* @QQ      570526723 
  * @version V2.0
  * @date    12/05/2014
  * @brief   1��רҵǶ��ʽ�����豸��������
						 2��רҵ�������߹�Ӧ�̣�http://wenjieteam.taobao.com/
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, jason SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2014 jason</center></h2>
  */ 
#include "include.h"

extern Pro_CommonCmdTypeDef         	 Pro_CommonCmdStruct;
extern Pro_CommonCmdTypeDef     		   Pro_M2WResetCmdStruct;    //MCU����WIFI����
extern Pro_D2W_ConfigWifiTypeDef       Pro_D2WConfigCmdStruct;   //MCU����WiFiģ��
extern Device_ReadTypeDef               Device_ReadStruct;
extern Device_WirteTypeDef   					  Device_WirteStruct;

extern uint8_t									     	 SN; 
uint8_t KeyCountTime;


/*******************************************************************************
* Function Name  : KEY_GPIO_Init
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void KEY_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_KEY1_CLK | GPIO_KEY2_CLK | GPIO_KEY3_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_PIN;
	GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_KEY2_PIN;
	GPIO_Init(GPIO_KEY2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_KEY3_PIN;
	GPIO_Init(GPIO_KEY3_PORT, &GPIO_InitStructure);		
}

/*******************************************************************************
* Function Name  : TIM3_Int_Init
* Description    : TIM3 initialization function
* Input          : arr ��װ��ֵ
									 psc Ԥ��Ƶ
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/

void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
 
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ��� 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx							 
}


/*******************************************************************************
* Function Name  : Get_Key
* Description    : Read the KEY state
* Input          : None
* Output         : None
* Return         : uint8_t KEY state
* Attention		 : None
*******************************************************************************/

uint8_t Get_Key(void) 
{
	uint8_t ReadKey;
	
	if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT,GPIO_KEY1_PIN))
	{
			ReadKey |= PRESS_KEY1;
	}	
	if(!GPIO_ReadInputDataBit(GPIO_KEY2_PORT,GPIO_KEY2_PIN))
	{
			ReadKey |= PRESS_KEY2;
	}
	if(!GPIO_ReadInputDataBit(GPIO_KEY3_PORT,GPIO_KEY3_PIN))
	{
			ReadKey |= PRESS_KEY3;
	}
  
		return ReadKey;
}


/*******************************************************************************
* Function Name  : ReadKeyValue
* Description    : Read the KEY value
* Input          : None
* Output         : None
* Return         : uint8_t KEY value
* Attention		 : None
*******************************************************************************/
uint8_t ReadKeyValue(void)
{
	static uint8_t Key_Check;
	static uint8_t Key_State;
	static uint16_t Key_LongCheck;
	static uint8_t Key_Prev    = 0;        							//��һ�ΰ���   
	
	uint8_t Key_press;
	uint8_t Key_return = 0;
	
	if(KeyCountTime >= 10)  //KeyCountTime 1MS+1  ��������10MS
	{
		KeyCountTime = 0;
		Key_Check = 1;
	}
	if(Key_Check == 1)
	{	
		Key_Check = 0;
		Key_press = Get_Key();
		switch (Key_State)
		{
			case 0:
				if(Key_press != 0)
				{
					Key_Prev = Key_press;
					Key_State = 1;
				}
					
				break;
			case 1:
				if(Key_press == Key_Prev) 
				{
					Key_State = 2;
					Key_return= Key_Prev | KEY_DOWN;
				}
			  else 																					//����̧��,�Ƕ���,����Ӧ���� 
				{
					Key_State = 0;
				}
				break;
			case 2:

				if(Key_press != Key_Prev)
				{					
					Key_State = 0;
					Key_LongCheck = 0;
					Key_return = Key_Prev | KEY_UP;
					return Key_return;				
				}

				if(Key_press == Key_Prev) 
				{
					Key_LongCheck++;
					if(Key_LongCheck >= 100)    //����2S
					{			
						Key_LongCheck = 0;
						Key_State = 3;
						Key_return= Key_press |  KEY_LONG;
						return Key_return;	
					}				
				}
				break;
				
				case 3:
				if(Key_press != Key_Prev)
				{
					Key_State = 0;
				}
				break;	
		}
	}
	
	return  NO_KEY;
}
/*******************************************************************************
* Function Name  : KEY_Handle
* Description    : Key processing function
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void KEY_Handle(void)
{
	uint8_t Key_return =0;
	
	Key_return = ReadKeyValue();
	
	if(Key_return & KEY_UP)
	{
		if(Key_return & PRESS_KEY1)
		{
			printf("KEY1 PRESS\r\n");
			LED_RGB_Control(0,0,10);
			Motor_status(0);
		}
		if(Key_return & PRESS_KEY2)
		{
			printf("KEY2 PRESS\r\n");
			LED_RGB_Control(0,10,0);
			Motor_status(10);
		}
		if(Key_return & PRESS_KEY3)
		{
			printf("KEY3 PRESS\r\n");
			LED_RGB_Control(10,0,00);
			DHT11_Read_Data(&Device_ReadStruct.Temperature, &Device_ReadStruct.Humidity);
			printf("Temperature =%d;Humidity = %d " ,Device_ReadStruct.Temperature,Device_ReadStruct.Humidity);

			Motor_status(5);
			
		}					
	}

	if(Key_return & KEY_LONG)
	{
		if(Key_return & PRESS_KEY1)
		{
			KEY_LongHandle(PRESS_KEY1);
			printf("KEY1 Long PRESS\r\n");
			printf("M2W RESET WIFI\r\n");
		}
		if(Key_return & PRESS_KEY2)
		{
			KEY_LongHandle(PRESS_KEY2);
			printf("KEY2 Long PRESS\r\n");
			printf("M2W  Config WIFI\r\n");
		}
		if(Key_return & PRESS_KEY3)
		{
			printf("KEY3 Long PRESS\r\n");
		}					
	}
}		
/*******************************************************************************
* Function Name  : KEY_LongHandle
* Description    : Key Long Press processing function
                   
* Input          : KeyAction :
														  RESS_KEY1 ->MCU To WIFI Send Reset command
                              PRESS_KEY2 ->MCU To WIFI Send Config command
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/	
void KEY_LongHandle(uint8_t KeyAction)
{
	if(KeyAction  == KEY1_Long_Action)
	{
		Device_WirteStruct.LED_R = 50;
		Device_WirteStruct.LED_G = 0;
		Device_WirteStruct.LED_B = 0;
		LED_RGB_Control(Device_WirteStruct.LED_R,Device_WirteStruct.LED_G,Device_WirteStruct.LED_B);
		
		Pro_M2WResetCmdStruct.Pro_HeadPart.SN = SN++;
		Pro_M2WResetCmdStruct.Sum = CheckSum((uint8_t *)&Pro_M2WResetCmdStruct, sizeof(Pro_M2WResetCmdStruct));
		Pro_UART_SendBuf((uint8_t *)&Pro_M2WResetCmdStruct,sizeof(Pro_M2WResetCmdStruct), 0);	

			
	}

	if(KeyAction  == KEY2_Long_Action)
	{
		Device_WirteStruct.LED_R = 0;
		Device_WirteStruct.LED_G = 0;
		Device_WirteStruct.LED_B = 50;
		LED_RGB_Control(Device_WirteStruct.LED_R,Device_WirteStruct.LED_G,Device_WirteStruct.LED_B);		
		
		Pro_D2WConfigCmdStruct.Pro_HeadPart.SN = SN++;
		Pro_D2WConfigCmdStruct.Config_Method = 0x02;
		Pro_D2WConfigCmdStruct.Sum = CheckSum((uint8_t *)&Pro_D2WConfigCmdStruct, sizeof(Pro_D2WConfigCmdStruct));
		Pro_UART_SendBuf((uint8_t *)&Pro_D2WConfigCmdStruct,sizeof(Pro_D2WConfigCmdStruct), 0);	


	}
	
}	





