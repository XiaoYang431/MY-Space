#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h "
#include "ENCODER.H"
#include "PWM.H"
#include "OLED.H"
#include "USART.H"
#include "DELAY.H"
#include "MOTOR.H"

int16_t Encoder1_Speed,  Encoder2_Speed,  Encoder3_Speed,  Encoder4_Speed; //存放四个编码器速度
int16_t Motor1_Out,  Motor2_Out,  Motor3_Out,  Motor4_Out;


int main()
{
	  OLED_Init();
      Encoder1_Init();
      Encoder2_Init();
	  Encoder3_Init();
      Encoder4_Init();
	  PWM_Init();
	  InitMotor();
	  int8_t Speed = 50;
      
while(1)
  {   
	  Run_Straight(50);
	  Encoder1_Speed = Encoder1_Get();
	  Encoder2_Speed = Encoder2_Get();
	  Encoder3_Speed = Encoder3_Get();
	  Encoder4_Speed = Encoder4_Get();
	  OLED_ShowString(1, 1, "电机1速度:");
	  OLED_ShowNum(1, 7, Encoder1_Speed, 2);
	  OLED_ShowString(2, 1, "电机2速度:");
	  OLED_ShowNum(2, 7, Encoder2_Speed, 2);
	  OLED_ShowString(3, 1, "电机3速度:");
	  OLED_ShowNum(3, 7, Encoder3_Speed, 2);
	  OLED_ShowString(4, 1, "电机4速度:");
	  OLED_ShowNum(4, 7, Encoder4_Speed, 2);
  }
}
