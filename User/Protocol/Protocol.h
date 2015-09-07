#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdio.h>
#include <stm32f10x.h>


#define		PRO_VER																"00000004"
#define		P0_VER																"00000004"
#define		HARD_VER															"00000001"
#define		SOFT_VER															"00000001"
#define		PRODUCT_KEY														"6f3074fe43894547a4f1314bd7e3ae0b"


__packed	typedef struct	
{
	uint8_t    	KEY1;
	uint8_t     KEY2;
	uint8_t			KEY3;
}KEY_StatusTypeDef;


#define Max_UartBuf             256

//�豸����ͨ��
__packed	typedef struct	
{
	uint8_t							Package_Flag;    				 //�ж��Ƿ���յ�һ�������Ĵ������ݰ�         
	uint8_t							UART_Flag1;
	uint8_t							UART_Flag2;
	uint16_t 						UART_Count;								//���ڻ������������ݳ���	
	uint8_t						 	UART_Cmd_len;							//ָ���	
	uint8_t 						UART_Buf[Max_UartBuf]; 		//���ڻ�����
	uint8_t             Message_Buf[Max_UartBuf]; //������յ�ָ���Buf
	uint8_t             Message_Len;	            //������Ϣ����
	
}UART_HandleTypeDef;




//����Э��ָ���
typedef enum
{
  Pro_W2D_GetDeviceInfo_Cmd 					= 0x01,
  Pro_D2W__GetDeviceInfo_Ack_Cmd			= 0x02,
	
	Pro_W2D_P0_Cmd 											= 0x03,
  Pro_D2W_P0_Ack_Cmd									= 0x04,
	
	Pro_D2W_P0_Cmd 											= 0x05,
  Pro_W2D_P0_Ack_Cmd									= 0x06,
	
	Pro_W2D_Heartbeat_Cmd 							= 0x07,
  Pro_D2W_heartbeatAck_Cmd						= 0x08,
	
	Pro_D2W_ControlWifi_Config_Cmd 			= 0x09,
  Pro_W2D_ControlWifi_Config_Ack_Cmd	= 0x0A,
	
	Pro_D2W_ResetWifi_Cmd 							= 0x0B,
  Pro_W2D_ResetWifi_Ack_Cmd						= 0x0C,
	
	Pro_W2D_ReportWifiStatus_Cmd 				= 0x0D,
  Pro_D2W_ReportWifiStatus_Ack_Cmd		= 0x0E,
	
	Pro_D2W_ReportWifiReset_Cmd 				= 0x0F,
  Pro_W2D_ReportWifiReset_Ack_Cmd			= 0x10,
	
	Pro_W2D_ErrorPackage_Cmd 						= 0x11,
  Pro_D2W_ErrorPackage_Ack_Cmd				= 0x12,
	
}Pro_CmdTypeDef;


typedef enum
{
  SetLED_OnOff    = 0x01,
	SetLED_Color    = 0x02,
	SetLED_R       	= 0x04,   
	SetLED_G    		= 0x08,     
	SetLED_B  		 	= 0x10,     
	SetMotor			 	= 0x20,	
  
}Attr_FlagsTypeDef;

typedef enum
{
  LED_OnOff         = 0x00,
	LED_OnOn          = 0x01,
	LED_Costom        = 0x00,
	LED_Yellow    		= 0x02,     
	LED_Purple  		 	= 0x04,     
	LED_Pink			 	  = 0x06,	
  
}LED_ColorTypeDef;
/******************************************************
* ֻ���豸�б��Ժ�Ҫ���ֻ���豸����ӵ�����
********************************************************/
__packed	typedef struct	
{

	bool                Infrared;
	uint8_t             Temperature;
	uint8_t             Humidity;
	
	                 
}Device_ReadTypeDef;  



