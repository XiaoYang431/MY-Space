#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h "
 
//指定地址写  
void MOTOR_WriteReg(uint8_t RegAddress,uint8_t Data)
{
I2C_GenerateSTART(I2C1, ENABLE);
while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
I2C_Send7bitAddress(I2C1, RegAddress, I2C_Direction_Transmitter);	
while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
I2C_SendData(I2C1, RegAddress);
while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);	

I2C_SendData(I2C1, Data);
while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);	

I2C_GenerateSTOP(I2C1, ENABLE);	
}	

//指定MOTOR寄存器地址读
uint8_t MOTOR_ReadReg(uint8_t RegAddress,uint8_t Data)
{
I2C_GenerateSTART(I2C1, ENABLE);
while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
I2C_Send7bitAddress(I2C1, 0x34, I2C_Direction_Transmitter);	
while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED != SUCCESS)); 
	
I2C_SendData(I2C1,RegAddress);
while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);	

I2C_GenerateSTART(I2C1, ENABLE);
while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);	
	
I2C_Send7bitAddress(I2C1, 0x34, I2C_Direction_Receiver);
while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);	
	
I2C_AcknowledgeConfig(I2C1, DISABLE);
I2C_GenerateSTOP(I2C1, ENABLE);

while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
Data = I2C_ReceiveData(I2C1);

I2C_AcknowledgeConfig(I2C1, ENABLE);
return Data;
}

//初始化I2C1
void IIC_MotorInit(void)
{
 RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOB,ENABLE);
 RCC_APB1PeriphClockLPModeCmd(RCC_APB1Periph_I2C1,ENABLE);	
	
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
    I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 50000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = 0;
	I2C_Init(I2C1,&I2C_InitStruct);
	
	I2C_Cmd(I2C1,ENABLE);
	
//通过I2C配置MOTOR寄存器
	//MOTOR_WriteReg();
	//MOTOR_WriteReg();
}
















