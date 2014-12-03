
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/groups/simplegroup.h>
#include <rt/materials/dummy.h>

#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/projectivelight.h>
#include <rt/textures/constant.h>

#include <rt/materials/lambertian.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/raytrace.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/materials/combine.h>
#include <rt\materials\CookTorranceMaterial.h>

#include <rt/integrators/recraytrace.h>

using namespace rt;

namespace {
	void makeBox(Group* scene, const Point& aaa, const Vector& forward, const Vector& left, const Vector& up, CoordMapper* texMapper, Material* material) {
		scene->add(new Quad(aaa, forward, left, texMapper, material));
		scene->add(new Quad(aaa, forward, up, texMapper, material));
		scene->add(new Quad(aaa, left, up, texMapper, material));
		Point bbb = aaa + forward + left + up;
		scene->add(new Quad(bbb, -forward, -left, texMapper, material));
		scene->add(new Quad(bbb, -forward, -up, texMapper, material));
		scene->add(new Quad(bbb, -left, -up, texMapper, material));
	}

	Texture* redtex;
	Texture* greentex;
	Texture* bluetex;
	Texture* blacktex;
	Texture* whitetex;

	void initTextures() {
		redtex = new ConstantTexture(RGBColor(.7f, 0.f, 0.f));
		greentex = new ConstantTexture(RGBColor(0.f, .7f, 0.f));
		bluetex = new ConstantTexture(RGBColor(0.f, 0.f, 0.7f));
		blacktex = new ConstantTexture(RGBColor::rep(0.0f));
		whitetex = new ConstantTexture(RGBColor::rep(1.0f));
	}

}

void a7prepMaterials1(Material** materials) {
	materials[0] = new LambertianMaterial(blacktex, whitetex);
	materials[1] = new LambertianMaterial(blacktex, redtex);
	materials[2] = new LambertianMaterial(blacktex, greentex);

	materials[3] = new LambertianMaterial(blacktex, whitetex);

	materials[4] = new LambertianMaterial(blacktex, whitetex);
}

void a7prepMaterials2(Material** materials) {
	materials[0] = new LambertianMaterial(blacktex, whitetex);
	materials[1] = new LambertianMaterial(blacktex, redtex);
	materials[2] = new LambertianMaterial(blacktex, greentex);
	//materials[3] = new PhongMaterial(whitetex, 10.0f);
	materials[3] = new CookTorranceMaterial(whitetex, 2.485, 3.433, 15.f, 10.f);//Cook-torrance material
	materials[4] = new MirrorMaterial(0.0f, 0.0f);
}


void a7prepMaterials3(Material** materials) {
	materials[0] = new LambertianMaterial(blacktex, whitetex);
	materials[1] = new LambertianMaterial(blacktex, redtex);

	CombineMaterial* green = new CombineMaterial();
	green->add(new LambertianMaterial(blacktex, greentex), 0.5f);
	green->add(new PhongMaterial(whitetex, 2.0f), 0.5f);
	materials[2] = green;

	materials[3] = new MirrorMaterial(2.485, 3.433);

	MirrorMaterial* mirror = new MirrorMaterial(0.0f, 0.0f);
	PhongMaterial* phong = new PhongMaterial(whitetex, 10.0f);
	CombineMaterial* combined = new CombineMaterial();
	combined->add(materials[0],0.2f);
	combined->add(phong,0.62f);
	combined->add(mirror,0.18f);
	materials[4] = combined;
}



void a7renderCornellbox(float scale, const char* filename, Material** materials) {
	Image img(400, 400);
	World world;
	SimpleGroup* scene = new SimpleGroup();
	world.scene = scene;
	PerspectiveCamera cam(Point(278 * scale, 273 * scale, -800 * scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);



	Material* grey = materials[0];
	Material* leftWallMaterial = materials[1];
	Material* rightWallMaterial = materials[2];

	Material* sphereMaterial = materials[3];
	Material* floorMaterial = materials[4];

	scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, floorMaterial)); //floor
	scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, grey)); //ceiling
	scene->add(new Quad(Point(000.f, 000.f, 560.f)*scale, Vector(550.f, 000.f, 000.f)*scale, Vector(000.f, 550.f, 000.f)*scale, nullptr, grey)); //back wall
	scene->add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, nullptr, rightWallMaterial)); //right wall
	scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(000.f, -550.f, 000.f)*scale, nullptr, leftWallMaterial)); //left wall

	scene->add(new Sphere(Point(150.0f, 100.0f, 150.0f)*scale, 99.0f*scale, nullptr, sphereMaterial));

	//tall box
	makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, grey);

	//point light
	world.light.push_back(new PointLight(Point((278)*scale, 529.99f*scale, (279.5f)*scale), RGBColor::rep(150000.0f*scale*scale)));
	world.light.push_back(new PointLight(Point((278)*scale, 229.99f*scale, (-359.5f)*scale), RGBColor::rep(50000.0f*scale*scale)));

	world.light.push_back(new PointLight(Point(490 * scale, 159.99f*scale, 279.5f*scale), RGBColor(40000.0f*scale*scale, 0, 0)));
	world.light.push_back(new PointLight(Point(40 * scale, 159.99f*scale, 249.5f*scale), RGBColor(5000.0f*scale*scale, 30000.0f*scale*scale, 5000.0f*scale*scale)));





	RecursiveRayTracingIntegrator integrator(&world);
	Renderer engine(&cam, &integrator);
	engine.test_render2(img);
	img.writePNG(filename);
}

