#include "visualizer.h"

#define KEYOFFSET 1

void attackKey(uint8_t key) {
  const int BW = 5;                        // Bandwidth? 변동 범위
  const int POWER[6] = {0, 5, 2, 1, 1, 1}; // 주변 변동량

  key += KEYOFFSET; // 왼쪽 빈 칸 보정

  // 누른 키는 최대 높이
  height[key] = 8;

  // 주변 키 높이 변화
  for (int i = 1; i <= BW; i++) {
    if (key + i < 40) {
      height[key + i] += POWER[i];
      if (height[key + i] > 8)
        height[key + i] = 8;
    }
    if (key - i >= 0) {
      height[key - i] += POWER[i];
      if (height[key - i] > 8)
        height[key - i] = 8;
    }
  }
}

void sustainKey(uint8_t key) { height[key + KEYOFFSET] = 8; }

LEDdata capture(int displaynum) {
  // 높이 데이터로부터 LEDdata 행렬을 생성
  LEDdata d;
  for (int i = 0; i < 8; i++) {
    // 해당 높이에서 1을 빼면 그 앞까지의 비트가 1로 채워짐
    d.vector[i] = ((uint16_t)1 << height[i + displaynum]) - 1;
  }
  return d;
}
