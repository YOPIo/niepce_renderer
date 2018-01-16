# niepce renderer

Simple Monte Carlo Path Tracer

# Features

 - Pure Pathtracing with Next Event Estimation
 - BVH (Surface Area Heuristic)
 - Shape
    - Triangle
    - Sphere
 - BSDF
    - Lambert
    - Oren-Nayar
    - Matte (Lambert and Oren-Nayar)
    - Glass
    - Mirror
    - GGX
 - Light
	- Image based lighting
	- Point light
	- Area light

# Example output

![rtcamp5](https://user-images.githubusercontent.com/12379808/34995921-5ea5d76a-fb1b-11e7-9045-e50198b308b3.png)

# How to build and run
```
git clone https://github.com/yopio/niepce.git
cd niepce
mkdir build
cd build
cmake ..
make
./niepce
```
