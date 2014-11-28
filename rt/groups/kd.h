#ifndef CG1RAYTRACER_GROUPS_KDTREE_HEADER
#define CG1RAYTRACER_GROUPS_KDTREE_HEADER
#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <stack>
#include <iostream>
#define ENTER 1
#define EXIT 2
#define eventType int
namespace rt {
	class KDTreeNode;
	class Event;
	class KDTree : public Group {
	public:
		KDTree();
		virtual BBox getBounds() const;
		virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
		virtual void rebuildIndex();
		virtual ~KDTree();
		virtual void add(Primitive* p);
		virtual void setMaterial(Material* m);
		virtual void setCoordMapper(CoordMapper* cm);
		float getSurfaceArea(Point &p1, Point &p2);
		std::pair<Point, Point> getBorderPoints(KDTreeNode * node, float boundingCoordinate);
		static bool compareEvents(Event & first, Event & second);
		virtual float KDTree::getArea() const { return -1; }
		virtual float KDTree::getIntersectionComplexity() const { return -1; }
		virtual Vector getNormalAtPoint(Point &p) const { return Vector(0, 0, 0); }
	private:
		std::vector< Primitive * > mPrimitives;
		BBox mBBox;
		KDTreeNode * rootNode;
	};
}
#endif 