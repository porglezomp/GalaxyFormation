#ifndef GALX_BODY_INC
#define GALX_BODY_INC

struct vec3;

class body {
	vec3 pos, vel;
	double mass;
public:
	body(vec3, double);
	body(vec3, vec3, double);
};

#endif