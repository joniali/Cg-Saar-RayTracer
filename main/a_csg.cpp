
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
void  a_csg()
{
	Image img(800, 600);

	
	
	

	SimpleGroup* scene = new SimpleGroup();
	World world;
	world.scene = scene;
	substract* sub = new subtract();

	sub->first = new Sphere(Point(0.f, 3.f, 0.f), 2.5f, nullptr, nullptr);
	sub->second = new Sphere(Point(0.f, 2.f, 0.f), 2.5, nullptr, nullptr);
	
	scene->add(sub);
	RayCastingIntegrator integrator(&world);

	PerspectiveCamera cam(Point(-3.75f, 20, 40), Vector(0.1, -0.5, -1), Vector(0, 1, 0), pi / 4, pi / 3);
	Renderer engine(&cam, &integrator);
	engine.test_render2(img);
	img.writePNG("a7-2.png");

}