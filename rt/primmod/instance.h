#ifndef CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER
#define CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER

#include <rt/primitive.h>
#include <core/Matrix.h>
#include <stack>
#include <math.h>  
#include <rt\bbox.h>
namespace rt {

class Instance : public Primitive {
public:

	Instance(Primitive* content);
	Primitive* content();

	void reset(); //reset transformation back to identity
	void translate(const Vector& t);
	void rotate(const Vector& axis, float angle);
	void scale(float scale);
	void scale(const Vector& scale);
	void changeBBox(Matrix &t);
	virtual BBox getBounds() const;
	virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual void setMaterial(Material* m){ material = m; }
	virtual void setCoordMapper(CoordMapper* cm){ coodMapper = cm; }
	Matrix transformations;
	Matrix inverseTransformation;
	Primitive *icontent;
	Material* material;
	CoordMapper* coodMapper;
	BBox tranformedBBox;
};

}

#endif