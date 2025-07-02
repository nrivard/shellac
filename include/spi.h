#pragma once

#define SPI_PORT    0xE00001
volatile char *SPIPort = (char *)SPI_PORT;

#define SPI_DDR     0xE00005
volatile char *SPIDataDir = (char *)SPI_DDR;

// GPIO pin numbers on the MFP
#define SPI_CLK     (1<<6)
#define SPI_CS      (1<<5)
#define SPI_MISO    (1<<7)
#define SPI_MOSI    (1<<4)

// initialize pin direction and resting spi state
void spi_init(void);

// transfer one byte to and from device
char spi_transfer(char byte);

// convenience to read a byte
static inline char spi_read(void) {
    spi_transfer(0xFF);
}
