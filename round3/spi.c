#include "common.h"

void SPI_Init(void) {
  // SPI 통신용 핀 출력 설정
  DDRB |= (1 << PB2 | 1 << SPI_MOSI | 1 << SPI_SCK);

  // SPI enable & set master mode
  SPCR |= (1 << SPE | 1 << MSTR);
  SPCR |= (1 << CPHA);

  // SPI Clock speed = 16M / 2 = 8MHz, T = 0.125us
  SPSR |= (1 << SPI2X);
  SPCR &= ~(1 << SPR1 | 1 << SPR0);
}

void SPI_byteTx(uint8_t byte) {
  // 바이트 전송 후 완료 시까지 대기
  SPDR = byte;
  while (!(SPSR & (1 << SPIF)))
    ;
}

void SPI_Amb_Tx(AMBData data) {
  uint8_t i, c, b, d;
  uint8_t bitbyte[8];

  // for each color byte g, r, b
  for (c = 0; c < 3; c++) {
    switch (c) {
    case 0:
      d = data.g;
      break;
    case 1:
      d = data.r;
      break;
    case 2:
      d = data.b;
      break;
    }

    // for each bit (MSB to LSB)
    for (b = 0; b < 8; b++) {
      if (d & (1 << b))
        bitbyte[b] = 0b00011;
      else
        bitbyte[b] = 0b11100;
      d <<= 1;
    }

    // transmit
    for (b = 0; b < 8; b++)
      SPI_byteTx(bitbyte[b]);
  }
  SPI_byteTx(0);

  // for(b=0;b<24;b++)
  // SPI_byteTx(0b11100);
  // uint8_t txbyte[10];

  // // for each byte
  // for (c = 0; c < 3; c++) { // 0=G 1=R 2=B
  //   // 데이터 초기화
  //   for (b = 0; b < 10; b++)
  //     txbyte[b] = 0;

  //   // 데이터 변환
  //   switch (c) {
  //   case 0:
  //     d = data.g;
  //     break;
  //   case 1:
  //     d = data.r;
  //     break;
  //   case 2:
  //     d = data.b;
  //     break;
  //   }
  //   for (b = 0; b < 8; b += 4) {
  //     // bit 7, 3
  //     if (d & (1 << (7 - b)))
  //       txbyte[b] |= 0b11111110;
  //     else
  //       txbyte[b] |= 0b11100000;

  //     // bit 6, 2
  //     if (d & (1 << (6 - b)))
  //       txbyte[b + 1] |= 0b00111111, txbyte[b + 2] |= 0b10000000;
  //     else
  //       txbyte[b + 1] |= 0b00111000, txbyte[b + 2] |= 0b00000000;

  //     // bit 5, 1
  //     if (d & (1 << (5 - b)))
  //       txbyte[b + 2] |= 0b00001111, txbyte[b + 3] |= 0b11100000;
  //     else
  //       txbyte[b + 2] |= 0b00001110, txbyte[b + 3] |= 0b00000000;

  //     // bit 4, 0
  //     if (d & (1 << (4 - b)))
  //       txbyte[b + 3] |= 0b00000011, txbyte[b + 4] |= 0b11111000;
  //     else
  //       txbyte[b + 3] |= 0b00000011, txbyte[b + 4] |= 0b10000000;
  //   }

  //   // 데이터 전송
  //   for (b = 0; b < 10; b++)
  //     SPI_byteTx(txbyte[b]);
  // }
}