/******************************************************
*��д�豸�б��Ժ�Ҫ��ӿ�д�豸����ӵ�����
********************************************************/
__packed	typedef struct	
{
	uint8_t							LED_Cmd;
	uint8_t							LED_R;
	uint8_t							LED_G;  
	uint8_t							LED_B;
	uint16_t						Motor;
	
	
}Device_WirteTypeDef;


/******************************************************
*�豸���������ϵ���Ϣ
*******************************************************/
__packed	typedef struct	
{
	uint8_t							Alert;
	uint8_t							Fault;

	
}Device_RestsTypeDef;
/******************************************************
*���������豸�Ľṹ��
********************************************************/
__packed	typedef struct	
{
	Device_WirteTypeDef Device_Wirte;
	Device_ReadTypeDef Device_Read;
	Device_RestsTypeDef Device_Rests;
}Device_AllTypeDef;


#define Send_MaxTime   200    
#define Send_MaxNum    3

/******************************************************
* ACK �ظ�����
* SendTime 
********************************************************/
__packed	typedef struct	
{
	uint8_t			SendTime;
	uint8_t			SendNum;
	
}Pro_Wait_AckTypeDef;



/******************************************************
* Э��Ĺ��ò���
********************************************************/
__packed	typedef struct	
{
	uint8_t							Head[2];
	uint16_t						Len;
	uint8_t							Cmd;
	uint8_t							SN;
	uint8_t							Flags[2];
	
}Pro_HeadPartTypeDef;


/******************************************************
* 4.1  WiFiģ�������豸��Ϣ
********************************************************/
__packed	typedef struct	
{
	Pro_HeadPartTypeDef  		Pro_HeadPart;
	uint8_t									Pro_ver[8];
	uint8_t									P0_ver[8];
	uint8_t									Hard_ver[8];
	uint8_t									Soft_ver[8];
	uint8_t									Product_Key[32];
	uint16_t								Binable_Time;
	uint8_t									Sum;
	
}Pro_M2W_ReturnInfoTypeDef;

/*****************************************************
*       ͨ�����������ack�ȿ��Ը��ô�֡            *
******************************************************
* 4.2 	WiFiģ�����豸MCU������
* 4.4 	�豸MCU����WiFiģ�� 
* 4.6 	WiFiģ����������MCU
* 4.9 	Wifiģ��ظ�
* 4.10  �豸MCU�ظ�
******************************************************/
__packed	typedef struct	
{
	Pro_HeadPartTypeDef    	Pro_HeadPart;
	uint8_t							  	Sum;
}Pro_CommonCmdTypeDef;


/******************************************************
* �豸MCUͨ��WiFiģ���������ģʽ
********************************************************/
__packed	typedef struct	
{
	Pro_HeadPartTypeDef  		Pro_HeadPart;
	uint8_t                 Config_Method;
	uint8_t							  	Sum;
}Pro_D2W_ConfigWifiTypeDef; 


/*****************************************************
*WiFi����ģʽ�궨��
******************************************************/
#define 		Wifi_SoftAPMode       			(uint8_t)(1<<0)    //�Ƿ���SoftAP ģʽ��0:�رգ�1������
#define 		Wifi_StationMode      	    (uint8_t)(1<<1)    //�Ƿ���Stationģʽ��0:�رգ�1������
#define 		Wifi_ConfigMode       		  (uint8_t)(1<<2)    //�Ƿ�������ģʽ��0:�رգ�1������
#define 		Wifi_BindingMode     			  (uint8_t)(1<<3)  	 //�Ƿ�����ģʽ��0:�رգ�1������
#define     Wifi_ConnRouter             (uint8_t)(1<<4) 	 //WiFiģ���Ƿ�ɹ����ӵ�·������0:�رգ�1������
#define     Wifi_ConnClouds             (uint8_t)(1<<5)    //WiFiģ���Ƿ�ɹ����ӵ��ƶˣ�0:�رգ�1������
	


