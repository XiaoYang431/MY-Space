#include "stm32f4xx.h"   
#include "stm32f4xx_conf.h "
#include "PWM.H"
#include <math.h>
#define WHEEL_RADIUS 0.04  //轮子半径
#define WHEEL_DISTANCE_X 0.125 //轮子中心到小车中心x轴的距离
#define WHEEL_DISTANCE_Y 0.0 //轮子中心到小车中心y轴的距离
int16_t PWM_MAX=7200; 
int16_t PWM_MIN=-7200;

void InitMotor(void)
{
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	
}


void MOTOR1_DIR(int16_t Speed)
{
	if(Speed>=0)  //正转
	{
	GPIO_SetBits(GPIOD,GPIO_Pin_0); //给INA1高电平
	GPIO_ResetBits(GPIOD,GPIO_Pin_1);
	PWM_SetCompare1(Speed);
	}
	else		  //反转
	{
	GPIO_SetBits(GPIOD,GPIO_Pin_1); //给INA2高电平
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
	PWM_SetCompare1(-Speed);
	}
	if(Speed>PWM_MAX||Speed<PWM_MIN)  //电机限速
	{
	Speed=PWM_MAX;
	}
	if(Speed<PWM_MIN||Speed>-PWM_MIN)
	{
	Speed=PWM_MIN;
	}
}

void MOTOR2_DIR(int16_t Speed)
{
	if(Speed>=0)  //正转
	{
	GPIO_SetBits(GPIOD,GPIO_Pin_3); //给INA1高电平
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);
	PWM_SetCompare2(Speed);
	}
	else		  //反转
	{
	GPIO_SetBits(GPIOD,GPIO_Pin_4); //给INA2高电平
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
	PWM_SetCompare2(-Speed);
	}
	if(Speed>PWM_MAX||Speed<PWM_MIN)  //电机限速
	{
	Speed=PWM_MAX;
	}
	if(Speed<PWM_MIN||Speed>-PWM_MIN)
	{
	Speed=PWM_MIN;
	}
}

void MOTOR3_DIR(int16_t Speed)
{
	if(Speed>=0)  //正转
	{
	GPIO_SetBits(GPIOG,GPIO_Pin_3); //给INA1高电平
	GPIO_ResetBits(GPIOG,GPIO_Pin_4);
	PWM_SetCompare3(Speed);
	}
	else		  //反转
	{
	GPIO_SetBits(GPIOG,GPIO_Pin_4); //给INA2高电平
	GPIO_ResetBits(GPIOG,GPIO_Pin_3);
	PWM_SetCompare3(-Speed);
	}
		if(Speed>PWM_MAX||Speed<PWM_MIN)  //电机限速
	{
	Speed=PWM_MAX;
	}
	if(Speed<PWM_MIN||Speed>-PWM_MIN)
	{
	Speed=PWM_MIN;
	}
}

void MOTOR4_DIR(int16_t Speed)
{
	if(Speed>=0)  //正转
	{
	GPIO_SetBits(GPIOG,GPIO_Pin_5); //给INA1高电平
	GPIO_ResetBits(GPIOG,GPIO_Pin_6);
	PWM_SetCompare4(Speed);
	}
	else		  //反转
	{
	GPIO_SetBits(GPIOG,GPIO_Pin_6); //给INA2高电平
	GPIO_ResetBits(GPIOG,GPIO_Pin_5);
	PWM_SetCompare4(-Speed);
	}
		if(Speed>PWM_MAX||Speed<PWM_MIN)  //电机限速
	{
	Speed=PWM_MAX;
	}
	if(Speed<PWM_MIN||Speed>-PWM_MIN)
	{
	Speed=PWM_MIN;
	}
}


void Run_Straight(int8_t Speed)
{
	if(Speed>=0)
	{
	  MOTOR1_DIR(Speed);
      MOTOR2_DIR(Speed);
      MOTOR3_DIR(Speed);
      MOTOR4_DIR(Speed);
	}
	else
	{
	  MOTOR1_DIR(-Speed);
      MOTOR2_DIR(-Speed);
      MOTOR3_DIR(-Speed);
      MOTOR4_DIR(-Speed);	
	
	}
}

void Run_Back(int8_t Speed)
{
	if(Speed>=0)
	{
      MOTOR1_DIR(-Speed);
      MOTOR2_DIR(-Speed);
      MOTOR3_DIR(-Speed);
      MOTOR4_DIR(-Speed);
	}
	else
	{
	  MOTOR1_DIR(Speed);
      MOTOR2_DIR(Speed);
      MOTOR3_DIR(Speed);
      MOTOR4_DIR(Speed);	
	
	}
}

void Run_Right(int8_t Speed)
{
	if(Speed>=0)
	{
      MOTOR1_DIR(-Speed);
      MOTOR2_DIR(Speed);
      MOTOR3_DIR(-Speed);
      MOTOR4_DIR(Speed);
	}
	else
	{
	  MOTOR1_DIR(Speed);
      MOTOR2_DIR(-Speed);
      MOTOR3_DIR(Speed);
      MOTOR4_DIR(-Speed);	
	}
}

void Run_Left(int8_t Speed)
{
	if(Speed>=0)
	{
      MOTOR1_DIR(Speed);
      MOTOR2_DIR(-Speed);
      MOTOR3_DIR(Speed);
      MOTOR4_DIR(-Speed);
    }
	else
	{
	  MOTOR1_DIR(-Speed);
      MOTOR2_DIR(Speed);
      MOTOR3_DIR(-Speed);
      MOTOR4_DIR(Speed);	
	}
}


void mecanum_calculate(float Vx, float Vy, float omega, uint16_t* V1, uint16_t* V2, uint16_t* V3, uint16_t* V4) 
{
    // 计算旋转分量
    float R = sqrtf(WHEEL_DISTANCE_X * WHEEL_DISTANCE_X + WHEEL_DISTANCE_Y * WHEEL_DISTANCE_Y);
    
    // 计算每个轮子的速度
    *V1 = Vx - Vy - omega * R;
    *V2 = Vx + Vy + omega * R;
    *V3 = Vx + Vy - omega * R;
    *V4 = Vx - Vy + omega * R;
	MOTOR1_DIR(*V1);
	MOTOR2_DIR(*V2);
	MOTOR3_DIR(*V3);
	MOTOR4_DIR(*V4);
}
