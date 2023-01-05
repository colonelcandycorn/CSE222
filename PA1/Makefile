build: main.o functions.o
	g++ -o main main.o functions.o
test: functions.o test.o
	g++ -o test test.o functions.o -l gtest -l gtest_main
main.o: main.c
	g++ -c main.c
functions.o: functions.c
	g++ -c functions.c
test.o: test.c
	g++ -c test.c
clean:
	rm -fr main.o functions.o test.o test main
