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
		KDNode *rootNode = new KDNode();
		cout << "Number of elements" << kPrimitives.size() << endl;
		if (kPrimitives.size() == 0)
			return;
		rootNode->KDNBBox = BBox(kBBox.min,kBBox.max);
		float lenZ = rootNode->KDNBBox.max.z - rootNode->KDNBBox.min.z;
		
		float lenY = rootNode->KDNBBox.max.y - rootNode->KDNBBox.min.y;
		float lenX = rootNode->KDNBBox.max.x - rootNode->KDNBBox.min.x;
		
		rootNode->kNPrimitives = kPrimitives;
		/*for each (Primitive *p in kPrimitives)
		{
			
			rootNode->kNPrimitives[i] = p;
			i++;
		}*/
	
		rootNode->split = 0;//lenX > lenY && lenX > lenZ ? 0 : lenY > lenX &&lenY > lenZ ? 1 : 2;
		cout << "split axis" << rootNode->split << endl;
		rootNode->leaf = false;
		innerStack.push(rootNode);
		krootNode = rootNode;

		while (true)
		{

			if (innerStack.size() == 0)
				break;
			
			
			KDNode *currentNode = innerStack.top();
			innerStack.pop();

			if (currentNode->kNPrimitives.size() <= 3)
			{
				//currentNode->leaf = true;
				continue;
			}
			

			// calculate childern
			Point newCorner1, newCorner2;
			float splitPos;
			if (currentNode->split == 0)
			{
				newCorner1 = Point((currentNode->KDNBBox.min.x+currentNode->KDNBBox.max.x )/ 2, currentNode->KDNBBox.max.y, currentNode->KDNBBox.max.z);
				newCorner2 = Point((currentNode->KDNBBox.min.x+currentNode->KDNBBox.max.x) / 2, currentNode->KDNBBox.min.y, currentNode->KDNBBox.min.z);
				splitPos = (currentNode->KDNBBox.min.x + currentNode->KDNBBox.max.x) / 2;
			}
			else if (currentNode->split == 1)
			{
				newCorner1 = Point(currentNode->KDNBBox.max.x, (currentNode->KDNBBox.min.y+currentNode->KDNBBox.max.y) / 2, currentNode->KDNBBox.max.z);
				newCorner2 = Point(currentNode->KDNBBox.min.x, (currentNode->KDNBBox.min.y + currentNode->KDNBBox.max.y) / 2, currentNode->KDNBBox.min.z);
				splitPos = (currentNode->KDNBBox.min.y + currentNode->KDNBBox.max.y) / 2;
			}
			else
			{
				newCorner1 = Point(currentNode->KDNBBox.max.x, currentNode->KDNBBox.max.y, (currentNode->KDNBBox.min.z + currentNode->KDNBBox.max.z) / 2);
				newCorner2 = Point(currentNode->KDNBBox.min.x, currentNode->KDNBBox.min.y, (currentNode->KDNBBox.min.z + currentNode->KDNBBox.max.z) / 2);
				splitPos = (currentNode->KDNBBox.min.z + currentNode->KDNBBox.max.z) / 2;
			}
			
			//KDNode * left = ;
			//KDNode * right = ;

			currentNode->leftChild = new KDNode();
			currentNode->rightChild = new KDNode();
			
			currentNode->leftChild->KDNBBox = BBox(currentNode->KDNBBox.min, newCorner1);
			currentNode->rightChild->KDNBBox = BBox(newCorner2, currentNode->KDNBBox.max);
			
			currentNode->leaf = false;
			currentNode->leftChild->leaf = true;
			currentNode->rightChild->leaf = true;

			currentNode->leftChild->split = (currentNode->split + 1) % 3;
			currentNode->rightChild->split = (currentNode->split + 1) % 3;
			
			//
			// now divide primitive
			float minPos, maxPos;
			for (int i = 0; i < kPrimitives.size(); i++)
			{
				//
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
		cout << "done building" << kPrimitives.size() << endl;
		

	}
	BBox KDTree::getBounds() const
	{
		return kBBox;
	}
	Intersection KDTree::intersect(const Ray& ray, float previousBestDistance) const
	{
		float t0, t1;
		std::pair<float, float>(t0, t1)=krootNode->KDNBBox.intersect(ray);
		if (t0>t1)
		{
			return Intersection::failure();
		}

		std::stack<KDNode *> innerStack;
		innerStack.push(krootNode->leftChild);
		innerStack.push(krootNode->rightChild);
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
				//cout << "entering this" << endl;

				//for each (Primitive *p in currentNode->kNPrimitives)
				for (int i = 0; i < currentNode->kNPrimitives.size();i++)
				{
					//float t0, t1;
					
					std::pair<float, float> intersections = currentNode->kNPrimitives[i]->getBounds().intersect(ray);
					if (intersections.first > intersections.second) continue;
					
					Intersection tempinter = currentNode->kNPrimitives[i]->intersect(ray, previousBestDist);

					if (tempinter)
					{
						
							ret = tempinter;
							previousBestDist = tempinter.distance;
						
						
					}

				}
			}
			else 
			{
				std::pair<float, float>(t0, t1) = currentNode->leftChild->KDNBBox.intersect(ray);
				if (t0 < t1) innerStack.push(currentNode->leftChild);

				std::pair<float, float>(t0, t1) = currentNode->rightChild->KDNBBox.intersect(ray);
				if (t0 < t1) innerStack.push(currentNode->rightChild);
			}






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