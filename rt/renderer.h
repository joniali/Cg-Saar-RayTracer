#ifndef CG1RAYTRACER_RENDERER_HEADER
#define CG1RAYTRACER_RENDERER_HEADER

#include <core/scalar.h>
#include <rt\cameras\camera.h>
#include <rt\integrators\integrator.h>
#include <SDL.h>
namespace rt {

class Image;
class Camera;
class Integrator;

class Renderer {
public:
    Renderer(Camera* cam, Integrator* integrator);
    void setSamples(uint samples);
	void render(Image& img,SDL_Surface * screen);
    void test_render1(Image& img,SDL_Surface * screen);
	void test_render2(Image& img);// , SDL_Surface* screen);
private:
	Camera* cam;
	Integrator* integrator;
	
};

}

#endif
