#include "common.h"

void SW_Init() {
  // 입력 포트 (Row)
  DDRD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) |
            (1 << PD7));
  DDRB &= ~((1 << PB7) | (1 << PB0));
  PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) |
           (1 << PD7); // 내부풀업저항있으면 이거 주석처리
  PORTB |= (1 << PB7) | (1 << PB0);

  // 출력 포트 (Column)
  DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4);
  PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4);
}

int KeySet(void) {
  volatile int KeyBuff = 99;
  volatile int col8;

  for (int col = 0; col < 5; col++) // Column loop (PC0 to PC4)
  {
    col8 = col * 8;
    // 활성화된 컬럼 핀만 LOW로 설정
    PORTC &= ~(1 << col);
    _delay_us(5); // 안정화 시간
    // Row 핀 확인 (PD2, PD3, PD4, PB7, PD5, PD6, PD7, PB0)
    if (!(PIND & (1 << PD2)))
      KeyBuff = col8 + 0;
    if (!(PIND & (1 << PD3)))
      KeyBuff = col8 + 1;
    if (!(PIND & (1 << PD4)))
      KeyBuff = col8 + 2;
    if (!(PINB & (1 << PB7)))
      KeyBuff = col8 + 3;
    if (!(PIND & (1 << PD5)))
      KeyBuff = col8 + 4;
    if (!(PIND & (1 << PD6)))
      KeyBuff = col8 + 5;
    if (!(PIND & (1 << PD7)))
      KeyBuff = col8 + 6;
    if (!(PINB & (1 << PB0)))
      KeyBuff = col8 + 7;

    // 다시 해당 컬럼 핀을 HIGH로 복원
    PORTC |= (1 << col);
  }

  return KeyBuff;
}