#include <SDL.h>
#include "SDL_thread.h"
void a_julia(SDL_Surface * screen);
void a_cameras();



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
    
	//SDL_Init( SDL_INIT_EVERYTHING );
	//SDL_Init(SDL_INIT_VIDEO);
	//SDL_Surface* screen = NULL;
	
	//screen = SDL_SetVideoMode(800, 800, sizeof(unsigned char)*8*3, SDL_SWSURFACE|SDL_RESIZABLE);
	//SDL_WM_SetCaption("Graphics First Assignment", NULL);
	// SDL_Thread *thread;
   
//	int threadReturnValue;

    // Simply create a thread
  //  thread = SDL_CreateThread(windowStuff, "TestThread");

   // if (NULL == thread) {
     //   printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
   // } else {
        //SDL_WaitThread(thread, &threadReturnValue);
		//SDL_Quit();
        //printf("\nThread returned value: %d", threadReturnValue);
    //}

	//SDL_Delay(10000);
   // a_cameras();
	/*SDL_Event event;
	  SDL_WaitEvent(&event) ;
		  if(event.type==SDL_QUIT) {
			SDL_Quit();
		  }       
      */    
	 //a_julia(screen);
	 a_cameras();
    return 0;
}