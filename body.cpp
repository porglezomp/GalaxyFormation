#include "body.h"
#include "vec3.h"
#include <SDL2/SDL_opengl.h>

body::body(): pos(0), vel(0), mass(0) { }
body::body(vec3 pos, double mass): pos(pos), vel(0), mass(mass) { }
body::body(vec3 pos, vec3 vel, double mass): pos(pos), vel(vel), mass(mass) { }

void body::draw() { glVertex3d(pos.x, pos.y, pos.z); }

body average(body a, body b) {
	vec3 newpos = a.pos * a.mass + b.pos * b.mass;
	double sum_mass = a.mass + b.mass;
	if (sum_mass == 0) return body(vec3(0), 0);
	newpos /= sum_mass;
	return body(newpos, sum_mass);
}