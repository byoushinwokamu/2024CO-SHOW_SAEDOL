#include "common.h"

int tim0_cnt, tim0_cntx4, tim0_st;

ISR(TIMER0_OVF_vect) {
  // Watchdog LED를 토글
  if (++tim0_cnt == 4) {
    for (int i = 0; i < 40; i++)
      if (height[i] > 0)
        height[i]--;
    if (++tim0_cntx4 == 8) {
      tim0_cntx4 = 0;
      tim0_st = !tim0_st;
      if (tim0_st)
        WLED_PORT |= (1 << WLED_PIN);
      else
        WLED_PORT &= ~(1 << WLED_PIN);
    }
    tim0_cnt = 0;
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
  sei();
}
