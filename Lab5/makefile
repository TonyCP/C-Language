lab5: list.h list.o lab5.o
	gcc -o lab5 list.o lab5.o

lab5.o: list.h lab5.c
	gcc -c lab5.c

list.o: list.h list.c
	gcc -c list.c

run:
	./lab5

clean:
	rm -f *.o lab5
