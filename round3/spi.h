#ifndef __SPI_H__
#define __SPI_H__

#define SPI_MOSI PB3
#define SPI_MISO PB4
#define SPI_SCK PB5

void SPI_Init(void);
void SPI_byteTx(uint8_t byte);
void SPI_Amb_Tx(AMBData data);

#endif