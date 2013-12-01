#include <vector>
#include <SDL2/SDL_opengl.h>
#include "node.h"

using namespace std;

node::node(vec3 lower, vec3 upper, int depth, node *parent): lower(lower), upper(upper), depth(depth), parent(parent) {
	center = (upper + lower) / 2;
}

bool node::contains(vec3 v) {
	if (v.x < lower.x || v.y < lower.y || v.z < lower.z) return false;
	if (v.x > upper.x || v.y > upper.y || v.z > upper.z) return false;
	return true;
}

bool node::insert1(body &b) {
	if (this->contains(b.pos)) {
		if (partitioned) {
			for (int j = 0; j < 8; ++j) {
				if (children[j]->insert1(b)) break; //Only insert it into the one it needs to be in
			}
		} else {
			bodies.push_back(&b);
		}
	} else return false;
	return true;
}

void node::insert(body** bodylist, int count) { 
	for (int i = 0; i < count; ++i) {
		this->insert1(*bodylist[i]);
	}
}

body node::cofm() {
	centerofmass = body(vec3(0), 0);
	if (partitioned) {
		for (int i = 0; i < children.size(); ++i) {
			centerofmass = average(centerofmass, children[i]->cofm());
		}
	} else {
		for (int i = 0; i < bodies.size(); ++i) {
			centerofmass = average(centerofmass, *bodies[i]);
		}
	}
	return centerofmass;
}

void node::draw() {
	//Bottom
	glBegin(GL_LINE_STRIP);
	glVertex3f(lower.x, lower.y, lower.z);
	glVertex3f(lower.x, upper.y, lower.z);
	glVertex3f(upper.x, upper.y, lower.z);
	glVertex3f(upper.x, lower.y, lower.z);
	glVertex3f(lower.x, lower.y, lower.z);
	//Top
	glVertex3f(lower.x, lower.y, upper.z);
	glVertex3f(lower.x, upper.y, upper.z);
	glVertex3f(upper.x, upper.y, upper.z);
	glVertex3f(upper.x, lower.y, upper.z);
	glVertex3f(lower.x, lower.y, upper.z);
	glEnd();
	
	glBegin(GL_LINES);
	//Connetions
	glVertex3f(lower.x, upper.y, lower.z);
	glVertex3f(lower.x, upper.y, upper.z);
	glVertex3f(upper.x, upper.y, lower.z);
	glVertex3f(upper.x, upper.y, upper.z);
	glVertex3f(upper.x, lower.y, lower.z);
	glVertex3f(upper.x, lower.y, upper.z);
	glEnd();
	
	//Children
	for (int i = 0; i < children.size(); ++i) {
		children[i]->draw();
	}
}

void node::partition() {
	vec3 nl, nu;
	children.push_back(new node(lower, center, depth + 1, this)); //Bottom, left back
	nl = lower; nl.x = center.x;
	nu = center; nu.x = upper.x;
	children.push_back(new node(nl, nu, depth + 1, this)); //Bottom, right, back
	nl = lower; nl.y = center.y;
	nu = center; nu.y = upper.y;
	children.push_back(new node(nl, nu, depth + 1, this)); //Bottom, left, front
	nl = center; nl.z = lower.z;
	nu = upper; nu.z = center.z;
	children.push_back(new node(nl, nu, depth + 1, this)); //Bottom, right, front
	nl = lower; nl.z = center.z;
	nu = center; nu.z = upper.z;
	children.push_back(new node(nl, nu, depth + 1, this)); //Top, left, back
	nl = center; nl.y = lower.y;
	nl = upper; nu.y = center.y;
	children.push_back(new node(nl, nu, depth + 1, this)); //Top, right, back
	nl = center; nl.x = lower.x;
	nu = upper; nu.x = center.x;
	children.push_back(new node(nl, nu, depth + 1, this)); //Top, left, front
	children.push_back(new node(center, upper, depth + 1, this)); //Top, right, front
	this->insert(bodies.data(), bodies.size());
	bodies.clear();
}