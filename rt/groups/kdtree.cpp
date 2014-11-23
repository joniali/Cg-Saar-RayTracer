#define nSAH

#include "kdTree.h"primitivesL

#define eventIter std::vector<Event>::iterator

namespace rt {

	
	class Event{
		public:
			Event() {};
			Primitive * mP;
			eventType mType; // true if enter, false if exit
			float mCoordinate;

			Event(Primitive * aP, eventType aType, float aCoordinate)
			{
				mP = aP;
				mType = aType;
				mCoordinate = aCoordinate;
			}
		};

	class KDNode
	{
	public:
		std::vector<Primitive * > primitivesL;
		std::vector<Event> mEvents;
		BBox minBox;
		KDNode * childLeft;
		KDNode * childRight;
		float getMinInSplitAxis()
		{
			if (splitAxis == 0) return minBox.min.x;
			if (splitAxis == 1) return minBox.min.y;
			if (splitAxis == 2) return minBox.min.z;
		}

		float getMaxInSplitAxis()
		{
			if (splitAxis == 0) return minBox.max.x;
			if (splitAxis == 1) return minBox.max.y;
			if (splitAxis == 2) return minBox.max.z;
		}

		bool isLeaf;	

		int splitAxis;

		int depth;


	};

	float KDTree::getSurfaceArea(Point &p1, Point &p2)
	{
		float a = abs(p1.x - p2.x);
		float b = abs(p1.y - p2.y);
		float c = abs(p1.z - p2.z);

		return 2 * (a*b + b*c + a*c);
	}

	
	std::pair<Point, Point> KDTree::getBorderPoints(KDNode * node, float boundingCoordinate)
	{

		float maxX1 = node->minBox.max.x;
		float maxY1 = node->minBox.max.y;
		float maxZ1 = node->minBox.max.z;

		float minX2 = node->minBox.min.x;
		float minY2 = node->minBox.min.y;
		float minZ2 = node->minBox.min.z;

		if (node->splitAxis == 0)
		{
			maxX1 = boundingCoordinate;
			minX2 = boundingCoordinate;
		}

		if (node->splitAxis == 1)
		{
			maxY1 = boundingCoordinate;
			minY2 = boundingCoordinate;
		}

		if (node->splitAxis == 2)
		{
			maxZ1 = boundingCoordinate;
			minZ2 = boundingCoordinate;
		}

		
		Point firstMaxP = Point(maxX1, maxY1, maxZ1);
		Point secondMinP = Point(minX2, minY2, minZ2);

		std::pair<Point, Point> p; 
		p = std::make_pair(firstMaxP, secondMinP);
		return p;
		
	}

	
	bool KDTree::compareEvents(Event & first, Event & second) { return (first.mCoordinate < second.mCoordinate); }
	BBox KDTree::getBounds() const { return BBox(); }

	Intersection KDTree::intersect(const Ray& ray, float previousBestDistance) const 
	{ 
		std::stack<KDNode * > mStack;
		mStack.push(rootNode);

		std::pair<float, float> intersections = rootNode->minBox.intersect(ray);
		if (intersections.first > intersections.second) return Intersection::failure();

		float bestT = previousBestDistance;
		Intersection bestIntersection;
		bool anyIntersection = false;

		while (! mStack.empty())
		{
			KDNode * node = mStack.top();
			mStack.pop();

			if (node->isLeaf) 
			{
				for(std::vector<Primitive * >::iterator it = node->primitivesL.begin(); it != node->primitivesL.end(); ++it)
				{
					Primitive * p = * it;
					std::pair<float, float> intersections = p->getBounds().intersect(ray);
					if (intersections.first > intersections.second) continue;

					Intersection isect = p->intersect(ray, bestT);
					if (isect)
					{
						if (p->getBounds().pointIsInBBox(isect.hitPoint()))
						{
							bestT = isect.distance;
							bestIntersection = isect;
							anyIntersection = true;
						}
					}
				}
			}
			else	// go deeper in the KDTree
			{
				KDNode * left = node->childLeft;
				KDNode * right = node->childRight;

				std::pair<float, float> intersections = left->minBox.intersect(ray);
				if (intersections.first < intersections.second) mStack.push(left);
				
				intersections = right->minBox.intersect(ray);
				if (intersections.first < intersections.second) mStack.push(right);
			}
		}

		if (anyIntersection) return bestIntersection;
			
		return Intersection::failure();
		
	}

#ifdef SAH

