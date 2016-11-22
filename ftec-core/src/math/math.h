#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "rect.h"
#include "mat4.h"
#include "helpers.h"


#define PI 3.141592654f

/*
Every mathematical sturct or class should have (if applicable)

Most arguments should be const &, unless you want to modify the result.
All functions return a reference to themselves, unless they either clone, or calculate a new result

The name should be:							Examples:
<name>[dimensions]							line2, line3, plane, triangle3

Methods for matrices:
translate()
translated()
scale()
scaled()
rotate()
rotated()
clone()

Methods for shapes:
transform(mat[dim] )						Transforms the shape giving the matrix
transformed(mat[dim] )						Copies and transforms the shape giving the matrix
clone()										Clones the object

Methods when applicable:
circumcenter()								Calculates and returns the circumcenter
circumcircle()								Calculates and returns the circumcircle
circumsphere()								Calculates and returns the circumsphere

normalize()
normalized()
flip()
flipped()

magnitude()
length()

distance(vec[dim])							Calculates the distance to the given point (in local coordinates)
project(vec[dim])							Projects point onto plane (and returns the direction)

center()

*/