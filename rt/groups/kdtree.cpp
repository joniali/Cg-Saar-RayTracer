#include <rt\groups\kdtree.h>

namespace rt{

	class KDNode{
	public:
		KDNode * leftChild;
		KDNode * rightChild;
		int split;
		std::vector<Primitive * > kNPrimitives;
		BBox KDNBBox;
		bool leaf;



	};

	void KDTree::rebuildIndex()
	{
		std::stack<KDNode *> innerStack;

		cout << "size of thing" << kPrimitives.size() << endl;
		rootNode->KDNBBox = BBox(kBBox.min,kBBox.max);
		float lenZ = rootNode->KDNBBox.max.z - rootNode->KDNBBox.min.z;
		float lenY = rootNode->KDNBBox.max.y - rootNode->KDNBBox.min.y;
		float lenX = rootNode->KDNBBox.max.x - rootNode->KDNBBox.min.x;
		int i = 0;
		for each (Primitive *p in kPrimitives)
		{
			
			rootNode->kNPrimitives[i] = p;
			i++;
		}
		
		rootNode->split = 0 ? lenX > lenY &&lenX > lenZ : 1 ? lenY > lenX &&lenY > lenZ : 2;
		rootNode->leaf = false;
		innerStack.push(rootNode);


		while (true)
		{

			if (innerStack.size() == 0)
				break;
			
			
			KDNode *currentNode = innerStack.top();
			innerStack.pop();

			if (currentNode->kNPrimitives.size() <= 3)
			{
				currentNode->leaf = true;
				continue;
			}
			

			// calculate childern
			Point newCorner1, newCorner2;
			float splitPos;
			if (currentNode->split == 0)
			{
				newCorner1 = Point(currentNode->KDNBBox.max.x / 2, currentNode->KDNBBox.max.y, currentNode->KDNBBox.max.z);
				newCorner2 = Point(currentNode->KDNBBox.max.x / 2, currentNode->KDNBBox.min.y, currentNode->KDNBBox.min.z);
				splitPos = currentNode->KDNBBox.max.x / 2;
			}
			else if (currentNode->split == 1)
			{
				newCorner1 = Point(currentNode->KDNBBox.max.x, currentNode->KDNBBox.max.y / 2, currentNode->KDNBBox.max.z);
				newCorner2 = Point(currentNode->KDNBBox.min.x, currentNode->KDNBBox.max.y / 2, currentNode->KDNBBox.min.z);
				splitPos = currentNode->KDNBBox.max.y / 2;
			}
			else
			{
				newCorner1 = Point(currentNode->KDNBBox.max.x, currentNode->KDNBBox.max.y, currentNode->KDNBBox.max.z / 2);
				newCorner2 = Point(currentNode->KDNBBox.min.x, currentNode->KDNBBox.min.y, currentNode->KDNBBox.max.z / 2);
				splitPos = currentNode->KDNBBox.max.z / 2;
			}

		
			currentNode->leftChild->KDNBBox = BBox(currentNode->KDNBBox.min, newCorner1);
			currentNode->rightChild->KDNBBox = BBox(newCorner2, currentNode->KDNBBox.max);

			currentNode->leaf = false;
			currentNode->leftChild->leaf = true;
			currentNode->rightChild->leaf = true;

			currentNode->leftChild->split = (currentNode->split + 1) % 3;
			currentNode->rightChild->split = (currentNode->split + 1) % 3;

			// now divide primitive
			float minPos, maxPos;
			for (int i = 0; i < kPrimitives.size(); i++)
			{
				if (currentNode->split == 0)
				{
					maxPos=kPrimitives[i]->getBounds().max.x;
					minPos = kPrimitives[i]->getBounds().min.x;

				}
				else if (currentNode->split == 1)
				{
					maxPos = kPrimitives[i]->getBounds().max.y;
					minPos = kPrimitives[i]->getBounds().min.y;

				}
				else {
					maxPos = kPrimitives[i]->getBounds().max.z;
					minPos = kPrimitives[i]->getBounds().min.z;

				}

				if (maxPos > splitPos)
				{
					currentNode->rightChild->kNPrimitives.push_back(kPrimitives[i]);
				}
				if (minPos < splitPos)
				{
					currentNode->leftChild->kNPrimitives.push_back(kPrimitives[i]);
				}
			}


			innerStack.push(currentNode->leftChild);
			innerStack.push(currentNode->rightChild);

		}



	}
	BBox KDTree::getBounds() const
	{
		return kBBox;
	}
	Intersection KDTree::intersect(const Ray& ray, float previousBestDistance) const
	{
		float t0, t1;
		std::pair<float, float>(t0, t1)=rootNode->KDNBBox.intersect(ray);
		if (t0>t1)
		{
			return Intersection::failure();
		}

		std::stack<KDNode *> innerStack;
		innerStack.push(rootNode->leftChild);
		innerStack.push(rootNode->rightChild);
		float previousBestDist = previousBestDistance;
		Intersection ret = Intersection::failure();
		while(!innerStack.empty())
		{

			KDNode *currentNode = innerStack.top();
			innerStack.pop();
			
			float t0, t1;
			std::pair<float, float>(t0, t1) = currentNode->KDNBBox.intersect(ray);
			
			if (t0 > t1) continue;

			if (currentNode->leaf)
			{
				for each (Primitive *p in currentNode->kNPrimitives)
				{
					float t0, t1;
					std::pair<float, float>(t0, t1)=p->getBounds().intersect(ray);
					if (t0 > t1) continue;
					
					Intersection tempinter = p->intersect(ray, previousBestDist);

					if (tempinter)
					{
						ret = tempinter;
						previousBestDist = tempinter.distance;
					}

				}
			}

			std::pair<float, float>(t0, t1) = currentNode->leftChild->KDNBBox.intersect(ray);
			if (t0 < t1) innerStack.push(currentNode->leftChild);

			std::pair<float, float>(t0, t1) = currentNode->rightChild->KDNBBox.intersect(ray);
			if (t0 < t1) innerStack.push(currentNode->rightChild);
			






		}

		return ret;
	}
	void KDTree::add(Primitive* p)
	{
		BBox b = p->getBounds();
		kPrimitives.push_back(p);
		kBBox.extend(p->getBounds());
		//cout << "size of thing" << kPrimitives.size()<<endl;
	}
	void KDTree::setMaterial(Material* m)
	{}
	void KDTree::setCoordMapper(CoordMapper* cm)
	{}
	KDTree::~KDTree()
	{
	}
}