#include "Sphere.h"

//////////////////////////////
// Sphere class Implementation
//
// Nicolas Bordes - 10/2016
//////////////////////////////

Sphere::Sphere() :
	Object3D(),
	m_center(),
	m_radius(1)
{
}

Sphere::Sphere(Vector3f center, float radius, Material* material) :
	Object3D(material),
	m_center(center),
	m_radius(radius)
{
}

Sphere::~Sphere()
{
}

Vector3f Sphere::getCenter() const
{
	return m_center;
}

float Sphere::getRadius() const
{
	return m_radius;
}

bool Sphere::intersect(const Ray& r, Hit& h, float tmin)
{
	float t;
	Ray ray = Ray(r.getOrigin(), r.getDirection().normalized());
	float b = 2 * Vector3f::dot(ray.getDirection(), ray.getOrigin() - m_center);
	float c = Vector3f::dot(ray.getOrigin() - m_center, ray.getOrigin() - m_center) - m_radius * m_radius;

	float det = b * b - 4 * c;
	if (det == 0)
	{
		t = -b / 2;
		if (t >= tmin && t < h.getT())
		{
			h.set(t, m_material, (ray.pointAtParameter(t) - m_center).normalized());
			return true;
		}
	}
	else if (det > 0)
	{
		t = (-b - sqrt(det)) / 2;
		if (t < 0)
		{
			t = (-b + sqrt(det)) / 2;
		}
		if (t >= tmin && t < h.getT())
		{
			h.set(t, m_material, (ray.pointAtParameter(t) - m_center).normalized());
			return true;
		}
	}
	return false;
}