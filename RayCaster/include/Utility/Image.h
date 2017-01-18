#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <cassert>
#include "Vector3f.h"

///////////////////////////
// Image Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Image
{

public:

	Image(int w, int h);
	~Image();

	int Width() const;
	int Height() const;

	const Vector3f& GetPixel(int x, int y) const;
	void SetAllPixels(const Vector3f& color);
	void SetPixel(int x, int y, const Vector3f& color);

	static Image* LoadPPM(const char* filename);
	void SavePPM(const char* filename) const;

	static Image* LoadTGA(const char* filename);
	void SaveTGA(const char* filename) const;
	int SaveBMP(const char *filename);
	void SaveImage(const char *filename);
	// extension for image comparison
	static Image* compare(Image* img1, Image* img2);

private:

	int m_width;
	int m_height;
	Vector3f* m_data;

};

#endif // IMAGE_H
