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

// Line number for error checking purposes
int line_num;

/**
 * get_char
 *	Reads in a character from a specified stream, if a newline, carriage return, or linefeed 
 *	character is encountered we add 1 to our line counter (line_num). If an end-of-file is 
 *	encountered, prompt the user and throw and error and exit out of the program.
 */
int get_char(FILE *fpointer) {
	int c = getc(fpointer);
	
	if((c == '\n') || (c == '\r') || (c == '\f')) {
		line_num = line_num + 1;
		
	} else if(c == EOF) {
		fprintf(stderr, "Error, line number %d; unexpected end-of-file.\n", line_num);
		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		
	}
	
	return c;
	
} 
 
 
/**
 * skip_whitespace
 *	Reads in a character from a specified stream and checks whether that character is
 *	a whitespace. If the character is a whitespace it advances the position indicator
 * 	for the stream until a non-whitespace character is found or until the position indicator 
 *	encounters an EOF.
 */
void skip_whitespace(FILE *fpointer) {
	int c = get_char(fpointer);
	
	while(isspace(c) != 0){
		c = get_char(fpointer);
		
	}
	
	ungetc(c, fpointer);
	
}

 
/**
 * get_string
 *	Reads in a stream of characters delimited by quotation marks. Validates against the existence
 *	of escape sequence codes, strings longer then 256 characters, and non-ascii characters.
 *
 */
char *get_string(FILE *fpointer){
	char buffer[256];
	int c, i = 0;
	// Read in character advance the stream position indicator
	c = get_char(fpointer);
	
	if(c != '"') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, c, '"');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	} else {
		// Read in character advance the stream position indicator
		c = get_char(fpointer);
		
		while(c != '"'){
			 // String exceeds the buffer size
			if(i > 256) {
				fprintf(stderr, "Error, line number %d; Strings with a length greater than 256 characters are not supported.\n", line_num);
				// Close file stream flush all buffers
				fclose(fpointer);
				exit(-1);	
				
			}
			// String contains escape sequence code(s)
			if(c == '\\') {
				fprintf(stderr, "Error, line number %d; Strings with escape character codes are not supported.\n", line_num);
				// Close file stream flush all buffers
				fclose(fpointer);
				exit(-1);
				
			}
			// String is not an ascii character
			if((c < 32) || (c > 126)) {
				fprintf(stderr, "Error, line number %d; Strings can contain ascii characters only.\n", line_num);
				// Close file stream flush all buffers
				fclose(fpointer);
				exit(-1);	
				
			}
			// Add character to the buffer
			buffer[i] = c;
			i = i + 1;
			
			// Read in character advance the stream position indicator
			c = get_char(fpointer);
			 
		}
	}
	 
	buffer[i] = 0;
	return strdup(buffer);	 
 }
 
 
/**
 * get_double
 *	
 *
 */
double get_double(FILE *fpointer){
	 double dbl;
	 
	 if(fscanf(fpointer, "%lf", &dbl) == 0) {
		fprintf(stderr, "Error, line number %d; expected numeric value.\n", line_num);
		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);		
		
	 } else {
		 return dbl;
		 
	 }
	 
 }
 
 
/**
 * get_vector
 *	
 *
 */
double *get_vector(FILE *fpointer){
	double *vector = malloc(3 * sizeof(double));
	int c;
	
	c = get_char(fpointer);
	
	if(c != '[') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, c, '[');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}	
	skip_whitespace(fpointer);
	
	vector[0] = get_double(fpointer);
	
	skip_whitespace(fpointer);
	
	c = get_char(fpointer);
	
	if(c != ',') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, c, ',');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}
	skip_whitespace(fpointer);
	
	vector[1] = get_double(fpointer);
	
	skip_whitespace(fpointer);
	
	c = get_char(fpointer);
	
	if(c != ',') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, c, ',');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}
	skip_whitespace(fpointer);
	
	vector[2] = get_double(fpointer);
	
	skip_whitespace(fpointer);

	c = get_char(fpointer);
	
	if(c != ']') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, c, ']');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}		
	
	return vector;
 }


/**
 * read_object
 *	
 *
 */ 
 void read_object(FILE *fpointer) {
	char *name, *value;
	int c;
	
	// Read in a character advance the stream position indicator
	c = get_char(fpointer);
	
	// Determine if the character read in is a valid begining of an object
	if(c != '{') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, c, '{');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	} else {
		skip_whitespace(fpointer);
		// Read in a character advance the stream position indicator
		c = get_char(fpointer);	
		
		while(c != '}') {

			if(c == '"') {
				ungetc(c, fpointer);			
			}
			name = get_string(fpointer);
			printf("%s ", name);
			
			if(strcmp(name, "type") == 0){
				skip_whitespace(fpointer);
				c = get_char(fpointer);
				if(c != ':') {
					// throw error
				} else {
					skip_whitespace(fpointer);
					value = get_string(fpointer);
					printf("%s\n", value);
					skip_whitespace(fpointer);
					printf("%c", get_char(fpointer));
					skip_whitespace(fpointer);
					
				}
				
			} else if(strcmp(name, "width") == 0) {
				
			} else if(strcmp(name, "height") == 0) {
				
			} else if(strcmp(name, "color") == 0) {
				skip_whitespace(fpointer);
				c = get_char(fpointer);
				if(c != ':') {
					// Error
				} else {
					skip_whitespace(fpointer);
					get_vector(fpointer);
					printf("got vector!\n");
					skip_whitespace(fpointer);
					printf("%c", get_char(fpointer));
					skip_whitespace(fpointer);					
				}
				
			} else if(strcmp(name, "position") == 0) {
				
			} else if(strcmp(name, "radius") == 0) {
				
			} else if(strcmp(name, "normal") == 0) {
				
			} else {
				skip_whitespace(fpointer);
			}
				

			
			
			
			

			
			
			
			
			
			c = get_char(fpointer);
		}
		
	}

 }
 
 
/**
 * json_read
 *	
 *
 */ 
void json_read(FILE *fpointer) {
	//double *mydbl = get_double(fpointer);
	//printf("%f\n", get_double(fpointer));
	//double *mydbl = get_vector(fpointer);
	//printf("%lf\n", mydbl[0]);
	//printf("%lf\n", mydbl[1]);
	//printf("%lf\n", mydbl[2]);
	read_object(fpointer);

 }