#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>
#include <algorithm>
#include <rt\intersection.h>
#include <rt/world.h>
#include <core\color.h>
#include <rt\lights\light.h>
#include <rt\solids\solid.h>
#include <rt\materials\material.h>
#include <core\scalar.h>
namespace rt {

class World;
class Ray;
class RGBColor;

class RecursiveRayTracingIntegrator : public Integrator {
public:
	RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
	RGBColor getRadiance(const Ray& ray,int& depth) const;
	
};

}

#endif
