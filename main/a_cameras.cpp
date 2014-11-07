#include <core/image.h>
#include <core/point.h>
#include <core/vector.h>
#include <core/scalar.h>
#include <core/julia.h>
#include <rt/ray.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/orthographic.h>
#include <rt/cameras/fisheye.h>
#include <rt/cameras/environment.h>
#include <iostream>
#include <rt/renderer.h>

using namespace rt;
using namespace std;
float a2computeWeight(float fx, float fy, const Point& c, float div) {
	Point v(fx, fy, 0.0f);
	int numIter = julia(v, c);
	return numIter/(numIter+div);
}

RGBColor a2computeColor(const Ray& r) {
	float theta = asin(r.d.z)/pi*2;
	float phi = atan2(r.d.y,r.d.x)/pi;
	float ofx = absfractional((r.o.x+1.0f)/2.0f)*2.0f-1.0f;
	float ofy = absfractional((r.o.y+1.0f)/2.0f)*2.0f-1.0f;
	RGBColor color = RGBColor::rep(0.0f);
	color = color + a2computeWeight(phi, theta, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
	color = color + a2computeWeight(phi, theta, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
	color = color + a2computeWeight(ofy, ofx, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.4f, 0.5f, 0.6f);
	color = RGBColor::rep(1.0f) - color;
	if (absfractional(theta/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.5f,0.5f)*0.7f;
	if (absfractional(phi/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.9f,0.5f)*0.7f;
	return color;
}


void a_cameras(SDL_Surface* screen) {
	Image img(800, 800);
	Image low(128, 128);
	cout<<"Press any key to start"<<endl;
	system("pause");

	/*OrthographicCamera ocam(Point(0, 0, 0), Vector(0.1, 0.1, 1), Vector(0.2, 1.0, 0.2), 10.f, 10.f);
	Renderer r0(&ocam,0);
	r0.test_render1(img,screen);
	img.writePNG("a1-4.png");
	system("pause");

	PerspectiveCamera pcam(Point(0, 0, 0), Vector(1, 0, 0.1), Vector(0, 0, 1), pi/3, pi/3);
	Renderer r1(&pcam,0);
	r1.test_render1(img,screen);
	system("pause");
	r1.test_render1(low,screen);
	img.writePNG("a1-2.png");
	low.writePNG("a1-2-low.png");
	system("pause");

	PerspectiveCamera pcam2(Point(0, 0, 0), Vector(0.5, 0.5, 0.3), Vector(0, 0, 1), pi * 0.9f, pi * 0.9f);
	Renderer r12(&pcam2,0);
	r12.test_render1(img,screen);
	img.writePNG("a1-3.png");
	system("pause");*/



	FishEyeCamera fcam(Point(0, 0, 0), Vector(1, 0, 0), Vector(0, 0, 1), pi, pi);
	Renderer r2(&fcam,0);
	r2.test_render1(img,screen);
	img.writePNG("a1-5.png");
	system("pause");

	EnvironmentCamera ecam(Point(0, 0, 0), Vector(1, 0, 0), Vector(0, 0, 1), pi, pi);
	Renderer r3(&ecam,0);
	r3.test_render1(img,screen);
	img.writePNG("a1-6.png");
	system("pause");
	SDL_Quit();

}
