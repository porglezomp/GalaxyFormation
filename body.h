#ifndef GALX_BODY_INC
#define GALX_BODY_INC

#include "vec3.h";

class body {
	vec3 vel;
	double mass;
public:
	vec3 pos;
	body();
	body(vec3, double);
	body(vec3, vec3, double);
	void draw();
	friend body average(body, body);
};

#endif