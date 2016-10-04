# Simple Raycaster

This program reads in a collection of objects (scene) formatted using JSON (JavaScript Object Notation). These mathematical 
primitives, sphere(s) and plane(s) are loaded into memory, where I preform a simple ray interection test to determine if the
object is in the view plane and assign that pixel the color of the intersecting object. Finally this image data is written out
in portable pixmap format (PPM). I decided on using p6 format as the write functionality I implemented in my previous project
was the simplistic port into this application.

## Usage

raycast width height input.json output.ppm

## Resources

* Scratchapixel [Ray-Plane Intersection] 
* A. Glassner, etal., [An Introduction to Ray Tracing], Academic Press, 1989.

[An Introduction to Ray Tracing]: http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter0.htm
[Ray-Plane Intersection]: http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
