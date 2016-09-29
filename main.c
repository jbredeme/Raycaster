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
	
	// Check json read in
	int i;
	
	for(i = 0; i < num_objects; i++) {
		if(strcmp(objects[i].type, "camera") == 0){
			printf("Type: %s\n", objects[i].type);
			printf("Width: %lf\n", objects[i].properties.camera.width);
			printf("Height: %lf\n\n", objects[i].properties.camera.height);
		}
		
		if(strcmp(objects[i].type, "sphere") == 0){
			printf("Type: %s\n", objects[i].type);
			printf("Radius: %lf\n", objects[i].properties.sphere.radius);
			printf("Color: %lf %lf %lf\n", objects[i].properties.sphere.color[0], objects[i].properties.sphere.color[1], objects[i].properties.sphere.color[2]);
			printf("Position: %lf %lf %lf\n\n", objects[i].properties.sphere.position[0], objects[i].properties.sphere.position[1], objects[i].properties.sphere.position[2]);
			
		}
		
		if(strcmp(objects[i].type, "plane") == 0){
			printf("Type: %s\n", objects[i].type);
			printf("Color: %lf %lf %lf\n", objects[i].properties.plane.color[0], objects[i].properties.plane.color[1], objects[i].properties.plane.color[2]);
			printf("Position: %lf %lf %lf\n", objects[i].properties.plane.position[0], objects[i].properties.plane.position[1], objects[i].properties.plane.position[2]);
			printf("Normal: %lf %lf %lf\n\n", objects[i].properties.plane.normal[0], objects[i].properties.plane.normal[1], objects[i].properties.plane.normal[2]);			
		}
	}

	return(0);
	
} 