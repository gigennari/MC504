CFLAGS = -std=c99 -Wall -g -pthread
LDFLAGS = -lm

.PHONY: all clean

all: prod_cons

prod_cons: prod_cons.c
	gcc $(CFLAGS) -c prod_cons.c $(LDFLAGS)
	gcc $(CFLAGS) -o prod_cons.out prod_cons.o $(LDFLAGS)

clean:
	rm -f prod_cons
	rm -f *.o
