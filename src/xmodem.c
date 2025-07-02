#include "xmodem.h"
#include "serial.h"

#define XMODEM_START_OF_HEADER  0x01
#define XMODEM_END_TX           0x04
#define XMODEM_ACK              0x06
#define XMODEM_NACK             0x15
#define XMODEM_END_TX_BLOCK     0x17
#define XMODEM_CANCEL           0x18

// timeout duration in seconds
#define XMODEM_TIMEOUT          3

typedef struct {
    char data[0x80];
    unsigned int expected;
} XModemPacket;

int xmodem_recv(const char *destination, int maxsize) {
    XModemPacket packet;
    packet.expected = 1;

    // send NACK until we get START_OF_HEADER
    
}
