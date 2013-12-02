#include "vec3.h"
#include <iostream>
#include <cmath>
using namespace std;

vec3::vec3() : x(0), y(0), z(0) {}
vec3::vec3(double v) : x(v), y(v), z(v) {}
vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

//addition
vec3& vec3::operator+=(const vec3& b) {
	x += b.x; y += b.y; z += b.z;
	return *this;
}
vec3 operator+(vec3 a, const vec3& b) {
	a += b;
	return a;
}

//subtraction
vec3& vec3::operator-=(const vec3& b) {
	x -= b.x; y -= b.y; z -= b.z;
	return *this;
}
vec3 operator-(vec3 a, const vec3& b) {
	a -= b;
	return a;
}

//multiplication
vec3& vec3::operator*=(const double b) {
	x *= b; y *= b; z *= b;
	return *this;
}
vec3 operator*(vec3 a, const double b) {
	a *= b;
	return a;
}
vec3 operator*(const double b, vec3 a) {
	a *= b;
	return a;
}

//division
vec3& vec3::operator/=(const double b) {
	x /= b; y /= b; z /= b;
	return *this;
}
vec3 operator/(vec3 a, const double b) {
	a /= b;
	return a;
}

//dot product
double dot(const vec3& a, const vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 normalize(const vec3& v) {
	return v / length(v);
}

//length
double length(const vec3& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double dist(const vec3 &a, const vec3 &b) {
	return length(a - b);
}

//negation
vec3 vec3::operator-() { return vec3(-x, -y, -z); }

//iostream handling
ostream& operator<<(ostream &out, const vec3 &v) {
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}
