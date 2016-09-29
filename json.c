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
	int token = getc(fpointer);
	
	if((token == '\n') || (token == '\r') || (token == '\f')) {
		line_num = line_num + 1;
		
	} else if(token == EOF) {
		fprintf(stderr, "Error, line number %d; unexpected end-of-file.\n", line_num);
		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		
	}
	
	return token;
	
} 
 
 
/**
 * skip_whitespace
 *	Reads in a character from a specified stream and checks whether that character is
 *	a whitespace. If the character is a whitespace it advances the position indicator
 * 	for the stream until a non-whitespace character is found or until the position indicator 
 *	encounters an EOF.
 */
void skip_whitespace(FILE *fpointer) {
	int token = get_char(fpointer);
	
	while(isspace(token) != 0){
		token = get_char(fpointer);
		
	}
	
	ungetc(token, fpointer);
	
}

 
/**
 * get_string
 *	Reads in a stream of characters delimited by quotation marks. Validates against the existence
 *	of escape sequence codes, strings longer then 256 characters, and non-ascii characters.
 *
 */
char *get_string(FILE *fpointer){
	char buffer[256];
	int token, i = 0;
	// Read in character advance the stream position indicator
	token = get_char(fpointer);
	
	if(token != '"') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, '"');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	} else {
		// Read in character advance the stream position indicator
		token = get_char(fpointer);
		
		while(token != '"'){
			 // String exceeds the buffer size
			if(i > 256) {
				fprintf(stderr, "Error, line number %d; Strings with a length greater than 256 characters are not supported.\n", line_num);
				// Close file stream flush all buffers
				fclose(fpointer);
				exit(-1);	
				
			}
			// String contains escape sequence code(s)
			if(token == '\\') {
				fprintf(stderr, "Error, line number %d; Strings with escape character codes are not supported.\n", line_num);
				// Close file stream flush all buffers
				fclose(fpointer);
				exit(-1);
				
			}
			// String is not an ascii character
			if((token < 32) || (token > 126)) {
				fprintf(stderr, "Error, line number %d; Strings can contain ascii characters only.\n", line_num);
				// Close file stream flush all buffers
				fclose(fpointer);
				exit(-1);	
				
			}
			// Add character to the buffer
			buffer[i] = token;
			i = i + 1;
			
			// Read in character advance the stream position indicator
			token = get_char(fpointer);
			 
		}
	}
	 
	buffer[i] = 0;
	return strdup(buffer);	 
 }
 
 
/**
 * get_double
 *	Reads in a double precsion floating point number, if none are found throws error
 *  exits the program.
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
 *	Reads in an array with the format pattern [x, y, z] and parses into an array of	
 *  doubles. Returns a pointer to the new array to the function call.
 */
double *get_vector(FILE *fpointer){
	// Allocate memory for vector array of doubles
	double *vector = malloc(3 * sizeof(double));

	int token;
	
	token = get_char(fpointer);
	
	if(token != '[') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, '[');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}	
	skip_whitespace(fpointer);
	
	vector[0] = get_double(fpointer);
	
	skip_whitespace(fpointer);
	
	token = get_char(fpointer);
	
	if(token != ',') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ',');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}
	skip_whitespace(fpointer);
	
	vector[1] = get_double(fpointer);
	
	skip_whitespace(fpointer);
	
	token = get_char(fpointer);
	
	if(token != ',') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ',');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}
	skip_whitespace(fpointer);
	
	vector[2] = get_double(fpointer);
	
	skip_whitespace(fpointer);

	token = get_char(fpointer);
	
	if(token != ']') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ']');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	}		
	
	return vector;
 }


 /**
 * json_read_scene
 *	Reads in a scene of objects formatted using json. [... ] delimit a scene where {... }
 *  delimit objects within that scene. Ignores comments seperating objects with in a scene
 *  Accepts empty scenes, empty objects. Returns the number of objects read in from the scene
 *
 */ 
