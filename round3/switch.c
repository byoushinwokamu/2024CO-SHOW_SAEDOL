#include "common.h"

#define COLUMN_PIN (1 << PC0 | 1 << PC1 | 1 << PC2 | 1 << PC3 | 1 << PC4)

void SW_Init() {
  // 입력 포트 (Row)
  DDRD &= ~(1 << PD2 | 1 << PD3 | 1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7);
  DDRB &= ~(1 << PB7 | 1 << PB0);
  DDRC &= ~(1 << PC5); // Sustain pedal

  PORTD |= (1 << PD2 | 1 << PD3 | 1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7);
  PORTB |= (1 << PB7) | (1 << PB0);
  PORTC |= (1 << PC5);

  // 출력 포트 (Column)
  DDRC |= COLUMN_PIN;
  PORTC &= ~COLUMN_PIN; // 모두 LOW로 설정
}

void KeySet(void) {
  volatile int col8;

  for (int col = 0; col < 5; col++) { // Column loop (PC0 to PC4)
    col8 = col * 8;

    // 활성화된 컬럼 핀만 LOW 출력, 나머지 컬럼은 HIGH-Z
    DDRC &= ~COLUMN_PIN;
    DDRC |= (1 << col);
    _delay_us(5); // 안정화 시간

    // Row 핀 확인 (PD2, PD3, PD4, PB7, PD5, PD6, PD7, PB0)
    // 확인해서 눌려있으면 btnPushed의 해당 비트를 Set, 안 눌려있으면 Clear
    (!(PIND & 1 << PD2)) ? (btnPushed |= (uint64_t)1 << (col8 + 0))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 0)));
    (!(PIND & 1 << PD3)) ? (btnPushed |= (uint64_t)1 << (col8 + 1))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 1)));
    (!(PIND & 1 << PD4)) ? (btnPushed |= (uint64_t)1 << (col8 + 2))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 2)));
    (!(PINB & 1 << PB7)) ? (btnPushed |= (uint64_t)1 << (col8 + 3))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 3)));
    (!(PIND & 1 << PD5)) ? (btnPushed |= (uint64_t)1 << (col8 + 4))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 4)));
    (!(PIND & 1 << PD6)) ? (btnPushed |= (uint64_t)1 << (col8 + 5))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 5)));
    (!(PIND & 1 << PD7)) ? (btnPushed |= (uint64_t)1 << (col8 + 6))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 6)));
    (!(PINB & 1 << PB0)) ? (btnPushed |= (uint64_t)1 << (col8 + 7))
                         : (btnPushed &= ~((uint64_t)1 << (col8 + 7)));
  }
  // check sustain pedal
  (!(PINC & 1 << PC5)) ? (btnPushed |= (uint64_t)1 << 40)
                       : (btnPushed &= ~((uint64_t)1 << 40));
}