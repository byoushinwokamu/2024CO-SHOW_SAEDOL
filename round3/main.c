#include "common.h"

// TEAM SAEDOL
// 경북대학교 전자공학부 하드웨어 동아리 "빛돌"
// 김규리 남기웅 정재웅 최승헌

int main(void) {
  uint8_t i;
  SPI_Init();
  SW_Init();
  UART_Init();
  TIM0_Init();

  while (1) {
    // read switch
    KeySet();

    // send NoteOn signal & turn-on ambient light
    for (i = 0; i < 41; i++) {
      if (btnPushed & ((uint64_t)1 << i)) {    // button pushed
        if (!(noteNowOn & (uint64_t)1 << i)) { // note not playing
          MIDI_NoteOn(i);
          pressKey(i);
          noteNowOn |= ((uint64_t)1 << i);
        }
      } else {                                // button not pushed
        if ((noteNowOn & (uint64_t)1 << i)) { // note playing
          MIDI_NoteOff(i);
          releaseKey(i);
          noteNowOn &= ~((uint64_t)1 << i);
        }
      } // end if-else
    } // end for

    // transmit ambient light data
    for (i = 0; i < 22; i++)
      SPI_Amb_Tx(lightdata[i]);
  } // end while
}
