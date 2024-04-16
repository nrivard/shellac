CC=gcc
INCLUDE=./include
CFLAGS=-g -I $(INCLUDE)
OBJ=main.o shellac.o spi.o sdcard.o xmodem.o string.o serial.o ctype.o
DEP=
EXEC=shellac

%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
