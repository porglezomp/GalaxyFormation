#ifndef TENSOR_VEC3_INCLUDED
#define TENSOR_VEC3_INCLUDED

#include <iostream>
using namespace std;

struct vec3 {
	double x, y, z;

	vec3();
	vec3(double);
	vec3(double, double, double);
	vec3& operator+=(const vec3&);
	vec3& operator-=(const vec3&);
	vec3& operator*=(const double);
	vec3& operator/=(const double);
	vec3 operator-();
	
};

vec3 operator+(vec3, const vec3&);
vec3 operator-(vec3, const vec3&);
vec3 operator*(vec3, const double);
vec3 operator*(const double, vec3);
vec3 operator/(vec3, const double);
ostream& operator<<(ostream&, const vec3&);

double dot(const vec3&, const vec3&);
double length(const vec3&);
vec3 normalize(const vec3&);

#endif