#include "common.h"

LEDdata cascadeData[5];

int main(void) {
  uint8_t key, prevkey = 100, i;
  SPI_Init();
  SW_Init();
  UART_Init();
  TIM0_Init();

  // Initialize MAX7219 matrix
  for (i = 0; i < 5; i++) {
    SPI_rowTx(0x0c, 0x01);
    SPI_rowTx(0x09, 0x00);
    SPI_rowTx(0x0a, 0x02);
    SPI_rowTx(0x0b, 0x07);
  }

  while (1) {
    // read switch
    KeySet();

    // send NoteOn signal & turn-on ambient light
    for (i = 0; i < 40; i++) {
      if (btnPushed & ((uint64_t)1 << i)) {
        if (!(noteNowOn & (uint64_t)1 << i)) {
          attackKey(i);
          MIDI_NoteOn(i);
          noteNowOn |= ((uint64_t)1 << i);
        } else {
          sustainKey(i);
        }
      } else {
        if ((noteNowOn & (uint64_t)1 << i)) {
          MIDI_NoteOff(i);
          noteNowOn &= ~((uint64_t)1 << i);
        }
      }
    }

    // capture Visualizer height and print
    for (i = 0; i < 5; i++) {
      cascadeData[i] = capture((int)i * 8);
      Matrix_Transpose(cascadeData + i);
    }
    SPI_cascadeTx(cascadeData, 5);
  }
}
