#ifndef GALX_BODY_INC
#define GALX_BODY_INC

#include "vec3.h";
class node;

class body {
	vec3 vel;
	double attract;
public:
	vec3 pos;
	body();
	body(vec3, double);
	body(vec3, vec3, double);
	void attract_to(body&);
	void update(node&);
	void move();

	friend body average(body, body);
};

#endif