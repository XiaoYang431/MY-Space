#ifndef __USART_H
#define __USART_H  
void uart_init(void);
void uart_send_number(uint32_t num, uint8_t len);
uint32_t uart_pow(uint32_t x, uint32_t y);
void uart_send_string(char *str);
void uart_send_array(uint8_t *arr, uint16_t len);
void uart_send_byte(uint8_t byte);
#endif
