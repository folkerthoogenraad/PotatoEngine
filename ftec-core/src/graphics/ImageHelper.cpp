#include "ImageHelper.h"

#define FREEIMAGE_LIB
#include <FreeImage.h>
#include "GL.h"

#include "util/scope_guard.h"

namespace ftec {

	std::optional<Image> loadImage(const std::string & filename)
	{//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		unsigned int width(0), height(0);

		//Make sure it gets destroyed
		std::scope_guard bitmapGuard([&dib]() {FreeImage_Unload(dib); });

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(filename.c_str(), 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename.c_str());
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return std::optional<Image>();

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename.c_str());

		//if the image failed to load, return failure
		if (!dib)
			return std::optional<Image>();

		FIBITMAP *image = FreeImage_ConvertTo32Bits(dib);

		//Make sure it gets destroyed
		std::scope_guard imageGuard([&image]() {FreeImage_Unload(image); });

		//retrieve the image data
		bits = FreeImage_GetBits(image);
		//get the image width and height
		width = FreeImage_GetWidth(image);
		height = FreeImage_GetHeight(image);

		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (width == 0) || (height == 0))
			return std::optional<Image>();

		Image out(width, height);

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int index = (x + y * width) * 4;

				Color32 c;

				c.r = bits[index + 0];
				c.g = bits[index + 1];
				c.b = bits[index + 2];
				c.a = bits[index + 3];

				out.setColor(x, y, c);
			}
		}

		return std::move(out);
	}

	bool saveImage(const Image & image, const std::string & filename)
	{
		FIBITMAP* fImage = FreeImage_ConvertFromRawBits((BYTE*)&image.getColors()[0], image.getWidth(), image.getHeight(), 4, 8, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);

		std::scope_guard fImageGuard([&fImage]() {FreeImage_Unload(fImage); });

		bool res = FreeImage_Save(FIF_PNG, fImage, filename.c_str(), 0);

		return res;
	}

	Vector2i glLoadImage(std::string name, unsigned int target)
	{
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		unsigned int width(0), height(0);

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(name.c_str(), 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(name.c_str());
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return Vector2i(-1, -1);

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, name.c_str());

		//if the image failed to load, return failure
		if (!dib)
			return Vector2i(-1, -1);

		FIBITMAP *image = FreeImage_ConvertTo32Bits(dib);

		//retrieve the image data
		bits = FreeImage_GetBits(image);
		//get the image width and height
		width = FreeImage_GetWidth(image);
		height = FreeImage_GetHeight(image);
		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (width == 0) || (height == 0))
			return Vector2i(-1,-1);

		//store the texture data for OpenGL use
		glTexImage2D(target, 0, GL_RGBA, width, height,
			0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

		//Free FreeImage's copy of the data
		FreeImage_Unload(dib);
		FreeImage_Unload(image);

		//return success
		return Vector2i(width, height);
	}
}