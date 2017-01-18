#include "Hit.h"

///////////////////////////
// Hit class Implementation
//
// Nicolas Bordes - 10/2016
///////////////////////////

///////////////
// Constructors
///////////////
#pragma region Constructors

Hit::Hit()
{
	m_material = NULL;
	m_t = FLT_MAX;
	hasTex = false;
}

Hit::Hit(float _t, Material* m, const Vector3f& n)
{
	m_t = _t;
	m_material = m;
	m_normal = n;
	hasTex = false;
}

Hit::Hit(const Hit& h)
{
	m_t = h.m_t;
	m_material = h.m_material;
	m_normal = h.m_normal;
	hasTex = h.hasTex;
}

// destructor
Hit::~Hit()
{

}
#pragma endregion
//////////
// Utility
//////////
#pragma region Utility

float Hit::getT() const
{
	return m_t;
}

Material* Hit::getMaterial() const
{
	return m_material;
}

const Vector3f& Hit::getNormal() const
{
	return m_normal;
}

void Hit::set(float _t, Material* m, const Vector3f& n)
{
	m_t = _t;
	m_material = m;
	m_normal = n;
}

void Hit::setTexCoord(const Vector2f & coord) {
	texCoord = coord;
	hasTex = true;
}
#pragma endregion