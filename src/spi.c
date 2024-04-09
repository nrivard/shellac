#include "spi.h"

void spi_init() {
    // mark CLK, MOSI, and CS as outputs
    *SPIDataDir |= (SPI_CLK | SPI_CS | SPI_MOSI);
    // mark MISO as input
    *SPIDataDir &= (SPI_MISO);

    // set up initial resting SPI state by setting pins high
    *SPIPort |= (SPI_CLK | SPI_CS | SPI_MOSI);
}

char spi_transfer(char byte) {
    char recvd = 0;
    char gpio = *SPIPort;

    for (int i = 0; i < 8; i++) {
        // set CLK low and MOSI low by default
        char newGPIO = (gpio & ~(SPI_CLK | SPI_MOSI));

        // mask highest bit. if set, send a 1
        if (byte & 0x80) {
            newGPIO |= (SPI_MOSI);
        }

        *SPIPort = newGPIO;

        // TODO: noops?
        *SPIPort ^= SPI_CLK;

        gpio = *SPIPort;

        if (gpio & SPI_MISO) {
            recvd |= 1;
        }

        byte <<= 1;
        recvd <<= 1;
    }

    return recvd;
}
