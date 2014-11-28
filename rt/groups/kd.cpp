#define SAH

#include "kd.h"

#define eventIter std::vector<Event>::iterator

namespace rt {

	class Event
	{
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

	class KDTreeNode
	{
	public:
		std::vector<Primitive * > mPrimitives;
		std::vector<Event> mEvents;
		BBox mBBox;
		KDTreeNode * leftChild;
		KDTreeNode * rightChild;

		bool isLeaf;	// true if the node is leaf, false if it is an inner node of the kd tree

		int splitAxis; // 0 for X, 1 for Y, 2 for Z

		int depth;

		float getMinInSplitAxis()
		{
			if (splitAxis == 0) return mBBox.min.x;
			if (splitAxis == 1) return mBBox.min.y;
			if (splitAxis == 2) return mBBox.min.z;
		}

		float getMaxInSplitAxis()
		{
			if (splitAxis == 0) return mBBox.max.x;
			if (splitAxis == 1) return mBBox.max.y;
			if (splitAxis == 2) return mBBox.max.z;
		}
	};

	float KDTree::getSurfaceArea(Point &p1, Point &p2)
	{
		float a = abs(p1.x - p2.x);
		float b = abs(p1.y - p2.y);
		float c = abs(p1.z - p2.z);

		return 2 * (a*b + b*c + a*c);
	}

	bool KDTree::compareEvents(Event & first, Event & second) { return (first.mCoordinate < second.mCoordinate); }

	// returns pair<firstMax, secondMin>
	std::pair<Point, Point> KDTree::getBorderPoints(KDTreeNode * node, float boundingCoordinate)
	{
		// compute the bounding box of the tree node
		float firstMaxX = node->mBBox.max.x;
		float firstMaxY = node->mBBox.max.y;
		float firstMaxZ = node->mBBox.max.z;

		float secondMinX = node->mBBox.min.x;
		float secondMinY = node->mBBox.min.y;
		float secondMinZ = node->mBBox.min.z;

		if (node->splitAxis == 0)
		{
			firstMaxX = boundingCoordinate;
			secondMinX = boundingCoordinate;
		}

		if (node->splitAxis == 1)
		{
			firstMaxY = boundingCoordinate;
			secondMinY = boundingCoordinate;
		}

		if (node->splitAxis == 2)
		{
			firstMaxZ = boundingCoordinate;
			secondMinZ = boundingCoordinate;
		}


		Point firstMaxP = Point(firstMaxX, firstMaxY, firstMaxZ);
		Point secondMinP = Point(secondMinX, secondMinY, secondMinZ);

		std::pair<Point, Point> p;
		p = std::make_pair(firstMaxP, secondMinP);
		return p;

	}

	KDTree::KDTree() { }

	BBox KDTree::getBounds() const { return BBox(); }

	Intersection KDTree::intersect(const Ray& ray, float previousBestDistance) const
	{
		std::stack<KDTreeNode * > mStack;
		mStack.push(rootNode);

		std::pair<float, float> intersections = rootNode->mBBox.intersect(ray);
		if (intersections.first > intersections.second) return Intersection::failure();

		float bestT = previousBestDistance;
		Intersection bestIntersection;
		bool anyIntersection = false;

		while (!mStack.empty())
		{
			KDTreeNode * node = mStack.top();
			mStack.pop();

			if (node->isLeaf) // do intersections
			{
				for (std::vector<Primitive * >::iterator it = node->mPrimitives.begin(); it != node->mPrimitives.end(); ++it)
				{
					Primitive * p = *it;
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
				KDTreeNode * left = node->leftChild;
				KDTreeNode * right = node->rightChild;

				std::pair<float, float> intersections = left->mBBox.intersect(ray);
				if (intersections.first < intersections.second) mStack.push(left);

				intersections = right->mBBox.intersect(ray);
				if (intersections.first < intersections.second) mStack.push(right);
			}
		}

		if (anyIntersection) return bestIntersection;

		return Intersection::failure();

	}


#ifdef SAH

	void KDTree::rebuildIndex()
	{
		std::stack<KDTreeNode * > mStack;

		float depthTreshold = 100;

		KDTreeNode * rootNode = new KDTreeNode();
		rootNode->mBBox = BBox(mBBox.min, mBBox.max);
		rootNode->mPrimitives = this->mPrimitives;
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

			KDTreeNode * node = mStack.top();
			mStack.pop();

			int wholeNodeCount = node->mPrimitives.size();

			if (node->depth > depthTreshold) continue;
			if (node->mPrimitives.size() <= 3) continue;

			// recognize events in the mPrimitives and put them into node->mEvents			
			for (std::vector < Primitive * > ::iterator it = node->mPrimitives.begin(); it != node->mPrimitives.end(); ++it)
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

			// sort events so that the time complexity of the iteration equals nlogn
			std::sort(node->mEvents.begin(), node->mEvents.end(), &rt::KDTree::compareEvents);

			float wholeNodeArea = getSurfaceArea(node->mBBox.min, node->mBBox.max);

			int enteredSolids = 0;
			int leftSolids = 0;

			float minimalCost = FLT_MAX;
			float minimalCostCoordinate = -1;
			bool splitDone = false;

			// iterate over all events (begin and end of primitives) in the vector held by the node
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

				Point firstMinP = node->mBBox.min;
				Point firstMaxP = pair.first;

				Point secondMinP = pair.second;
				Point secondMaxP = node->mBBox.max;

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

			Point firstMinP = node->mBBox.min;
			Point firstMaxP = pair.first;

			Point secondMinP = pair.second;
			Point secondMaxP = node->mBBox.max;

			KDTreeNode * left = new KDTreeNode();
			KDTreeNode * right = new KDTreeNode();

			node->leftChild = left;
			node->rightChild = right;

			node->isLeaf = false;
			left->isLeaf = true;
			right->isLeaf = true;

			left->mBBox = BBox(firstMinP, firstMaxP);
			right->mBBox = BBox(secondMinP, secondMaxP);

			left->depth = node->depth + 1;
			right->depth = node->depth + 1;

			left->splitAxis = (node->splitAxis + 1) % 3;
			right->splitAxis = (node->splitAxis + 1) % 3;

			mStack.push(left);
			mStack.push(right);

			// divide primitives from node to left child and right child

			for (std::vector<Primitive * >::iterator it = node->mPrimitives.begin(); it != node->mPrimitives.end(); ++it)
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
					left->mPrimitives.push_back(p);

				if (maxCoord > minimalCostCoordinate)
					right->mPrimitives.push_back(p);
			}

			//std::cout << left->mPrimitives.size() << " | " <<  right->mPrimitives.size() << std::endl;
		}

	}

#endif

#ifndef SAH

