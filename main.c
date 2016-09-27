/**
 * Author: Jarid Bredemeier
 * Email: jpb64@nau.edu
 * Date: Tuesday, September 20, 2016
 * File: main.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "json.h"

/**
 * json_obj
 *
 *
 */
typedef struct json_obj {
	char *type;
	double radius;
	double width;
	double height;
	double *color_vector;
	double *position_vector;
	double *normal_vector;
	
} json_obj;



int main(int argc, char *argv[]){
	
	FILE *fpointer;
	json_obj *scene;
	
	scene = (json_obj *)malloc(128 * sizeof(json_obj));
	if(scene == NULL) {
		fprintf(stderr, "Error, memory allocation failed.\n");
		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);		
	}

	fpointer = fopen("test01_good.txt", "r");
	
	if(fpointer == NULL) {
		fprintf(stderr, "Error, could not open file.\n");
		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		
	} else {
		json_read_scene(fpointer);
		
	}
	
	return(0);
} 
