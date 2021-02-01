CFLAGS=-std=c11 -g -static

pcc: pcc.c

test: pcc
	./test.sh

clean:
	rm -f pcc *.o *~ tmp*

.PHONY: test clean
