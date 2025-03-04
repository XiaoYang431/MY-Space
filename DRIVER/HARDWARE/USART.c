#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h "
#include <stdio.h>

//发送数据：单个字节
void uart_send_byte(uint8_t byte)
{
	USART_SendData(USART1, byte);
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

//发送数组
void uart_send_array(uint8_t *arr, uint16_t len)
{
	uint16_t i;
	for (i = 0; i < len; i++)
	{
		uart_send_byte(arr[i]);
	}
}

//发送字符串
void uart_send_string(char *str)
{
	uint16_t i = 0;
	
	while(*(str + i) != '\0')
	{
		uart_send_byte(str[i]);
		i++;
	}
}

//x的y次方
uint32_t uart_pow(uint32_t x, uint32_t y)
{
	uint32_t result = 1;
	
	while(y)
	{
		result *= x;
		y--;
	}
	
	return result;
}


int fputc(int ch, FILE *fp)
{
	uart_send_byte(ch);
	
	return ch;
}



//发送数字
void uart_send_number(uint32_t num, uint8_t len)
{
	uint8_t i;
	for (i = 0; i < len; i++)
	{
		uart_send_byte(num / uart_pow(10, len - i - 1) % 10 + '0');
	}
	
}



void uart_init(void)
{
//1.初始化两个结构体
	GPIO_InitTypeDef GPIO_InitStruct; 
	USART_InitTypeDef USART_InitStruct;
	
//2.打开USART GPIO的时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

//3.通过结构体初始化GPIO和USART
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF ;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  //复用推挽输出，具体什么模式需要根据传输模式查表得到
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx |USART_Mode_Rx;   
	USART_InitStruct.USART_Parity = USART_Parity_No;   
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);  
	
	USART_Cmd(USART1, ENABLE);
}
