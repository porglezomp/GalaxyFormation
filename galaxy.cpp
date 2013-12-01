#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

SDL_Window *window;
SDL_GLContext context;

int width = 640, height = 480;

void quit(int);

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) quit(1);
	window = SDL_CreateWindow("Galaxy Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (window == NULL) quit(2);
	context = SDL_GL_CreateContext(window);
	if (context == NULL) quit(3);
	SDL_GL_SwapWindow(window);
	SDL_Delay(1000);
	quit(0);
}

void quit(int rc) {
	exit(rc);
}