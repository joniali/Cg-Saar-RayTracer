#include <rt\renderer.h>
#include <core/image.h>
#include <core/color.h>
#include <rt\ray.h>
#include <iostream>


using namespace std;
rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);
rt::RGBColor a2computeColor(const rt::Ray& r);
namespace rt{


	Renderer::Renderer(Camera* cam, Integrator* integrator):cam(cam),integrator(integrator)
	{

	}

	void Renderer::setSamples(uint samples)
	{

	}
	void Renderer::render(Image& img)
	{
		
		for (uint j=0;j< img.height();j++)
		{
			for (uint i=0;i<img.width();i++)
			{
				img(i,j)=a1computeColor(i,j,img.width(),img.height());
				

			}
			
		}

		

	}

	void Renderer::test_render1(Image& img)
	{
		
		for (uint j=0;j< img.height();j++)
		{
			for (uint i=0;i<img.width();i++)
			{

				float X = 2.0 * float(i + 0.5) / float(img.width()) - 1;
				float Y = 1 - 2.0 * float(j + 0.5) / float(img.height());
				const Ray r = cam->getPrimaryRay(X, Y);
				img(i, j)=a2computeColor(r);
				

			}
			
		}

	}


	void Renderer::test_render2(Image& img )
	{
		
		for (uint j=0;j< img.height();j++)
		{
			for (uint i=0;i<img.width();i++)
			{


				float X = 2.0 * float(i + 0.5) / float(img.width()) - 1;
				float Y = 1 - 2.0 * float(j + 0.5) / float(img.height());

				const Ray r = cam->getPrimaryRay(X, Y);

				img(i, j) = integrator->getRadiance(r);
				

			}
			
		}
		
	}
}
