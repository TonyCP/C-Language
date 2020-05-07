cipher: cipher.o
	gcc cipher.o -o cipher

cipher.o: cipher.c


run: cipher test


test: test1 test2


test1:
	./cipher 1 ADTON data.txt data.out

test2:
	./cipher 2 ADTON data.out data.bak

compare:
	diff -s data.txt data.bak

clean: 
	rm -f *.bak *.o *.out cipher
