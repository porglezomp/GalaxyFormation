#include "node.h"

node::node(vec3 lower, vec3 upper, int depth, node *parent): lower(lower), upper(upper), depth(depth), parent(parent) {
	center = (upper + lower) / 2;
}

bool node::contains(vec3 v) {
	if (v.x < lower.x || v.y < lower.y || v.z < lower.z) return false;
	if (v.x > upper.x || v.y > upper.y || v.z > upper.z) return false;
	return true;
}

bool node::instert1(body &b) {
	if (contain(b.pos)) {
		if (partitioned) {
			for (int j = 0; j < 8; ++j) {
				if (children[j]->insert1(b)) break; //Only insert it into the one it needs to be in
			}
		} else {
			body.push_back(&b);
		}
	} else return false;
	return true;
}

void node::insert(body* bodylist, int count) { 
	for (int i = 0; i < count; ++i) {
		this->insert1(bodylist[i]);
	}
}

body node::cofm() {
	centerofmass = body(vec3(0), 0);
	if (partitioned) {
		for (int i = 0; i < children.length(); ++i) {
			centerofmass = average(centerofmass, children.cofm());
		}
	} else {
		for (int i = 0; i < bodies.length(); ++i) {
			centerofmass = average(centerofmass, *bodies[i]);
		}
	}
	return centerofmass;
}

void partition() {
	vec3 nl, nu;
	children.push_back(&node(lower, center, depth + 1, this)); //Bottom, left back
	nl = lower; nl.x = center.x;
	nu = center; nu.x = upper.x;
	children.push_back(&node(nl, nu, depth + 1, this)); //Bottom, right, back
	nl = lower; nl.y = center.y;
	nu = center; nu.y = upper.y;
	children.push_back(&node(nl, nu, depth + 1, this)); //Bottom, left, front
	nl = center; nl.z = lower.z;
	nu = upper; nu.z = center.z;
	children.push_back(&node(nl, nu, depth + 1, this)); //Bottom, right, front
	nl = lower; nl.z = center.z;
	nu = center; nu.z = upper.z;
	children.push_back(&node(nl, nu, depth + 1, this)); //Top, left, back
	nl = center; center.y = lower.y;
	nl = upper; upper.y = center.y;
	children.push_back(&node(nl, nu, depth + 1, this)); //Top, right, back
	nl = center; nl.x = lower.x;
	nu = upper; nu.x = center.x;
	children.push_back(&node(nl, nu, depth + 1, this)); //Top, left, front
	children.push_back(&node(center, upper, depth + 1, this)); //Top, right, front
	this->insert(bodies.data(), bodies.length());
	bodies.clear();
}