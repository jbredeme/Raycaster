# Author: Jarid Bredemeier
# Email: jpb64@nau.edu
# Date: Tuesday, September 20, 2016
# File: Makefile.mak

all: main.o json.o
	gcc main.o json.o -o output
	
main.o: main.c
	gcc -c main.c
	
json.o: json.c json.h
	gcc -c json.c
	
clean:
	rm *.o *.exe