/**
 * Author: Jarid Bredemeier
 * Email: jpb64@nau.edu
 * Date: Tuesday, September 20, 2016
 * File: raycaster.c
 * Copyright © 2016 All rights reserved 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "..\ppm\ppm6.h"
#include "..\json\json.h"
#include "raycaster.h"


/**
 * sqr
 *
 * @param v
 * @returns 
 * @description 
 */
static inline double sqr(double v) {
	return v * v;
	
}


/**
 * normalize
 *
 * @param v
 * @returns 
 * @description 
 */
static inline void normalize(double *v) {
	double len = sqrt(sqr(v[0]) + sqr(v[1]) + sqr(v[2]));
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
	
}


/*
 Step 1.) Find the equation for the object you are interested in..  
 Step 2.) Parameterize the equation with a center point
 Step 3.) Substitute the eq for a ray into our object equation.
 Step 4.) Solve for t.
 Step 4a.) Rewrite the equation (flatten).
*/

/**
 * sphere_intersection
 *
 * @param ro
 * @param rd
 * @param center
 * @param radius
 * @returns 
 * @description 
 */
double sphere_intersection(double *ro, double *rd, double *center, double radius){
	double a, b, c, t, det;
		
	a = sqr(rd[0]) + sqr(rd[1]) + sqr(rd[2]);
	b =  2 * (rd[0] * (ro[0] - center[0]) + rd[1] * (ro[1] - center[1]) + rd[2] * (ro[2] - center[2]));
	c = sqr(ro[0] - center[0]) + sqr(ro[1] - center[1]) + sqr(ro[2] - center[2]) - sqr(radius);
	det = sqr(b) - 4 * a * c;
	
	if(det < 0) {
		return (-4);
		
	}
		
	det = sqrt(det);
	t = (-b - det) / ( 2 * a);
	
	if(t > 0){
		return t;
		
	}
	t = (-b + det) / (2 * a);
	
	if(t > 0){
		return (-4);
		
	} 

	return (-4);
	
}


/**
 * plane_intersection
 *
 * @param ro
 * @param rd
 * @param p
 * @param n
 * @returns 
 * @description 
 */
int plane_intersection(double *ro, double *rd, double *p, double *n){
	double top, bottom, t;
	
	top = (n[0] * ro[0] - n[0] * p[0] + n[1] * ro[1] - n[1] * p[1] + n[2] * ro[2] - n[2] * p[2]);
	bottom = (- 1 * ((n[0] * rd[0] + n[1] * rd[1] + n[2] * rd[2])));
	t = top / bottom;

	if(t > 0) {
		return t;
		
	}
  
	return (-4);
}


/**
 * raycaster
 *
 * @param objects
 * @returns 
 * @description 
 */
Image* raycaster(Object objects[], Image *image, int width, int height, int num_objects) {
	double cx, cy, h, w, pixel_height, pixel_width, best_t, ro[3];
	int i, t, x, y;
	Pixel pixel;

	best_t = INFINITY;

	pixel_height = h / height;
	pixel_width = w / width;

	cx = 0;
	cy = 0;
		
	ro[0] = 0;
	ro[1] = 0;
	ro[2] = 0;
	
	image->width = width;
	image->height = height;
	image->max_color = 255;	
	
	// Allocated memory size for image data
	image->image_data = malloc(sizeof(Pixel) * image->width * image->height);
	
	
	for(i = 0; i < num_objects; i++) {
		if(strcmp((objects[i].type), "camera") == 0) {
			h = objects[i].properties.camera.height;
			w = objects[i].properties.camera.width;
			printf("%s", objects[i].type);
		}
		
	}
	

	for (y = 0; y < height; y++) {
		
		for (x = 0; x < width; x++) {
			
			// rd = normalize(P - ro)
			double rd[3] = {(cx - (w/2) + pixel_width * (x + 0.5)), (cy - (h/2) + pixel_height * (y + 0.5)), 1};
			
			normalize(rd);

			for (i = 0; i < num_objects; i++) {
				
				t = 0;
				
				if(strcmp((objects[i].type), "sphere")){
					t = sphere_intersection(ro, rd, objects[i].properties.sphere.position, objects[i].properties.sphere.radius);
					
				} else if(strcmp((objects[i].type), "plane")){
					t = plane_intersection(ro, rd, objects[i].properties.plane.position, objects[i].properties.plane.normal);
					
				} else {
					fprintf(stderr, "Error, object type is not valid.\n");	
					exit(-2);
				}
				
				if ((t > 0) && (t < best_t)){
					best_t = t;
					
				}
				
				if((best_t > 0) && (best_t != INFINITY)){
					pixel.red = objects[i].properties.sphere.color[0];
					pixel.green = objects[i].properties.sphere.color[1];
					pixel.blue = objects[i].properties.sphere.color[2];
					image->image_data[y * width + x] = pixel;
					
				} else {
					pixel.red = 0;
					pixel.green = 0;
					pixel.blue = 0;
					image->image_data[y * width + x] = pixel;					
					
				}
				
			}
			
		} // EoRow For Loop
		
	} // EoColumn For Loop
	
	return image;
	
}