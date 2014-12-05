#include <rt\textures\imagetex.h>

namespace rt
{


	ImageTexture::ImageTexture()
	{}
	ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
	{
		imteximage = image;
		imtexbh = bh;
		imtexi = i;

	}
	ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
	{
		imteximage.readPNG(filename);
		imtexbh = bh;
		imtexi = i;
	}
	RGBColor ImageTexture::getColor(const Point& coord)
	{
		float x = coord.x * imteximage.width();
		float y = coord.y * imteximage.height();
		if (imtexi == InterpolationType::NEAREST)
		{
			int newx = floor(x);
			int newy = floor(y);

			float diffx = x - newx;
			float diffy = y - newy;

			if (diffx > 0.5) newx++;
			if (diffy > 0.5) newy++;

			Point p = getTextureCoord(newx, newy);
			newx = p.x;
			newy = p.y;
			return imteximage(newx, newy);
		}
		if (imtexi == InterpolationType::BILINEAR)
		{
			int floorx = floor(x);
			int cielx = ceil(x);

			int floory = floor(y);
			int ciely = ceil(y);

			float diffx = abs(x - floorx);
			float diffy = abs(y - floory);

			Point p0 = getTextureCoord(floorx, floory);
			Point p1 = getTextureCoord(floorx, ciely);
			Point p2 = getTextureCoord(cielx, floory);
			Point p3 = getTextureCoord(cielx, ciely);

			RGBColor c00 = imteximage(p0.x, p0.y);
			RGBColor c01 = imteximage(p1.x, p1.y);
			RGBColor c10 = imteximage(p2.x, p2.y);
			RGBColor c11 = imteximage(p3.x, p3.y);

			return lerp2d(c00, c10, c01, c11, diffx, diffy);



		}

		return RGBColor::rep(0.0f);

	}
	Point ImageTexture::getTextureCoord(int x, int y) const
	{
		switch (imtexbh)
		{
		case BorderHandlingType::CLAMP:
			if (x < 0) x = 0;
			if (x >= imteximage.width()) x = imteximage.width() - 1;
			if (y < 0) y = 0;
			if (y >= imteximage.height()) y = imteximage.height() - 1;
			break;
		case BorderHandlingType::MIRROR:
			if (x < 0) x = -1 - x;
			if (x >= imteximage.width())
			{
				int divx = x / imteximage.width();

				x = x % imteximage.width();
				if (divx % 2 != 0) x = imteximage.width() - 1 - x;

			}

			if (y < 0) y = -1 - y;
			if (y >= imteximage.height())
			{
				int divy = y / imteximage.height();

				y = y % imteximage.height();
				if (divy % 2 != 0) y = imteximage.width() - 1 - y;


			}
			break;
		case BorderHandlingType::REPEAT:
			x = x % imteximage.width();
			y = y % imteximage.height();
			break;
		default:
			break;
		}

		return Point(x, y, 0);

	}
	RGBColor ImageTexture::getColorDX(const Point& coord)
	{
		NOT_IMPLEMENTED;
	}
	RGBColor ImageTexture::getColorDY(const Point& coord)
	{
		NOT_IMPLEMENTED;
	}
}