
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
//#include <rt/groups/bvh.h>
#include <rt/groups/kd.h>
#include <rt\groups\simplegroup.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt\solids\aabox.h>
#include <rt/solids/sphere.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/triangle.h>
#include <rt/solids/quad.h>
#include <rt/solids/disc.h>
#include <rt/solids/aabox.h>
#include <rt\solids\gensphere.h>
using namespace rt;


void a_indexing(){//SDL_Surface* screen) {
	//Image img(800, 600);

	KDTree* scene = new KDTree();
	//scene->add(new AABox(Point(2, 1.5f, -0.5f), Point(3, 2.5f, 2.5f), nullptr, nullptr));
	//scene->add(new Triangle(Point(3, 2, 3), Point(3, 2, -3), Point(-3, 2, -3), nullptr, nullptr));
	//scene->add(new Triangle(Point(3, 2, 3), Point(3, 2, -3), Point(-3, 2, -3), nullptr, nullptr));
	//scene->add(new Triangle(Point(3, 2, 3), Point(3, 2, -3), Point(-3, 2, -3), nullptr, nullptr));
	scene->add(new Sphere(Point(2.5f, .5f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(2.5f, -1.f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(4.5f, .5f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(4.5f, 1.5f, -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(4.5f, .5f, -1), 0.5, nullptr, nullptr));
	/*
	GenSphere auxgS(Point(-2.f, 1.7f, 0), 2, nullptr, nullptr);
	Sphere auxS(Point(4.5f, .5f, -1), 0.5, nullptr, nullptr);
	Point argvertices[3];
	argvertices[0] = Point(-1, 3.7f, 0);
	argvertices[1] = Point(1, 2, 1);
	argvertices[2] = Point(3, 2.8f, -2);
	Triangle auxT(argvertices, nullptr, nullptr);
	Quad auxQ(Point(1, -0.9f, 4.5f), Vector(-2, 0, 0), Vector(0, 0.1f, -2), nullptr, nullptr);
	Disc auxD(Point(-3, -0.75f, 1.5f), Vector(0, 0.5f, 0.5f), 1.5f, nullptr, nullptr);
	scene->add(new AABox(auxgS.getBounds().min, auxgS.getBounds().max, nullptr, nullptr));
	scene->add(new AABox(auxQ.getBounds().min, auxQ.getBounds().max, nullptr, nullptr));
	scene->add(new AABox(auxD.getBounds().min, auxD.getBounds().max, nullptr, nullptr));
	scene->add(new AABox(auxT.getBounds().min, auxT.getBounds().max, nullptr, nullptr));
	scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
	scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));
	scene->add(new AABox(auxS.getBounds().min, auxS.getBounds().max, nullptr, nullptr));//getboundingbox test*/
	loadOBJ(scene, "models/", "cow.obj");

	scene->rebuildIndex();

	World world;
	world.scene = scene;

	Image img(800, 600);
	RayCastingIntegrator integrator(&world);
	PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f, 1.0f, -0.6f), Vector(0, 0, 1), pi / 8, pi / 6);
	Renderer engine1(&cam1, &integrator);

	engine1.test_render2(img);// , screen);
	img.writePNG("a3-1.png");

	Image img2(800, 600);
	RayCastingIntegrator integrator2(&world);
	PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f) - Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi / 8, pi / 6);
	Renderer engine2(&cam2, &integrator2);
	engine2.test_render2(img2);// , screen);
	img2.writePNG("a3-2.png");

	/*engine1.test_render2(img,screen);
	img.writePNG("a3-3.png");

	Image img2(320, 240);
	RayCastingIntegrator integrator2(&world);
	PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f) - Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi / 8, pi / 6);
	Renderer engine2(&cam2, &integrator2);
	engine2.test_render2(img2 ,screen);
	img2.writePNG("a3-4.png");
>>>>>>> d0494d2e246e189f38c882e80255207b85dd1454
*/

	system("pause");
	//SDL_Quit();
}
