#ifndef GALX_NODE_INC
#define GALX_NODE_INC

#include "vec3.h"
#include "body.h"

class node {
	body centerofmass;
	vec3 lower, upper;
	vector<node*> children;
	vector<body> bodies;
	node *parent;
	int depth;
	bool contains(vec3);
	bool insert1(body&);
	bool partitioned;
public:
	node(vec3, vec3, int, node*);
	void insert(body*, int);
	body cofm();
};

#endif