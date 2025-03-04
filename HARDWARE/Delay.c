#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h "

static uint8_t fac_us=0; // 计数器因子
void Delay_init(uint8_t SysCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 设置SysTick时钟源：HCLK/8
	fac_us=SysCLK/8; // 设置计数器因子
}

void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD=nus*fac_us-1; // 计数值加载
	SysTick->VAL=0x00; // 清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; // 开始计数
	do
	{
		temp=SysTick->CTRL; // 读取控制寄存器状态
	}while((temp&0x01)&&!(temp&(1<<16))); 
	// temp&0x01:定时器使能，!(temp&(1<<16)):定时器计数值不为0
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; // 关闭计数
	SysTick->VAL=0x00;// 清空计数器
}

/// @brief nms延时
/// @param nus 延时的ms数
void delay_ms(uint32_t nms)
{
	uint32_t repeat=nms/540;
	uint32_t remain=nms%540;
	while(repeat)
	{
		delay_us(540*1000); // 延时 540 ms
		repeat--;
	}
	if(remain)
	{
		delay_us(remain*1000); // 延时remain ms
	}
}