	void KDTree::rebuildIndex()
	{
		std::stack<KDNode * > mStack;

		float depthTreshold = 100;

		KDNode * rootNode = new KDNode();
		rootNode->minBox = BBox(minBox.min, minBox.max);
		rootNode->primitivesL = this->primitivesL;
		rootNode->splitAxis = 0;
		rootNode->depth = 0;

		this->rootNode = rootNode;

		mStack.push(rootNode);

		bool run = true;

		while (run)
		{
			if (mStack.empty())
			{
				run = false;
				std::cout << "Stack empty" << std::endl;
				continue;
			}

			KDNode * node = mStack.top();
			mStack.pop();

			int wholeNodeCount = node->primitivesL.size();

			if (node->depth > depthTreshold) continue;
			if (node->primitivesL.size() <= 3) continue;

			// recognize events in the primitivesL and put them into node->mEvents			
			for (std::vector < Primitive * > ::iterator it = node->primitivesL.begin(); it != node->primitivesL.end(); ++it)
			{
				Primitive * p = *it;
				Event enterE;
				Event exitE;

				if (node->splitAxis == 0)
				{
					enterE = Event(p, ENTER, p->getBounds().min.x);
					exitE = Event(p, EXIT, p->getBounds().max.x);
				}

				if (node->splitAxis == 1)
				{
					enterE = Event(p, ENTER, p->getBounds().min.y);
					exitE = Event(p, EXIT, p->getBounds().max.y);
				}

				if (node->splitAxis == 2)
				{
					enterE = Event(p, ENTER, p->getBounds().min.z);
					exitE = Event(p, EXIT, p->getBounds().max.z);
				}

				node->mEvents.push_back(enterE);
				node->mEvents.push_back(exitE);
			}

			
			std::sort(node->mEvents.begin(), node->mEvents.end(), &rt::KDTree::compareEvents);

			float wholeNodeArea = getSurfaceArea(node->minBox.min, node->minBox.max);

			int enteredSolids = 0;
			int leftSolids = 0;

			float minimalCost = FLT_MAX;
			float minimalCostCoordinate = -1;
			bool splitDone = false;

			for (eventIter it = node->mEvents.begin(); it != node->mEvents.end(); ++it)
			{
				Event ev = *it;
				int firstHalfCount;
				int secondHalfCount;

				if (ev.mType == ENTER) enteredSolids++;
				else leftSolids++;


				firstHalfCount = enteredSolids;
				secondHalfCount = wholeNodeCount - leftSolids;

				if (ev.mCoordinate < node->getMinInSplitAxis()) continue;
				if (ev.mCoordinate > node->getMaxInSplitAxis()) continue;

				std::pair<Point, Point> pair = getBorderPoints(node, ev.mCoordinate);

				Point firstMinP = node->minBox.min;
				Point firstMaxP = pair.first;

				Point secondMinP = pair.second;
				Point secondMaxP = node->minBox.max;

				float firstCost = firstHalfCount * getSurfaceArea(firstMinP, firstMaxP) / wholeNodeArea;
				float secondCost = secondHalfCount * getSurfaceArea(secondMinP, secondMaxP) / wholeNodeArea;
				float totalNodeCost = firstCost + secondCost;

				if (totalNodeCost < minimalCost)
				{
					minimalCost = totalNodeCost;
					minimalCostCoordinate = ev.mCoordinate;
					splitDone = true;
				}

			} // Eof For-loop

			// now split the node into two nodes wrt to the minimalCostCoordinate

			if (!splitDone) continue;
			if (minimalCost > wholeNodeCount) continue;

			std::pair<Point, Point> pair = getBorderPoints(node, minimalCostCoordinate);

			Point firstMinP = node->minBox.min;
			Point firstMaxP = pair.first;

			Point secondMinP = pair.second;
			Point secondMaxP = node->minBox.max;

			KDNode * left = new KDNode();
			KDNode * right = new KDNode();

			node->childLeft = left;
			node->childRight = right;

			node->isLeaf = false;
			left->isLeaf = true;
			right->isLeaf = true;

			left->minBox = BBox(firstMinP, firstMaxP);
			right->minBox = BBox(secondMinP, secondMaxP);

			left->depth = node->depth + 1;
			right->depth = node->depth + 1;

			left->splitAxis = (node->splitAxis + 1) % 3;
			right->splitAxis = (node->splitAxis + 1) % 3;

			mStack.push(left);
			mStack.push(right);

			// divide primitives from node to left child and right child

			for (std::vector<Primitive * >::iterator it = node->primitivesL.begin(); it != node->primitivesL.end(); ++it)
			{
				Primitive * p = *it;

				float minCoord;
				float maxCoord;

				if (node->splitAxis == 0)
				{
					minCoord = p->getBounds().min.x;
					maxCoord = p->getBounds().max.x;
				}

				if (node->splitAxis == 1)
				{
					minCoord = p->getBounds().min.y;
					maxCoord = p->getBounds().max.y;
				}

				if (node->splitAxis == 2)
				{
					minCoord = p->getBounds().min.z;
					maxCoord = p->getBounds().max.z;
				}

				// the division into left and right is non-exclusive
				if (minCoord < minimalCostCoordinate)
					left->primitivesL.push_back(p);

				if (maxCoord > minimalCostCoordinate)
					right->primitivesL.push_back(p);
			}

			//std::cout << left->primitivesL.size() << " | " <<  right->primitivesL.size() << std::endl;
		}

	}

#endif

#ifndef SAH

	void KDTree::rebuildIndex()
	{
		std::stack<KDNode * > mStack;

		float depthLevel = 20;

		int wholeNodeCount = primitivesL.size();

		KDNode * rootNode = new KDNode();
		rootNode->minBox = BBox(minBox.min, minBox.max);
		rootNode->primitivesL = this->primitivesL;
		rootNode->splitAxis = 0;
		rootNode->depth = 0;
		this->rootNode = rootNode;

		mStack.push(rootNode);
		
		bool run = true;

		while (run)
		{
			if (mStack.empty())
			{
				run = false;
				break;
			}

			KDNode * node = mStack.top();
			mStack.pop();

			if (node->depth >= depthLevel) continue;

			if (node->primitivesL.size() <= 3) continue;

			float splitCoordinate;

			if (node->splitAxis == 0)
				splitCoordinate = (node->minBox.min.x + node->minBox.max.x) / 2;
			
			if (node->splitAxis == 1)
				splitCoordinate = (node->minBox.min.y + node->minBox.max.y) / 2;
			
			if (node->splitAxis == 2)
				splitCoordinate = (node->minBox.min.z + node->minBox.max.z) / 2;
					
			std::pair<Point, Point> pair = getBorderPoints(node, splitCoordinate);

			Point firstMinP = node->minBox.min;
			Point firstMaxP = pair.first;

			Point secondMinP = pair.second;
			Point secondMaxP = node->minBox.max;

			KDNode * left = new KDNode();
			KDNode * right = new KDNode();

			node->childLeft = left;
			node->childRight = right;

			node->isLeaf = false;
			left->isLeaf = true;
			right->isLeaf = true;

			left->minBox = BBox(firstMinP, firstMaxP);
			right->minBox = BBox(secondMinP, secondMaxP);

			left->depth = node->depth + 1;
			right->depth = node->depth + 1;

			left->splitAxis = (node->splitAxis + 1) % 3;
			right->splitAxis = (node->splitAxis + 1) % 3;

			mStack.push(left);
			mStack.push(right);

			for (std::vector<Primitive * >::iterator it = node->primitivesL.begin(); it != node->primitivesL.end(); ++it)
			{
				Primitive * p = *it;

				float minCoord;
				float maxCoord;

				if (node->splitAxis == 0)
				{
					minCoord = p->getBounds().min.x;
					maxCoord = p->getBounds().max.x;
				}

				if (node->splitAxis == 1)
				{
					minCoord = p->getBounds().min.y;
					maxCoord = p->getBounds().max.y;
				}

				if (node->splitAxis == 2)
				{
					minCoord = p->getBounds().min.z;
					maxCoord = p->getBounds().max.z;
				}
				

				if (minCoord < splitCoordinate)
					left->primitivesL.push_back(p);

				if (maxCoord > splitCoordinate)
					right->primitivesL.push_back(p);
			}

		
		}

	}
#endif

	void KDTree::add(Primitive* p)
	{
		BBox b = p->getBounds();
		primitivesL.push_back(p);
		minBox.extend(p->getBounds());
	}

	void KDTree::setMaterial(Material* m) {
		for each (Primitive *p in primitivesL)
		{
			p->setMaterial(m);
		}
	}

	void KDTree::setCoordMapper(CoordMapper* cm) { }
}