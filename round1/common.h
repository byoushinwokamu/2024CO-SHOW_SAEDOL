#ifndef __COMMON_H__
#define __COMMON_H__

#define F_CPU 16000000L // MCU 동작 클럭 설정

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

typedef struct {
  uint8_t vector[8];
} LEDdata;

volatile uint8_t height[40];

#include "spi.h"
#include "switch.h"
#include "timer.h"
#include "uart.h"
#include "visualizer.h"

#endif