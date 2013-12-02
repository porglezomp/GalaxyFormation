#include "body.h"
#include "node.h"
#include "vec3.h"
#include "constants.h"
#include <iostream>
#include <SDL2/SDL_opengl.h>

using namespace std;

body::body(): pos(0), vel(0), attract(0) { }
body::body(vec3 pos, double mass): pos(pos), vel(0), attract(mass*G) { }
body::body(vec3 pos, vec3 vel, double mass): pos(pos), vel(vel), attract(mass*G) { }

void body::attract_to(body &b) {
	vec3 force = b.pos - pos;
	double d = length(force);
	force *= b.attract*dt;
	force /= d*d*d;
	d = (d*d)/(b.attract*dt);
	if (d == d && d != 0) {
		vel += force;
		cout << force << endl;
		cout << vel << endl;
	}
}

void body::update(node &n) {
	if (n.partitioned) {
		if (r > n.val/dist(pos, n.centerofmass.pos)) {
			attract_to(n.centerofmass);
		} else {
			for (int i = 0; i < n.children.size(); ++i) {
				this->update(*n.children[i]);
			}
		}
	} else {
		int count;
		body **bodies = n.get_bodies(&count);
		for (int i = 0; i < count; ++i) {
			attract_to(*bodies[i]);
		}
	}
}

void body::move() {
	pos += vel * dt;
}

body average(body a, body b) {
	vec3 newpos = a.pos * a.attract + b.pos * b.attract;
	double sum_mass = a.attract + b.attract;
	if (sum_mass == 0) return body(vec3(0), 0);
	newpos /= sum_mass;
	return body(newpos, sum_mass);
}