CC=g++
CFLAGS=-W -Wall -std=gnu++11 -O2 


abif: abif.o main.o
	$(CC) $(CFLAGS) -o abif main.o abif.o

abif.o: abif.h abif.cpp
	$(CC) $(CFLAGS) -o abif.o -c abif.cpp 

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp