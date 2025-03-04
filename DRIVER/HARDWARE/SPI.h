#ifndef __SPI_H
#define __SPI_H  
void MySPI_W_SS(uint8_t BitValue);
void MYSPI_Init(void);
void MYSPI_Start(void);
void MYSPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif