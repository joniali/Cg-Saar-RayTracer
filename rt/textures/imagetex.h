#ifndef CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER
#define CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER

#include <core/vector.h>
#include <core/image.h>
#include <rt/textures/texture.h>
#include <core/scalar.h>
#include <core/point.h>
#include <core/interpolate.h>
#include <core/image.h>
namespace rt {

class ImageTexture : public Texture {
public:
    enum BorderHandlingType {
        CLAMP,
        MIRROR,
        REPEAT
    };

    enum InterpolationType {
        NEAREST,
        BILINEAR
    };

    ImageTexture();
    ImageTexture(const Image& image, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR);
    ImageTexture(const std::string& filename, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR);
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord);
    virtual RGBColor getColorDY(const Point& coord);
	Point ImageTexture::getTextureCoord(int x, int y) const;
private:
	Image imteximage;
	BorderHandlingType imtexbh;
	InterpolationType imtexi;
	std::string imtexfilename;

};

}

#endif
