#include <SDL.h>
#include "SDL_thread.h"
void a_julia(SDL_Surface * screen);
void a_cameras(SDL_Surface* screen);
void a_solids(SDL_Surface* screen);
void a_indexing(SDL_Surface* screen);

static int windowStuff(void *ptr)
{
	SDL_Event event; 
	while(SDL_PollEvent(&event))
	{
		//SDL_WaitEvent(&event) ;
		if(event.type==SDL_QUIT) {
			SDL_Quit();
			return 0;
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
	putenv("SDL_VIDEO_CENTERED=1"); 
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode(800, 600, sizeof(unsigned char)*8*3, SDL_SWSURFACE|SDL_RESIZABLE);


	SDL_Thread *thread;
	thread = SDL_CreateThread(windowStuff, "TestThread");

	if (NULL == thread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	} 

	//a_julia(screen);
	//a_cameras(screen);
	//a_solids(screen);
	a_indexing(screen);
	return 0;
}