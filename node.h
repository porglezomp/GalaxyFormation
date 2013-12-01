#ifndef GALX_NODE_INC
#define GALX_NODE_INC

#include "vec3.h"
#include "body.h"

class node {
	bool partitioned;
	int depth;
	body centerofmass;
	vec3 lower, center, upper;
	vector<node*> children;
	vector<body*> bodies;
	node *parent;
	bool contains(vec3);
	bool insert1(body&);
	
public:
	node(vec3, vec3, int, node*);
	void insert(body*, int);
	void partition();
	body cofm();
};

#endif