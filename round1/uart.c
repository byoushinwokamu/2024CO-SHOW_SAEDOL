#include "common.h"

void UART_Init(void) {
  UCSR0A |= (1 << U2X0);
  UBRR0H = 0x00;
  UBRR0L = 207;
  UCSR0C |= 0x06;
  UCSR0B |= (1 << TXEN0);
}

void UART_transmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) // 송신 준비 완료까지 대기
    ;
  UDR0 = data;
}

void UART_printString(char *str) {
  while (*str)               // 문자열의 끝(\0) 이전까지
    UART_transmit(*(str++)); // 한 글자씩 송신
}

void UART_printInteger(int n) {
  if (n == 0) {
    UART_transmit('0'); // 숫자가 0인 경우 바로 출력
    return;
  }

  char buffer[10]; // 최대 10자리 정수 처리 가능
  int i = 0;

  // 자릿수를 추출하여 버퍼에 저장 (역순)
  while (n > 0) {
    buffer[i++] = (n % 10) + '0';
    n /= 10;
  }

  // 저장된 자릿수를 정방향으로 송신
  for (int j = i - 1; j >= 0; j--) {
    UART_transmit(buffer[j]);
  }
}

void int_to_string(int n, char *buffer) {
  sprintf(buffer, "%04d", n);
  buffer[4] = '\0';
}