/**
 * Author: Jarid Bredemeier
 * Email: jpb64@nau.edu
 * Date: Tuesday, September 20, 2016
 * File: json.c
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "json.h"

// Error checking purposes
int line_num;

/**
 * skip_whitespace
 *	Reads in a character from a specified stream and checks whether that character is
 *	a whitespace. If the character is a whitespace it advances the position indicator
 * 	for the stream until a nonwhitespace character is found or until the position indicator 
 *	encounters an EOF.
 */
void skip_whitespace(FILE *fpointer) {
	int c = getc(fpointer);
	
	while(isspace(c) != 0){
		c = getc(fpointer);
		
	}

	ungetc(c, fpointer);
	
}