#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h "

void PWM_Init(void)
{
	//开启GPIOA  GPIOB  TIM3时钟
    RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockLPModeCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//配置PA6 PA7  PB0 PB1作为四个输出PWM的引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//开启内部时钟模式
	TIM_InternalClockConfig(TIM3);
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;   //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;  //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; 
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//配置输出比较参数
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = ENABLE;
	TIM_OCInitStructure.TIM_Pulse = 0;

    //开启四个输出比较通道输出四路PWM信号
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //电机1
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //电机2
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //电机3
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //电机4
	
	TIM_Cmd(TIM3,ENABLE);
}

//通过人为修改CCR来控制第一路PWM占空比
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, Compare);    
}
//通过修改CCR来控制第二路PWM占空比
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);    
}
//通过修改CCR来控制第三路PWM占空比
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM3, Compare);    
}
//通过修改CCR来控制第四路PWM占空比
void PWM_SetCompare4(uint16_t Compare)
{
	TIM_SetCompare4(TIM3, Compare);    
}

