CC=gcc
CFLAGS=-Wall -g

SRC=main.c detector.c utils.c \
    modules/nx_detector.c \
    modules/return_detector.c \
    modules/register_modules.c

all:
	$(CC) $(CFLAGS) -o detector $(SRC)

clean:
	rm -f detector
