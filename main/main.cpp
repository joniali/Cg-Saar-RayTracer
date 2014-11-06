#include <SDL.h>
#include "SDL_thread.h"
void a_julia(SDL_Surface * screen);
void a_cameras();
void a_solids();


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
    // SDL stuff to show in window.. this just creates window and passes to julia which sends to renderer and it renders in the window. 
	/*
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = NULL;
	
	screen = SDL_SetVideoMode(800, 800, sizeof(unsigned char)*8*3, SDL_SWSURFACE|SDL_RESIZABLE);
	//SDL_WM_SetCaption("Graphics First Assignment", NULL);
	 SDL_Thread *thread;
   

    // Simply create a thread
    thread = SDL_CreateThread(windowStuff, "TestThread");

    if (NULL == thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
    } 
	*/
	   
	 //a_julia(screen);
	 a_cameras();
	a_solids();
    return 0;
}