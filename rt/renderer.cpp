#include <rt\renderer.h>
#include <core/image.h>
#include <core/color.h>


rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);
namespace rt{

	
	Renderer::Renderer(Camera* cam, Integrator* integrator)
	{
	
	}

	void Renderer::setSamples(uint samples)
	{
		
	}
	void Renderer::render(Image& img)
	{
	 
		for (uint i=0;i< img.width();i++)
			for (uint j=0;j<img.height();j++)
			{
				img(i,j)=a1computeColor(i,j,img.width(),img.height());
			}
	
	}
	
	
}