int json_read_scene(FILE *fpointer, Object objects[]) {
	int token;
	int index;
	char *name, *value;
	double *vector;
	
	index = 0;
	
	// Skip whitespace(s) read in the first character
	skip_whitespace(fpointer);
	// Read in a character and advance the stream position indicator
	token = get_char(fpointer);
	
	// Check to see of the first character is a brace denoting the start of a scene
	if(token != '[') {
		fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, '[');
		// Close file stream flush all buffers
		fclose(fpointer);		
		exit(-1);
		
	} else {
		// Check for an empty scene - no objects
		skip_whitespace(fpointer);
		// Read in a character and advance the stream position indicator
		token = get_char(fpointer);
		
		if(token != ']') {
			ungetc(token, fpointer);
			
		}
		// Loop through the scene until a closing brace is encountered
		while(token != ']') {
			skip_whitespace(fpointer);
		
			// Read in a character and advance the stream position indicator
			token = get_char(fpointer);
			
			// Determine if the character read in is a valid begining of an object
			if(token != '{') {
				fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, '{');
				// Close file stream flush all buffers
				fclose(fpointer);		
				exit(-1);
				
			} else {
				skip_whitespace(fpointer);
				// Read in a character advance the stream position indicator
				token = get_char(fpointer);	
				
				while(token != '}') {
					// If the next character is a '"' which means a string move indicator back one position then read in the string
					if(token == '"') {
						ungetc(token, fpointer);			

					}
					
					name = get_string(fpointer);
					
					if(strcmp(name, "type") == 0){
						skip_whitespace(fpointer);
						// Read in a character and advance the stream position indicator
						token = get_char(fpointer);
						
						if(token != ':') {
							fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ':');
							// Close file stream flush all buffers
							fclose(fpointer);		
							exit(-1);
							
						} else {
							skip_whitespace(fpointer);
							
							value = get_string(fpointer);
							objects[index].type = value;
							//printf("From json.c %s: %s - index %d\n", name, objects[index].type, index);
							//printf("%s : %s\n", name, value);
							
						}
			   
					} else if(strcmp(name, "width") == 0) {
						skip_whitespace(fpointer);
						
						token = get_char(fpointer);

						if(token != ':') {
							fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ':');
							// Close file stream flush all buffers
							fclose(fpointer);		
							exit(-1);
							
						} else {
							skip_whitespace(fpointer);
							objects[index].properties.camera.width = get_double(fpointer);
							//printf("From json.c %s: %lf\n", name, objects[index].properties.camera.width);
							//printf("%s : %lf\n", name, get_double(fpointer));
							
						}
						
					} else if(strcmp(name, "height") == 0) {
						skip_whitespace(fpointer);
						// Read in a character and advance the stream position indicator
						token = get_char(fpointer);

						if(token != ':') {
							fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ':');
							// Close file stream flush all buffers
							fclose(fpointer);		
							exit(-1);
							
						} else {
							skip_whitespace(fpointer);

							objects[index].properties.camera.height = get_double(fpointer);
							//printf("From json.c %s: %lf\n", name, objects[index].properties.camera.height);
							//printf("%s : %lf\n", name, get_double(fpointer));
							
						}
						
					} else if(strcmp(name, "radius") == 0) {
						skip_whitespace(fpointer);
						// Read in a character and advance the stream position indicator
						token = get_char(fpointer);

						if(token != ':') {
							fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ':');
							// Close file stream flush all buffers
							fclose(fpointer);		
							exit(-1);
							
						} else {
							skip_whitespace(fpointer);
							
							objects[index].properties.sphere.radius = get_double(fpointer);
							//printf("From json.c %s: %lf\n", name, objects[index].properties.sphere.radius);
							//printf("%s : %lf\n", name, get_double(fpointer));
							
						}
					
					} else if(strcmp(name, "color") == 0) {
						skip_whitespace(fpointer);
						// Read in a character and advance the stream position indicator
						token = get_char(fpointer);

						if(token != ':') {
							fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ':');
							// Close file stream flush all buffers
							fclose(fpointer);		
							exit(-1);
							
						} else {
							skip_whitespace(fpointer);
							
							vector = get_vector(fpointer);
							
							if(strcmp(objects[index].type, "sphere") == 0) {
								objects[index].properties.sphere.color[0] = vector[0];
								objects[index].properties.sphere.color[1] = vector[1];
								objects[index].properties.sphere.color[2] = vector[2];
								
								//printf("%s color: %lf %lf %lf\n", objects[index].type, objects[index].properties.sphere.color[0], objects[index].properties.sphere.color[1], objects[index].properties.sphere.color[2]);								
								
							} else if(strcmp(objects[index].type, "plane") == 0) {
								objects[index].properties.plane.color[0] = vector[0];
								objects[index].properties.plane.color[1] = vector[1];
								objects[index].properties.plane.color[2] = vector[2];
								
								//printf("%s color: %lf %lf %lf\n", objects[index].type, objects[index].properties.plane.color[0], objects[index].properties.plane.color[1], objects[index].properties.plane.color[2]);
								
							}
							//printf("%s : %lf %lf %lf\n", name,  vector[0], vector[1], vector[2]);
							
						}				
						
					} else if(strcmp(name, "position") == 0) {
						skip_whitespace(fpointer);
						// Read in a character and advance the stream position indicator
						token = get_char(fpointer);

						if(token != ':') {
							fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ':');
							// Close file stream flush all buffers
							fclose(fpointer);		
							exit(-1);
							
						} else {
							skip_whitespace(fpointer);
							
							vector = get_vector(fpointer);
							
							if(strcmp(objects[index].type, "sphere") == 0) {
								objects[index].properties.sphere.position[0] = vector[0];
								objects[index].properties.sphere.position[1] = vector[1];
								objects[index].properties.sphere.position[2] = vector[2];
								
								//printf("%s position: %lf %lf %lf\n", objects[index].type, objects[index].properties.sphere.position[0], objects[index].properties.sphere.position[1], objects[index].properties.sphere.position[2]);								
								
							} else if(strcmp(objects[index].type, "plane") == 0) {
								objects[index].properties.plane.position[0] = vector[0];
								objects[index].properties.plane.position[1] = vector[1];
								objects[index].properties.plane.position[2] = vector[2];
								
								//printf("%s position: %lf %lf %lf\n", objects[index].type, objects[index].properties.plane.position[0], objects[index].properties.plane.position[1], objects[index].properties.plane.position[2]);
								
							}	
							//printf("%s : %lf %lf %lf\n", name,  vector[0], vector[1], vector[2]);
							
						}				
						
					} else if(strcmp(name, "normal") == 0) {
						skip_whitespace(fpointer);
						// Read in a character and advance the stream position indicator
						token = get_char(fpointer);

						if(token != ':') {
							fprintf(stderr, "Error, line number %d; unexpected character '%c', expected character '%c'.\n", line_num, token, ':');
							// Close file stream flush all buffers
							fclose(fpointer);		
							exit(-1);
							
						} else {
							skip_whitespace(fpointer);
							
							vector = get_vector(fpointer);
							
							objects[index].properties.plane.normal[0] = vector[0];
							objects[index].properties.plane.normal[1] = vector[1];
							objects[index].properties.plane.normal[2] = vector[2];
								
							//printf("%s normal: %lf %lf %lf\n", objects[index].type, objects[index].properties.plane.normal[0], objects[index].properties.plane.normal[1], objects[index].properties.plane.normal[2]);	
							//printf("%s : %lf %lf %lf\n", name,  vector[0], vector[1], vector[2]);
							
						}	 
					   
					} else {
						fprintf(stderr, "Error, line number %d; invalid type '%s'.\n", name);
						// Close file stream flush all buffers
						fclose(fpointer);		
						exit(-1);				
					}
					
					skip_whitespace(fpointer);
					// Read in a character and advance the stream position indicator	
					token = get_char(fpointer);
					
					if(token == ',') {
						skip_whitespace(fpointer);
						// Read in a character and advance the stream position indicator
						token = get_char(fpointer);
						
					}
					
				}
				
			}
			
			skip_whitespace(fpointer);
			// Read in a character and advance the stream position indicator
			token = get_char(fpointer);
			
			if(token == '{') {
				ungetc(token, fpointer);
				
			}
			
			if(token == ',') {
				skip_whitespace(fpointer);
				// Read in a character and advance the stream position indicator
				token = get_char(fpointer);
				
				if(token == '{') {
					ungetc(token, fpointer);
					
				}				
				
			}			
			// Increment array index counter
			index = index + 1;
			
		} // End of while loop

	}
	// Return the total number of objects read-in from the scene
	return index;

}