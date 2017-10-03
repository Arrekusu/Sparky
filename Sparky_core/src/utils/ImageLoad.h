#pragma once

#include <FreeImage.h>
#include <string>

namespace sparky {  namespace graphics{

	static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		BYTE* bits = nullptr;

		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if (!dib)
			return nullptr;

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		int bpp = FreeImage_GetBPP(dib);

		int size = *width * *height * (bpp / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);

		return result;

	}

}  }
