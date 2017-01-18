#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include "Vector3f.h"
#include "Texture.h"

class Ray;
class Hit;

///////////////////////////
// Material class Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Material
{
public:

	Material(const Vector3f& d_color, const Vector3f& s_color = Vector3f::ZERO, float s = 0);
	virtual ~Material();

	virtual Vector3f getDiffuseColor() const;
	Vector3f getSpecularColor() const;
	float getShininess() const;
	Vector3f Shade(const Ray& ray, const Hit& hit, const Vector3f& dirToLight, const Vector3f& lightColor);
	void loadTexture(const char * filename);

protected:
	Vector3f m_diffuseColor;
	Vector3f m_specularColor;
	float m_shininess;
	Texture m_t;
};



#endif // MATERIAL_H
