#ifndef __TIMER_H__
#define __TIMER_H__

#define WLED_DDR DDRD
#define WLED_PORT PORTD
#define WLED_PIN PD0

ISR(TIMER0_OVF_vect);
void TIM0_Init(void);

#endif