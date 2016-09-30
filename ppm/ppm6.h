/**
 * Author: Jarid Bredemeier
 * Email: jpb64@nau.edu
 * Date: Tuesday, September 20, 2016
 * File: ppm6.h
 * Copyright © 2016 All rights reserved
 */
 
#ifndef _ppm6_h
#define _ppm6_h

/**
 * Pixel
 *	Pixel is a structure that stores 3 bites with a value range of 0 to 255.
 */
typedef struct Pixel {
    unsigned char red, green, blue;

} Pixel;

/**
 * Image
 * 	Image structure stores image information from a file according to the
 * 	PPM Format Specification.
 */
typedef struct Image {
    char *magic_number;
    int width, height;
    int max_color;
    Pixel *image_data;

} Image;

 
#endif