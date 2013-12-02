#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <vector>
#include "body.h"
#include "vec3.h"
#include "node.h"
#include <stdlib.h>

float size = 1E6;
float scale = 1E-5;

SDL_Window *window;
SDL_GLContext context;
node root (vec3(-size, -size, -size), vec3(size, size, size), 0, NULL);

bool running = true;
int width = 1280, height = 720;
vector<body> bodies;

void quit(int);
void events();

//NeHe perspective code (http://nehe.gamedev.net/article/replacement_for_gluperspective/21002/)
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar ) {
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;
	fH = tan( fovY / 360 * pi ) * zNear;
	fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

double randin(double range) {
	return (rand()%(int)(range*20000)/10000.0)-range;
}

int main() {
	for (int i = 0; i < 100; ++i) {
		bodies.push_back(body(vec3(randin(1E5), randin(1E5), randin(1E5)), 1E25));
	}
	root.insert(bodies.data(), bodies.size());
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) quit(1);
	window = SDL_CreateWindow("Galaxy Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (window == NULL) quit(2);
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	context = SDL_GL_CreateContext(window);
	
	//Set alpha blending
	glPointSize(3);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspectiveGL(75, width/(float)height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -10);
	glScalef(scale, scale, scale);
	glRotatef(25, 1, 0, 0);
	
	if (context == NULL) quit(3);
	while (running) {
		root.update();
		for (int i = 0; i < bodies.size(); ++i) {
			bodies[i].update(root);
		}
		for (int i = 0; i < bodies.size(); ++i) {
			bodies[i].move();
		}
		
		glRotatef(.1, 0, 1, .1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glColor4f(.2, .5, .2, .2);
		root.draw();
		
		glColor4f(1, 1, 1, 1);
		glBegin(GL_POINTS);
		for (int i = 0; i < bodies.size(); ++i) {
			glVertex3d(bodies[i].pos.x, bodies[i].pos.y, bodies[i].pos.z);
		}
		glEnd();
		
		SDL_GL_SwapWindow(window);
		events();
	}
	quit(0);
}

void events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
				break;
		}
	}
}

void quit(int rc) {
	exit(rc);
}