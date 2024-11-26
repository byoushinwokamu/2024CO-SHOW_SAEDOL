#include "common.h"

int tim0_cnt, tim0_st;

ISR(TIMER0_OVF_vect) {
  if (++tim0_cnt == 32) { // 0.5초마다 워치독 LED 토글
    tim0_cnt = 0;
    tim0_st = !tim0_st;
    if (tim0_st)
      WLED_PORT |= (1 << WLED_PIN);
    else
      WLED_PORT &= ~(1 << WLED_PIN);
  }
}

void TIM0_Init(void) {
  // Watchdog LED 출력 설정 후 끄기
  WLED_DDR |= (1 << WLED_PIN);
  WLED_PORT &= ~(1 << WLED_PIN);

  // Prescaler as 1024
  TCCR0B |= (1 << CS02) | (1 << CS00);

  // 인터럽트 허용
  TIMSK0 |= (1 << TOIE0);
  sei(); // 전역 허용
}
