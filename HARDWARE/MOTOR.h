#ifndef __MOTOR_H
#define __MOTOR_H  
void InitMotor(void);
void MOTOR1_DIR(int16_t Speed);
void MOTOR2_DIR(int16_t Speed);
void MOTOR3_DIR(int16_t Speed);
void MOTOR4_DIR(int16_t Speed);
void Run_Straight(int8_t Speed);
void Run_Back(int8_t Speed);
void Run_Right(int8_t Speed);
void Run_Left(int8_t Speed);
void mecanum_calculate(float Vx, float Vy, float omega, uint16_t* V1, uint16_t* V2, uint16_t* V3, uint16_t* V4);
#endif
