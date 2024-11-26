#ifndef UART_H_
#define UART_H_

void UART_Init(void);                   // UART 초기화
void UART_transmit(unsigned char data); // 1바이트 송신
void UART_printString(char *str);       // 문자열 송신
void UART_printInteger(int n);
void int_to_string(int n, char *buffer);

#endif /* UART_H_ */