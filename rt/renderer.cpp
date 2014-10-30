#include <rt\renderer.h>
#include <core/image.h>
#include <core/color.h>
#include <rt\ray.h>
#include <iostream>


using namespace std;
rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);
rt::RGBColor a2computeColor(const rt::Ray& r);
namespace rt{

	
	Renderer::Renderer(Camera* cam, Integrator* integrator):cam(cam)
	{
		
	}

	void Renderer::setSamples(uint samples)
	{
		
	}
	void Renderer::render(Image& img, SDL_Surface* screen)
	{
		Uint32 rmask, gmask, bmask, amask;
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif
		SDL_Surface* screenbuff = SDL_SetVideoMode(800, 800, sizeof(unsigned char)*8*3, SDL_SWSURFACE|SDL_RESIZABLE);
			//SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, sizeof(unsigned char)*8*3,rmask, gmask, bmask, amask);
		 int bpp = screenbuff->format->BytesPerPixel;
		cout<< "BPP are" <<bpp<<endl;
		cout<< "Image is : " <<img.width()<<" " <<img.height()<<endl;
		 SDL_PumpEvents();
		for (uint j=0;j< img.height();j++)
		{
			for (uint i=0;i<img.width();i++)
			{
				img(i,j)=a1computeColor(i,j,img.width(),img.height());
				//cout<< "position " <<+i*bpp+j*screen->pitch<<endl;
				((unsigned char *)screenbuff->pixels+i*bpp+j*screenbuff->pitch)[0]=img(i,j).r*255.0;
				((unsigned char *)screenbuff->pixels+i*bpp+j*screenbuff->pitch)[1]=img(i,j).g*255.0;
				((unsigned char *)screenbuff->pixels+i*bpp+j*screenbuff->pitch)[2]=img(i,j).b*255.0;
				// 
				
			}
			if(j%30==0)
			{
				SDL_BlitSurface(screenbuff,NULL,screen,NULL);
				SDL_UpdateRect(screen,0,0,800,j);
				//SDL_Flip( screen );
			}
		}
			
		//
		
		  SDL_Delay( 100000 );
		 SDL_FreeSurface( screenbuff );
		 // SDL_Quit();
	
	}
	
	void Renderer::test_render1(Image& img)
	{
			for (uint j=0;j< img.height();j++)
			{
				for (uint i=0;i<img.width();i++)
					{
						
						
						float X = float(i) / float(img.width()) - 1;
						float Y = 1 - float(j) / float(img.height());

						const Ray r = cam->getPrimaryRay(X, Y);
						
						img(i, j)=a2computeColor(r);
				
					}
			}
	}
}
