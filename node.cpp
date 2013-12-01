#include "node.h"

node::node(vec3 lower, vec3 upper, int depth, node *parent): lower(lower), upper(upper), depth(depth), parent(parent) { }

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
			
		}
	} else return false;
	return true;
}

void node::insert(body* bodylist, int count) { 
	for (int i = 0; i < count; ++i) {
		this->insert1(bodylist[i]);
	}
}