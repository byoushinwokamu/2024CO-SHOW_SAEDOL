#include "common.h"

volatile AMBData whtkey[22] = {
    {25, 0, 0},  {25, 0, 0},  {25, 0, 0},  {25, 0, 0},  {25, 0, 0},
    {25, 25, 0}, {25, 25, 0}, {25, 25, 0}, {25, 25, 0}, {25, 25, 0},
    {0, 25, 0},  {0, 25, 0},  {0, 25, 0},  {0, 25, 0},  {0, 25, 0},
    {0, 25, 25}, {0, 25, 25}, {0, 25, 25}, {0, 25, 25}, {0, 25, 25},
    {0, 25, 25}, {0, 25, 25}};
volatile AMBData blkkey[22] = {
    {0, 25, 0},  {0, 25, 0},  {0, 25, 0},  {0, 25, 0},  {0, 25, 0},
    {0, 25, 25}, {0, 25, 25}, {0, 25, 25}, {0, 25, 25}, {0, 25, 25},
    {0, 0, 25},  {0, 0, 25},  {0, 0, 25},  {0, 0, 25},  {0, 0, 25},
    {25, 0, 25}, {25, 0, 25}, {25, 0, 25}, {25, 0, 25}, {25, 0, 25},
    {25, 0, 0},  {25, 0, 0},  {25, 0, 0},  {25, 0, 0},  {25, 0, 0},
    {25, 0, 0},  {25, 0, 0}};

void pressKey(uint8_t key) {
  enum { WHT, BLK } keycol;
  uint8_t keynum, i, p;
  AMBData *coldata;
  if (key == 40) // ignore sustain pedal
    return;

  // judge if black key or white key
  switch (key % 12) {
  case 0:
  case 2:
  case 4:
  case 5:
  case 7:
  case 9:
  case 11:
    keycol = WHT;
    keynum = (key % 12 + 1) / 2 + key / 12 * 7;
    coldata = whtkey;
    break;
  case 1:
  case 3:
  case 6:
  case 8:
  case 10:
    keycol = BLK;
    keynum = (key % 12) / 2 + key / 12 * 7;
    if (key < 20)
      keynum++;
    coldata = blkkey;
    break;
  }

  lightdata[keynum].r = coldata[keynum].r;
  lightdata[keynum].g = coldata[keynum].g;
  lightdata[keynum].b = coldata[keynum].b;

  if (keycol == BLK) {
    lightdata[keynum + 1].r = coldata[keynum].r;
    lightdata[keynum + 1].g = coldata[keynum].g;
    lightdata[keynum + 1].b = coldata[keynum].b;
  }

  // const float bright[] = {0, 1, 0.5, 0.3, 0.1, 0.05};
  // const float bright[] = {0, 0.5};
  // for (i = 1; i <= 1; i++) {
  //   p = keynum + i + (keycol == BLK ? 1 : 0);
  //   if (p >= 22)
  //     break;
  //   lightdata[p].r += coldata[p].r * bright[i];
  //   lightdata[p].g += coldata[p].g * bright[i];
  //   lightdata[p].b += coldata[p].b * bright[i];
  // }
  // for (i = 1; i <= 1; i++) {
  //   if (keynum < i)
  //     break;
  //   p = keynum - i;
  //   lightdata[p].r += coldata[p].r * bright[i];
  //   lightdata[p].g += coldata[p].g * bright[i];
  //   lightdata[p].b += coldata[p].b * bright[i];
  // }
}

void releaseKey(uint8_t key) {
  enum { WHT, BLK } keycol;
  uint8_t keynum, i, p;
  if (key == 40)
    return;
  switch (key % 12) {
  case 0:
  case 2:
  case 4:
  case 5:
  case 7:
  case 9:
  case 11:
    keycol = WHT;
    keynum = (key % 12 + 1) / 2 + key / 12 * 7;
    break;
  case 1:
  case 3:
  case 6:
  case 8:
  case 10:
    keycol = BLK;
    keynum = (key % 12) / 2 + key / 12 * 7;
    if (key < 20)
      keynum++;
    break;
  }

  lightdata[keynum].r = 0;
  lightdata[keynum].g = 0;
  lightdata[keynum].b = 0;

  if (keycol == BLK) {
    lightdata[keynum + 1].r = 0;
    lightdata[keynum + 1].g = 0;
    lightdata[keynum + 1].b = 0;
  };
}