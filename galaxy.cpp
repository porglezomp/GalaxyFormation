#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

SDL_Window *window;
SDL_GLContext context;

bool running = true;
int width = 640, height = 480;

void quit(int);
void events();

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) quit(1);
	window = SDL_CreateWindow("Galaxy Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (window == NULL) quit(2);
	SDL_GL_SetSwapInterval(1);
	context = SDL_GL_CreateContext(window);
	if (context == NULL) quit(3);
	while (running) {
		glClear(GL_COLOR_BUFFER_BIT);
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