#-------------------------------------------------------------------------
  # Student's Name: Kevin Ho
  # CMPT 361 Assignment #2
  # makefile
  # Assignment 2 makefile
#-----------------------------------------------------------------------

CFLAGS=-std=c99 -Wall -pedantic -D_POSIX_C_SOURCE=201112L -D_GNU_SOURCE -D_DEFAULT_SOURCE

.PHONY: all clean

all: blackjack game
	
blackjack: blackjack.o server.o
	$(CC) $(LDFLAGS) -o $@ $^

blackjack.o: blackjack.c
	$(CC) $(CFLAGS) -c $<

server.o: server.c server.h
	$(CC) $(CFLAGS) -c $<

game: game.o
	$(CC) $(LDFLAGS) -o $@ $^

game.o: game.c game.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) blackjack blackjack.o server.o game game.o