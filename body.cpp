#include "body.h"
#include "vec3.h"
#include <SDL2/SDL_opengl.h>

body::body(vec3 pos, double mass): pos(pos), vel(0), mass(mass) { }
body::body(vec3 pos, vec3 vel, double mass): pos(pos), vel(vel), mass(mass) { }

void body::draw() { glVertex3d(pos.x, pos.y, pos.z); }