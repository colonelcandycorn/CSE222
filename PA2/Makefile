plate: hash.o list.o main.o
	gcc -o plate hash.o list.o main.o
hash.o: hash.c
	gcc -c hash.c
list.o: list.c
	gcc -c list.c
main.o: main.c
	gcc -c main.c
clean:
	rm -fr main.o hash.o list.o plate