/*****************************************************
* 4.5 WiFiģ�����豸MCU֪ͨWiFiģ�鹤��״̬�ı仯
******************************************************/
__packed	typedef struct	
{
	Pro_HeadPartTypeDef    	Pro_HeadPart;
	uint16_t                 Wifi_Status;
	uint8_t							  	Sum;
}Pro_W2D_WifiStatusTypeDef;



/*****************************************************
* �Ƿ���Ϣ֪ͨö���б�
******************************************************/
typedef enum
{
  Error_AckSum = 0x01,      //У��ʹ���      
  Error_Cmd 	 = 0x02,			//�����ʶ��
	Error_Other  = 0x03,      //��������              
}Error_PacketsTypeDef;


/*****************************************************
* 4.7 �Ƿ���Ϣ֪ͨ
******************************************************/
__packed	typedef struct	
{
	Pro_HeadPartTypeDef  		Pro_HeadPart;
	Error_PacketsTypeDef		Error_Packets;
	uint8_t									Sum;
}Pro_ErrorCmdTypeDef;


/*****************************************************
* P0 command �б�
******************************************************/
typedef enum
{
	P0_W2D_Control_Devce_Action 		= 0x01,
  P0_W2D_ReadDevStatus_Action 		= 0x02,
	P0_D2W_ReadDevStatus_Action_ACK = 0x03,
	P0_D2W_ReportDevStatus_Action   = 0X04,
	
}P0_ActionTypeDef;


/******************************************************
* ��P0ָ��Ĺ�������
********************************************************/
__packed	typedef struct	
{
	Pro_HeadPartTypeDef  		Pro_HeadPart;
	P0_ActionTypeDef        Action;
}Pro_HeadPartP0CmdTypeDef;


/*****************************************************
* 4.8 WiFiģ���ȡ�豸�ĵ�ǰ״̬
****************************************************** 
*Wifi ģ�鷢��
******************************************************/
__packed	typedef struct	
{
	Pro_HeadPartP0CmdTypeDef 			Pro_HeadPartP0Cmd;
	uint8_t												Sum;
}Pro_W2D_ReadDevStatusTypeDef;



/****************************************************** 
*�豸MCU �ظ� 
*�豸MCU�ϱ���ǰ��״̬
*******************************************************
*4.9 �豸MCU��WiFiZ�����ϱ���ǰ״̬ 
******************************************************/
__packed	typedef struct	
{
	Pro_HeadPartP0CmdTypeDef 			Pro_HeadPartP0Cmd;
	Device_AllTypeDef       			Device_All;
	uint8_t												Sum;
}Pro_D2W_ReportDevStatusTypeDef;





/*****************************************************
* 4. 10 WiFiģ������豸
****************************************************** 
* WiFiģ�鷢��
******************************************************/
__packed	typedef struct	
{
	
	Pro_HeadPartP0CmdTypeDef 			Pro_HeadPartP0Cmd;
	Attr_FlagsTypeDef             Attr_Flags;
	Device_WirteTypeDef     			Device_Wirte;
	uint8_t							  				Sum;	
}Pro_P0_ControlTypeDef; 






void MessageHandle(void);
void Pro_W2D_GetMcuInfo(void);
void Pro_W2D_CommonCmdHandle(void);
void Pro_W2D_WifiStatusHandle(void);
void Pr0_W2D_RequestResetDeviceHandle(void);
void Pro_W2D_ErrorCmdHandle(void);
void Pro_W2D_P0CmdHandle(void);
void Pro_W2D_Control_DevceHandle(void);
void Pro_W2D_ReadDevStatusHandle(void);

void Pro_D2W_ReportDevStatusHandle(void);

void Pro_UART_SendBuf(uint8_t *Buf, uint16_t PackLen, uint8_t Tag);
void Log_UART_SendBuf(uint8_t *Buf, uint16_t PackLen);
short	exchangeBytes(short	value);
uint8_t CheckSum( uint8_t *buf, int packLen );



#endif /*_PROTOCOL_H*/



