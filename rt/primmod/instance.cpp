#include <rt/primmod/instance.h>

namespace rt
{


	Instance::Instance(Primitive* content)
	{
		icontent = content;
		tranformedBBox=content->getBounds();
		transformations = Matrix::identity();
		inverseTransformation = Matrix::identity();

	}
	Primitive* Instance::content()
	{
		return icontent;
	}
	void Instance::reset()
	{
		transformations = Matrix::identity();
		inverseTransformation = Matrix::identity();

	}
	void Instance::translate(const Vector& t)
	{
		Float4 r1(1.0, 0.0, 0.0, t.x);
		Float4 r2(0.0, 1.0, 0.0, t.y);
		Float4 r3(0.0, 0.0, 1.0, t.z);
		Float4 r4(0.0, 0.0, 0.0, 1.0);
		transformations = product(Matrix(r1, r2, r3, r4), transformations);
		inverseTransformation = transformations.invert();
		changeBBox(Matrix(r1, r2, r3, r4));
	}
	void Instance::scale(float scale)
	{
		Float4 r1(scale, 0.0, 0.0, 0.0);
		Float4 r2(0.0,scale, 0.0, 0.0);
		Float4 r3(0.0, 0.0, scale, 0.0);
		Float4 r4(0.0, 0.0, 0.0, 1.0);
		transformations = product(Matrix(r1, r2, r3, r4), transformations);
		inverseTransformation = transformations.invert();
		changeBBox(Matrix(r1, r2, r3, r4));

	}
	void Instance::scale(const Vector& scale)
	{
		Float4 r1(scale.x, 0.0, 0.0, 0.0);
		Float4 r2(0.0, scale.y, 0.0, 0.0);
		Float4 r3(0.0, 0.0, scale.z, 0.0);
		Float4 r4(0.0, 0.0, 0.0, 1.0);
		transformations = product(Matrix(r1, r2, r3, r4), transformations);
		inverseTransformation = transformations.invert();
		changeBBox(Matrix(r1, r2, r3, r4));

	}
	void Instance::rotate(const Vector& axis, float angle)
	{
		float cosTerm = cos(angle);
		float sineTerm = sin(angle);
		Float4 r1(cosTerm + axis.x*(1 - cosTerm), axis.x*axis.y*(1 - cosTerm) - axis.z*sineTerm, axis.x*axis.z*(1 - cosTerm) - axis.y*sineTerm, 0.0);
		Float4 r2(axis.z*sineTerm + axis.y*axis.x*(1 - cosTerm), axis.y*axis.y*(1- cosTerm) - cosTerm, axis.y*axis.z*(1 - cosTerm) - axis.x*sineTerm, 0.0);
		Float4 r3(axis.y*sineTerm + axis.z*axis.x*(1 - cosTerm), axis.z*axis.y*(1 - cosTerm) - axis.x*sineTerm, axis.z*axis.z*(1 - cosTerm) - cosTerm, 0.0);
		Float4 r4(0.0, 0.0, 0.0, 1.0);
		transformations = product(Matrix(r1, r2, r3, r4), transformations);
		inverseTransformation = transformations.invert();
		changeBBox(Matrix(r1, r2, r3, r4));

	
	}
	BBox Instance::getBounds() const
	{
		return tranformedBBox;
	}
	void Instance::changeBBox(Matrix &t)
	{
		Float4 points[8];

		points[0] = Float4(tranformedBBox.min);
		points[1] = Float4(tranformedBBox.min.x, tranformedBBox.min.y, tranformedBBox.max.z, 0);
		points[2] = Float4(tranformedBBox.min.x, tranformedBBox.max.y, tranformedBBox.min.z, 0);
		points[3] = Float4(tranformedBBox.min.x, tranformedBBox.max.y, tranformedBBox.max.z, 0);
		points[4] = Float4(tranformedBBox.max.x, tranformedBBox.min.y, tranformedBBox.min.z, 0);
		points[5] = Float4(tranformedBBox.max.x, tranformedBBox.min.y, tranformedBBox.max.z, 0);
		points[6] = Float4(tranformedBBox.max.x, tranformedBBox.max.y, tranformedBBox.min.z, 0);
		points[7] = Float4(tranformedBBox.max.x, tranformedBBox.max.y, tranformedBBox.max.z, 0);
		Float4 transPoints[8];
		Matrix invt = t.invert();
		int i = 0;
		for each (Float4 p in points)
		{
			transPoints[i] = t.invert()*p;
			i++;
		}
		Point min = Point(points[0]);
		Point max = Point(points[0]);

		for (int i = 0; i < 8; ++i)
		{
			if (min.x > points[i].x) min.x = points[i].x;
			if (min.y > points[i].y) min.y = points[i].y;
			if (min.z > points[i].z) min.z = points[i].z;

			if (max.x < points[i].x) max.x = points[i].x;
			if (max.y < points[i].y) max.y = points[i].y;
			if (max.z < points[i].z) max.z = points[i].z;
		}

		tranformedBBox = BBox(min, max);
	}
	Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const
	{
		Point newOrigin=Point(inverseTransformation*Float4(ray.o));
		Vector newDirection = Vector(inverseTransformation*Float4(ray.d));
		Ray newRay(newOrigin, newDirection.normalize());
		float factor = newDirection.length();
		Intersection intersection = icontent->intersect(newRay,previousBestDistance * factor);
	
		if (intersection)
		{
			
				return Intersection(intersection.distance, ray, intersection.solid, inverseTransformation.transpose()*intersection.normal(), intersection.local());
			
		}
		return Intersection::failure();

	}

}