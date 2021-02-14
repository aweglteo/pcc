CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

pcc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJS): pcc.h


test: pcc
	./test.sh

clean:
	rm -f pcc *.o *~ tmp*

.PHONY: test clean
