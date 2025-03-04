#ifndef __DELAY_H
#define __DELAY_H     

static __IO uint32_t TimingDelay; 

void Delay_Init(void);

void TimingDelay_Decrement(void);

#endif
