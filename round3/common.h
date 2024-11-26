#ifndef __COMMON_H__
#define __COMMON_H__

#define F_CPU 16000000L // MCU 동작 클럭 설정

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

typedef struct {
  uint8_t vector[8];
} LEDdata;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} AMBData;

volatile uint8_t sustain[40];
volatile AMBData lightdata[22];

volatile uint64_t noteNowOn; // 현재 소리를 내는 중인 버튼
volatile uint64_t btnPushed; // 현재 눌려 있는 버튼

#include "ambient.h"
#include "midi.h"
#include "spi.h"
#include "switch.h"
#include "timer.h"
#include "uart.h"

#endif