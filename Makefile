# Author: Jarid Bredemeier
# Email: jpb64@nau.edu
# Date: Tuesday, September 20, 2016
# File: Makefile.mak
# Copyright © 2016 All rights reserved 

all: main.o json.o ppm6.o raycaster.o
	gcc main.o json.o ppm6.o raycaster.o -o raycaster
	
main.o: main.c
	gcc -c main.c
	
json.o: json\json.c json\json.h
	gcc -c json\json.c
	
ppm6.o: ppm\ppm6.c ppm\ppm6.h
	gcc -c ppm\ppm6.c

raycaster.o: raycaster\raycaster.c raycaster\raycaster.h
	gcc -c raycaster\raycaster.c	
	
clean:
	rm *.o *.exe