void a7prepMaterials4(Material** materials) {
	materials[3] = new  PhongMaterial(whitetex, 10.0f);
	materials[0] = new LambertianMaterial(bluetex, whitetex);
	materials[2] = new LambertianMaterial(blacktex, redtex);
	MirrorMaterial* mirror = new MirrorMaterial(0.0f, 0.0f);
	PhongMaterial* phong = new PhongMaterial(whitetex, 10.0f);
	CombineMaterial* combined = new CombineMaterial();
	combined->add(materials[2], 0.2f);
	combined->add(phong, 0.62f);
	combined->add(mirror, 0.18f);
	materials[2] = combined;

	materials[4] = new CookTorranceMaterial(whitetex, 2.485, 3.433, 10.f, 10.f);//Cook-torrance material
	materials[1] = new MirrorMaterial(0.0f, 0.0f);
}


void superRender(const char* filename, Material** materials) {
	Image img(1280, 1080);
	World world;
	SimpleGroup* scene = new SimpleGroup();
	world.scene = scene;
	Material* sphereMaterial = materials[3];
	scene->add(new Quad(Point(-2.5f, 2.5f, -0.5f), Vector(5.f, 0.f, 0.f), Vector(0.f, 0.f, 5.f), nullptr, materials[0]));
	scene->add(new Quad(Point(-2.5f, -2.5f, -0.5f), Vector(5.f, 0.f, 0.f), Vector(0.f, 5.f, 0.f), nullptr, materials[2]));
	scene->add(new Sphere(Point(1.f, 1.f, 0.f), 0.5, nullptr, materials[1]));
	scene->add(new Sphere(Point(-1.f, 1.f, 0.f), 0.5, nullptr, materials[0]));
	scene->add(new Sphere(Point(0.f, 2.f, 0.f), 0.5, nullptr, materials[3]));
	scene->add(new Sphere(Point(0.f, 0.f, 0.f), 0.5f, nullptr, materials[4]));
	world.light.push_back(new PointLight(Point(3.f, -3.f, 3.f), RGBColor(16.f, 8.f,8.f)));
	world.light.push_back(new PointLight(Point(-3.f, 0.f, 3.f), RGBColor(8.f, 8.f, 0)));
	world.light.push_back(new ProjectiveLight(Point(0.f, -3.f, 0.f), Vector(0.0f, 1.0f, 1.0f), pi / 4, 8.0f, RGBColor(128.f,0.f,0.f)));
	world.light.push_back(new ProjectiveLight(Point(-2.f, 0.f, 0.f), Vector(1.f, 1.0f, 0.f), pi / 8, 8.0f, RGBColor(4.f, 4.f, 0.f)));

	RecursiveRayTracingIntegrator integrator(&world);
	PerspectiveCamera cam(Point(0.f, -5.f, 3.f), Vector(0.f, 1.f, -0.5f), Vector(0.f, 0.f, 0.1f), pi / 8, pi / 6);
	Renderer engine(&cam, &integrator);
	engine.test_render2(img);
	img.writePNG(filename);
}

void a_materials() {
	Material** materials = new Material*[5];
	initTextures();
	a7prepMaterials1(materials);
	a7renderCornellbox(0.001f, "a5-1.png", materials);
	a7prepMaterials2(materials);
	a7renderCornellbox(0.001f, "a5-2.png", materials);
	a7prepMaterials3(materials);
	a7renderCornellbox(0.001f, "a5-3.png", materials);
	a7prepMaterials4(materials);
	superRender("a5-4.png",materials);
	delete[] materials;
}

