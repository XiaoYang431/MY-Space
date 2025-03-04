#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h "

//写
void MySPI_W_SS(uint8_t BitValue)
{
GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)BitValue);
}

//1.开始写
void MYSPI_Start(void)
{
  MySPI_W_SS(0);      //把片选电位拉低 ，建立联系开始传输数据
}

//2.停止写
void MYSPI_Stop(void)
{
  MySPI_W_SS(1);      //把片选电位拉高 ，中断联系
}

//3.交换字节
//等待TXE = 1 → 写入发送的数据至TDR → 等待RXNE为1 → 读取RDR接收的数据 → 等待TXE为1……
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) != SET);     //等待TXE为1，为1表示发送寄存器空
  SPI_I2S_SendData(SPI2,ByteSend);                                //写入发送的数据至TDR
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) != SET);    //等待RXNE为1，为1表示接收寄存器非空
  return SPI_I2S_ReceiveData(SPI2) ;                              //读取RDR接收的数据
}


void MYSPI_Init(void)
{
//开启GPIO SPI时钟
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);

//配置GPIO SPI结构体 SPI输出  MOSI SCK
GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	
//SCK SS 复用推挽输出	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

//SPI输入：MISO脚用浮空/上拉输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

SPI_InitTypeDef SPI_InitStructure ;
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;     //配置SCK时钟频率，分频系数越大，越慢
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge  ;                          //配置时钟相位
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low  ;                            //配置时钟极性
SPI_InitStructure.SPI_CRCPolynomial = 0 ;                               // CRC校验
SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;                      // 8b / 16b 数据帧
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      // 单线半双工的接收/发送；双线全双工的发送/接收
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB ;                     // 高位先行/低位先行
SPI_InitStructure.SPI_Mode = SPI_Mode_Master ;                          // 主/从模式
SPI_InitStructure.SPI_NSS = SPI_NSS_Hard  ;                             // 硬件/软件NSS
SPI_Init(SPI2, &SPI_InitStructure);

//使能SPIx
SPI_Cmd(SPI2,ENABLE);

MySPI_W_SS(1); //默认高电平，不建立联系
}

