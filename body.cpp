#include "body.h"
#include "vec3.h"

void glVertex3f(float, float, float);

body::body(vec3 pos, double mass): pos(pos), vel(0), mass(mass) { }
body::body(vec3 pos, vec3 vel, double mass): pos(pos), vel(vel), mass(mass) { }

void draw() { glVertex3f(pos.x, pos.y, pos.z); }