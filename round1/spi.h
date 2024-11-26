#ifndef __SPI_H__
#define __SPI_H__

#define SPI_SS_LED PB2
#define SPI_MOSI PB3
#define SPI_MISO PB4
#define SPI_SCK PB5

void SPI_Init(void);
void SPI_byteTx(uint8_t byte);
void SPI_rowTx(uint8_t address, uint8_t data);
void SPI_cascadeTx(LEDdata *d, int n);
void Matrix_Transpose(LEDdata *data);
// void SPI_colMatrixTx(LEDdata data);

#endif