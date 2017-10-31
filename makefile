CFLAGS=-std=c99 -Wall -pedantic -D_POSIX_C_SOURCE=201112L -D_GNU_SOURCE -D_DEFAULT_SOURCE

.PHONY: all clean

all: blackjack

select: select.o
	$(CC) $(LDFLAGS) -o $@ $^
	
select.o: select.c
	$(CC) $(CFLAGS) -c $<
	
blackjack: blackjack.o server.o
	$(CC) $(LDFLAGS) -o $@ $^

blackjack.o: blackjack.c
	$(CC) $(CFLAGS) -c $<
	
server.o: server.c server.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) select select.o blackjack blackjack.o server.o