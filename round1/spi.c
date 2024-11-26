#include "common.h"

#define SPI_select_LED() PORTB &= ~(1 << SPI_SS_LED)
#define SPI_deselect_LED() PORTB |= (1 << SPI_SS_LED)

void SPI_Init(void) {
  // SPI 통신용 핀 출력 설정
  DDRB |= (1 << SPI_SS_LED | 1 << SPI_MOSI | 1 << SPI_SCK);

  // 초기 SS HIGH(disable)
  PORTB |= (1 << SPI_SS_LED);

  // 마스터 설정, 클럭 속도 설정
  SPCR |= (1 << SPE | 1 << MSTR | 1 << SPR1 | 1 << SPR0);
}

void SPI_byteTx(uint8_t byte) {
  // 바이트 전송 후 완료 시까지 대기
  SPDR = byte;
  while (!(SPSR & (1 << SPIF)))
    ;
}

void SPI_rowTx(uint8_t address, uint8_t data) {
  SPI_select_LED();    // LED 매트릭스 선택
  SPI_byteTx(address); // 주소 전송
  SPI_byteTx(data);    // 데이터 전송
  SPI_deselect_LED();  // LED 매트릭스 선택 해제
}

void SPI_cascadeTx(LEDdata *d, int n) {
  // 각 row별로 전송
  for (int r = 0; r < 8; r++) {
    SPI_select_LED(); // LED 매트릭스 선택

    // 해당 row의 데이터를 매트릭스 모듈마다 전송
    for (int i = n - 1; i >= 0; i--) {
      SPI_byteTx(r + 1);
      SPI_byteTx(d[i].vector[r]);
    }
    SPI_deselect_LED(); // LED 매트릭스 선택 해제
  }
  _delay_us(200);
}

void Matrix_Transpose(LEDdata *data) {
  uint8_t i, t;

  // 대각선 기준 대칭 성분이 서로 다를 경우에만 교환
  for (i = 0; i < 7; i++) {
    for (uint8_t c = i + 1; c < 8; c++) {
      t = (data->vector[i] & (1 << c)) ? 1 : 0;
      t |= ((data->vector[c] & (1 << i)) ? 2 : 0);

      switch (t) {
      case 1: // (i,c)=1 and (c,i)=0
        data->vector[i] &= ~(1 << c);
        data->vector[c] |= (1 << i);
        break;
      case 2: // (i,c)=0 and (c,i)=1
        data->vector[i] |= (1 << c);
        data->vector[c] &= ~(1 << i);
        break;
      }
    }
  }
}

// void SPI_colMatrixTx(LEDdata data) {
//   uint8_t row = 0;
//   for (int i = 7; i >= 0; i--) {
//     row = 0;
//     for (int j = 7; j >= 0; j--) {
//       row |= (data.vector[j] & (1 << i)) ? (1 << j) : 0;
//     }
//     SPI_rowTx(i + 1, row);
//   }
// }