#ifndef GALX_NODE_INC
#define GALX_NODE_INC

#include <vector>
#include "vec3.h"
#include "body.h"

class node {
	int depth;
	vec3 lower, center, upper;
	std::vector<body*> bodies;
	node *parent;
	bool contains(vec3);
	bool insert1(body&);
	
public:
	std::vector<node*> children;
	
	body centerofmass;
	float val;
	bool partitioned;
	
	node(vec3, vec3, int, node*);
	~node();
	
	void insert(body*, int);
	void insert(body**, int);
	void partition();
	void collapse();
	void pass_upward(body*);
	body** get_bodies(int*);
	
	void draw();
	void update();
	body cofm();
};

#endif