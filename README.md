# Simple Raycaster

This program reads in a collection of objects written to a scene that are formatted using JSON (JavaScript Object Notation). These objects consisting of mathematical primitives, sphere(s) and plane(s) that are read into system memory where vector (ray) intersections calculations are made in order to detect an object's location in 3D space. This intersect data is stored into an image buffer and written to a P6 portable pixmap format (PPM) for viewing.This program reads in a collection of objects in a scene formatted using JSON (JavaScript Object Notation). These objects consisting of mathematical primitives, sphere(s) and plane(s) that are stored into system memory where vector (ray) intersections calculations are made in order to detect an object's location in 3D space. This intersect data is used to color individual pixels with the object’s corresponding color properties which is then loaded into an image buffer and written out to a P6 portable pixmap format (PPM) for viewing.This program reads in a collection of objects from a scene formatted using JSON (JavaScript Object Notation). These objects consisting of mathematical primitives, sphere(s) and plane(s) that are stored into system memory where vector (ray) intersections calculations are performed to detect an object's location in 3D space. This intersection data is then used to construct an image of scene by coloring individual pixels with an object’s corresponding color properties. Lastly this image data is fed into an image buffer and written out to a P6 portable pixmap format (PPM) for viewing.

## Usage
```c
raycast width height input.json output.ppm
```

## Example json scene data
```javascript
[
 {
    "type": "camera",
    "width": 1,
    "height": 1
 },
 {
    "type": "sphere",
    "color": [1, 0, 0],
    "position": [1, 1, 10],
    "radius": 2
 },
 {
    "type": "plane",
    "color": [0, 1, 0],
    "position": [0, -1, 0],
    "normal": [0, 1, 0]
 }
]
```
## Resources

* Scratchapixel [Ray-Plane Intersection] 
* A. Glassner, etal., [An Introduction to Ray Tracing], Academic Press, 1989.

[An Introduction to Ray Tracing]: http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter0.htm
[Ray-Plane Intersection]: http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
