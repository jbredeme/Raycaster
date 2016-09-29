/**
 * Author: Jarid Bredemeier
 * Email: jpb64@nau.edu
 * Date: Tuesday, September 20, 2016
 * File: json.h
 */
#ifndef _json_h
#define _json_h

typedef struct Camera {
	double width;
	double height;
	
} Camera;

typedef struct Plane {
	double color[3];
	double position[3];
	double normal[3];
	
} Plane;

typedef struct Sphere {
	double color[3];
	double position[3];
	double radius;
	
} Sphere;

typedef struct Object {
	char *type;
	
	union properties {
		Camera camera;
		Plane plane;
		Sphere sphere;
		
	} properties;

} Object;

void json_read_scene(FILE *fpointer, Object objects[]);
 
#endif