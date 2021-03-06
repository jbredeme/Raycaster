# Simple Raycaster ![Jarid_Bredemeier](https://img.shields.io/badge/build-passing-green.svg?style=flat-plastic)

This program reads in a collection of objects from a scene formatted using JSON (JavaScript Object Notation). These objects consisting of mathematical primitives, sphere(s) and plane(s) are stored into system memory where vector (ray) intersections calculations are then performed to determine an object's location in 3D space. This intersection data is used to construct an image of scene by coloring individual pixels on a pixel map with an object’s corresponding color property. Lastly this image data is fed into an image buffer and written out to a P6 portable pixmap format (PPM) for viewing.

## Screenshots
<img src="https://github.com/jbredeme/Raycaster/blob/master/example/png/example01.png" width="288"> <img src="https://github.com/jbredeme/Raycaster/blob/master/example/png/example02.png" width="288"> <img src="https://github.com/jbredeme/Raycaster/blob/master/example/png/example03.png" width="288">

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
## Built With
* [Cygwin](https://cygwin.com/index.html) - 64-bit version for Windows
* GNU Compiler Collection (GCC) release 5.4.0
* GNU Make release 4.2.1
* Windows 10 Professional

## Author
* **Jarid Bredemeier**

## Resources
* [Ray-Plane Intersection] - Scratchapixel
* A. Glassner, etal., [An Introduction to Ray Tracing], Academic Press, 1989.

[An Introduction to Ray Tracing]: http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter0.htm
[Ray-Plane Intersection]: http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
