#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h "

void Encoder1_Init(void)
{
//开启系统时钟
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//配置输出的GPIO口
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;    //TIM2的CH1 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;    //TIM2的CH2
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置TIM
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(65536-1);      //自动重装载计数器(ARR)
	TIM_TimeBaseInitStruct.TIM_Prescaler=(1 -1);   //预分频值(PSC)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct);

	//配置输入捕获
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);          //赋初值
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;   //选择通道 1
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;   //选择通道 2
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,
	               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //不反向
				   
	TIM_Cmd(TIM2,ENABLE);
}

void Encoder2_Init(void)
{
//开启系统时钟
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//配置输出的GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6 | GPIO_Pin_7;  //TIM4的CH1 CH2
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置TIM
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(65536-1);      //自动重装载计数器(ARR)
	TIM_TimeBaseInitStruct.TIM_Prescaler=(1 -1);   //预分频值(PSC)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseInitStruct);

	//配置输入捕获
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);          //赋初值
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;   //选择通道 1
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;   //选择通道 2
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInit(TIM4,&TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
	               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //不反向
				   
	TIM_Cmd(TIM4,ENABLE);
}


void Encoder3_Init(void)
{
//开启系统时钟
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//配置输出的GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1;  //TIM5的CH1 CH2
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//配置TIM
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(65536-1);      //自动重装载计数器(ARR)
	TIM_TimeBaseInitStruct.TIM_Prescaler=(1 -1);   //预分频值(PSC)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	
	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseInitStruct);

	//配置输入捕获
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);          //赋初值
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;   //选择通道 1
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;   //选择通道 2
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInit(TIM5,&TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,
	               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //不反向
				   
	TIM_Cmd(TIM5,ENABLE);
}


void Encoder4_Init(void)
{
//开启系统时钟
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//配置输出的GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14 | GPIO_Pin_15;  //TIM12的CH1 CH2
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置TIM
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(65536-1);      //自动重装载计数器(ARR)
	TIM_TimeBaseInitStruct.TIM_Prescaler=(1 -1);   //预分频值(PSC)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	
	TIM_TimeBaseInit( TIM12, &TIM_TimeBaseInitStruct);

	//配置输入捕获
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);          //赋初值
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;   //选择通道 1
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;   //选择通道 2
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInit(TIM12,&TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM12, TIM_EncoderMode_TI12,
	               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //不反向
				   
	TIM_Cmd(TIM12,ENABLE);
}


int16_t Encoder1_Get(void)
{
	int16_t temp;
	temp=TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2,0);
return temp;
}

int16_t Encoder2_Get(void)
{
	int16_t temp;
	temp=TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4,0);
return temp;
}

int16_t Encoder3_Get(void)
{
	int16_t temp;
	temp=TIM_GetCounter(TIM5);
	TIM_SetCounter(TIM5,0);
return temp;
}

int16_t Encoder4_Get(void)
{
	int16_t temp;
	temp=TIM_GetCounter(TIM12);
	TIM_SetCounter(TIM12,0);
return temp;
}