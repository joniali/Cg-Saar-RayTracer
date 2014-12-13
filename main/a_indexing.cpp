
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
#include <rt\groups\csg.h>
using namespace rt;


void a_indexing(){
	//SimpleGroup* scene = new SimpleGroup();
	KDTree* scene = new KDTree();
	scene->add(new Sphere(Point(1.f, 1.f, 0.f), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(-1.f, 1.f, 0.f), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(0.f, 1.f, 0.f), 0.5, nullptr, nullptr));
	scene->add(new Sphere(Point(0.f, 0.f, 0.f), 0.5f, nullptr, nullptr));

	//loadOBJ(scene, "models/", "cello.obj");
	scene->rebuildIndex();
	World world;
	world.scene = scene;
	/*Image img(800, 600);

	RayCastingIntegrator integrator(&world);
	PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f, 1.0f, -0.6f), Vector(0, 0, 1), pi / 8, pi / 6);
	Renderer engine1(&cam1, &integrator);
	engine1.test_render2(img);
	img.writePNG("a3-1.png");*/
	/*char fuck[50];
	sprintf(fuck, "a3 -%d.png", i);*/
	Image img2(400, 400);

	RayCastingIntegrator integrator2(&world);
	PerspectiveCamera cam2(Point(0.f, -5.f, 3.f), Vector(0.f, 1.f, -1.f), Vector(0.f, 0.f, 0.1f), pi / 8, pi / 6);
	Renderer engine2(&cam2, &integrator2);
	engine2.test_render2(img2);
	
	img2.writePNG("a3 - 1.png");

	system("pause");
}
