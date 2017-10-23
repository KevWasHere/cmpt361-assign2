CFLAGS = -Wall -pedantic -std=c99 -D_POSIX_C_SOURCE=200809L

.PHONY: all clean

all: select

select: select.o
	$(CC) $(LDFLAGS) -o $@ $^
	
select.o: select.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) select