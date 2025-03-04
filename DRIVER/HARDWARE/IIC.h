#ifndef __IIC_H
#define __IIC_H  
void IIC_MotorInit(void);
void MOTOR_WriteReg(uint8_t RegAddress,uint8_t Data);
uint8_t MOTOR_ReadReg(uint8_t RegAddress,uint8_t Data);
#endif