	void KDTree::rebuildIndex()
	{
		std::stack<KDTreeNode * > mStack;

		float depthTreshold = 20;

		int wholeNodeCount = mPrimitives.size();

		KDTreeNode * rootNode = new KDTreeNode();
		rootNode->mBBox = BBox(mBBox.min, mBBox.max);
		rootNode->mPrimitives = this->mPrimitives;
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

			KDTreeNode * node = mStack.top();
			mStack.pop();

			if (node->depth >= depthTreshold) continue;

			if (node->mPrimitives.size() <= 3) continue;

			float splitCoordinate;

			if (node->splitAxis == 0)
				splitCoordinate = (node->mBBox.min.x + node->mBBox.max.x) / 2;

			if (node->splitAxis == 1)
				splitCoordinate = (node->mBBox.min.y + node->mBBox.max.y) / 2;

			if (node->splitAxis == 2)
				splitCoordinate = (node->mBBox.min.z + node->mBBox.max.z) / 2;

			std::pair<Point, Point> pair = getBorderPoints(node, splitCoordinate);

			Point firstMinP = node->mBBox.min;
			Point firstMaxP = pair.first;

			Point secondMinP = pair.second;
			Point secondMaxP = node->mBBox.max;

			KDTreeNode * left = new KDTreeNode();
			KDTreeNode * right = new KDTreeNode();

			node->leftChild = left;
			node->rightChild = right;

			node->isLeaf = false;
			left->isLeaf = true;
			right->isLeaf = true;

			left->mBBox = BBox(firstMinP, firstMaxP);
			right->mBBox = BBox(secondMinP, secondMaxP);

			left->depth = node->depth + 1;
			right->depth = node->depth + 1;

			left->splitAxis = (node->splitAxis + 1) % 3;
			right->splitAxis = (node->splitAxis + 1) % 3;

			mStack.push(left);
			mStack.push(right);

			// divide primitives from node to left child and right child

			for (std::vector<Primitive * >::iterator it = node->mPrimitives.begin(); it != node->mPrimitives.end(); ++it)
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
				if (minCoord < splitCoordinate)
					left->mPrimitives.push_back(p);

				if (maxCoord > splitCoordinate)
					right->mPrimitives.push_back(p);
			}

			/*	std::cout << left->mPrimitives.size() << " | " <<  right->mPrimitives.size() << std::endl;
			std::cout << "(" << node->mBBox.min.x << " | " << node->mBBox.min.y << " | " << node->mBBox.min.z << " ) " << "(" << node->mBBox.max.x << " | " << node->mBBox.max.y << " | " << node->mBBox.max.z << " ) " << std::endl;
			std::cout << "(" << left->mBBox.min.x << " | " << left->mBBox.min.y << " | " << left->mBBox.min.z << " ) " << "(" << left->mBBox.max.x << " | " << left->mBBox.max.y << " | " << left->mBBox.max.z << " ) " << std::endl;
			std::cout << "(" << right->mBBox.min.x << " | " << right->mBBox.min.y << " | " << right->mBBox.min.z << " ) " << "(" << right->mBBox.max.x << " | " << right->mBBox.max.y << " | " << right->mBBox.max.z << " ) " << std::endl;*/

		}

		/*float value;
		std::cin >> value ;*/
	}
#endif

	KDTree::~KDTree()
	{

	}

	void KDTree::add(Primitive* p)
	{
		BBox b = p->getBounds();
		mPrimitives.push_back(p);
		mBBox.extend(p->getBounds());
	}

	void KDTree::setMaterial(Material* m) { }

	void KDTree::setCoordMapper(CoordMapper* cm) { }
}