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
    // read switch and update visualizer
    key = KeySet();
    if (key != 99 && prevkey != key)
      attackKey(key), btnPushed |= ((uint64_t)1 << key);
    prevkey = key;

    // if there's note sustained 8 tick, send off signal
    for (i = 0; i < 40; i++) {
      if (noteToOff & ((uint64_t)1 << i))
        MIDI_NoteOff(i), noteToOff &= ~((uint64_t)1 << i);
    }

    // capture Visualizer height and print
    for (i = 0; i < 5; i++) {
      cascadeData[i] = capture((int)i * 8);
      Matrix_Transpose(cascadeData + i);
    }
    SPI_cascadeTx(cascadeData, 5);
  }
}
