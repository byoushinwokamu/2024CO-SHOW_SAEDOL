#include "common.h"

void debug_tog(void) {
  static int a = 0;
  if (a = !a)
    PORTD |= (1 << PD1);

  else
    PORTD &= ~(1 << PD1);
}

LEDdata cascadeData[5];

int main(void) {
  uint8_t key, prevkey = 100;
  SPI_Init();
  SW_Init();
  UART_Init();
  TIM0_Init();

  for (int i = 0; i < 5; i++) {
    SPI_rowTx(0x0c, 0x01);
    SPI_rowTx(0x09, 0x00);
    SPI_rowTx(0x0a, 0x02);
    SPI_rowTx(0x0b, 0x07);
  }

  // attackKey(37);
  // reduceHeight();
  // attackKey(1);
  // reduceHeight();
  // attackKey(4);
  // reduceHeight();
  // attackKey(8);
  // reduceHeight();
  // attackKey(14);
  // reduceHeight();
  // attackKey(28);
  // attackKey(21);

  while (1) {
    // read switch and update visualizer
    key = KeySet();
    UART_printInteger(key);
    UART_printString("\r\n");
    if (key != 99 && prevkey != key)
      attackKey(key);

    prevkey = key;
    // capture Visualizer height and print
    for (int i = 0; i < 5; i++) {
      cascadeData[i] = capture(i * 8);
      Matrix_Transpose(cascadeData + i);
    }
    SPI_cascadeTx(cascadeData, 5);
  }
}
