#include "Plane.h"

/////////////////////////////
// Plane class Implementation
//
// Nicolas Bordes - 10/2016
/////////////////////////////

// Constructors
Plane::Plane() :
Object3D(),
m_normal(),
m_D()
{
}

Plane::Plane(const Vector3f& normal, float d, Material* m):
Object3D(m),
m_normal(normal),
m_D(d)
{
}

//Destructors
Plane::~Plane()
{
}

Vector3f Plane::getNormal() const
{
	return m_normal;
}

float Plane::getOffset() const
{
	return m_D;
}

bool Plane::intersect(const Ray& r, Hit& h, float tmin)
{
	float dotNOrigin = Vector3f::dot(r.getOrigin(), m_normal);
	float dotNDirection = Vector3f::dot(r.getDirection().normalized(), m_normal);

	if (dotNDirection != 0)
	{
		float t = -(-m_D + dotNOrigin) / dotNDirection;
		if (t >= tmin && t < h.getT())
		{
			h.set(t, m_material, m_normal);
			return true;
		}
	}
	return false;
}