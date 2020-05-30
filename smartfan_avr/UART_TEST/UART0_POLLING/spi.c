/*
 * spi.c
 */

#include "spi.h"

#if SPI_CONFIG_AS_MASTER        // defined in spi_config.h as 1
void spi_init()
{
	SPI_DDR = (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS); 
#if 1
	SPI_DDR &= ~(1 << SPI_MISO);   // MISO핀을 입력으로 설정
#endif 
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//prescaler 16  SPE: SPI활성화 MSTR: 마스터모드 
    //  SPCR = 0x00; 
}


uint8_t spi_transmit(uint8_t data)
{
	SPDR = data;
//UART0_printf_string("spi_transmit SPDR start \r\n");
	while(!(SPSR & (1<<SPIF)));
//UART0_printf_string("spi_transmit SPDR end!!! \r\n");	
	return SPDR;
}

#else
void spi_init()
{
	SPI_DDR = (1<<SPI_MISO);
	SPCR = (1<<SPE);
}

uint8_t spi_transmit(uint8_t data)
{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
#endif
