#pragma once
#ifndef HIT_H
#define HIT_H

#include "Vector2f.h"
#include "Vector3f.h"
#include "Ray.h"
#include "Material.h"
#include <float.h>
#include <ostream>

///////////////////////////
// Hit class Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Hit
{
public:

	// Constructors
	Hit();
	Hit(float _t, Material* m, const Vector3f& n);
	Hit(const Hit& h);
	// Destructor
	~Hit();

	float getT() const;

	Material* getMaterial() const;

	const Vector3f& getNormal() const;

	void set(float _t, Material* m, const Vector3f& n);
	void setTexCoord(const Vector2f & coord);
	bool hasTex;
	Vector2f texCoord;
private:
	float m_t;
	Material* m_material;
	Vector3f m_normal;

};

inline std::ostream& operator << (std::ostream &os, const Hit& h)
{
	os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
	return os;
}

#endif // HIT_H
