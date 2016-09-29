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

Object objects[128];

int main(int argc, char *argv[]){
	FILE *fpointer;
	int num_objects;

	fpointer = fopen("test01_good.txt", "r");
		
	if(fpointer == NULL) {
		fprintf(stderr, "Error, could not open file.\n");
		// Close file stream flush all buffers
		fclose(fpointer);
		exit(-1);
		
	} else {
		num_objects = json_read_scene(fpointer, objects);
		
	}
	printf("Number of objects in the scene are: %d\n\n", num_objects);	
	
	
	
	printf("type call from main type: %s\n", objects[0].type);
	printf("type call from main width: %lf\n", objects[0].properties.camera.width);
	printf("type call from main height: %lf\n\n", objects[0].properties.camera.height);
	
	printf("type call from main type: %s\n", objects[1].type);
	printf("type call from main radius: %lf\n", objects[1].properties.sphere.radius);
	
	printf("type call from main color: %lf", objects[1].properties.sphere.color[0]);
	printf(" %lf", objects[1].properties.sphere.color[1]);
	printf(" %lf\n", objects[1].properties.sphere.color[2]);
	
	printf("type call from main position: %lf", objects[1].properties.sphere.position[0]);
	printf(" %lf", objects[1].properties.sphere.position[1]);
	printf(" %lf\n", objects[1].properties.sphere.position[2]);	



	return(0);
	
} 