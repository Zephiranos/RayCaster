#include "Light.h"

/////////////////////////////
// Light class Implementation
//
// Nicolas Bordes - 10/2016
/////////////////////////////

///////////////////////////////////
// Directional Light Implementation
///////////////////////////////////

DirectionalLight::DirectionalLight(const Vector3f& d, const Vector3f& c)
{
	m_direction = d.normalized();
	m_color = c;
}

DirectionalLight::~DirectionalLight()
{

}
///@param p unsed in this function
///@param distanceToLight not well defined because it's not a point light
void DirectionalLight::getIllumination(const Vector3f& p, Vector3f& dir, Vector3f& col, float& distanceToLight) const
{
	// the direction to the light is the opposite of the
	// direction of the directional light source
	dir = -m_direction;
	col = m_color;
}

Vector3f DirectionalLight::getDirection() const
{
	return m_direction;
}

void DirectionalLight::setDirection(const Vector3f & direction)
{
	m_direction = direction;
}

Vector3f DirectionalLight::getColor() const
{
	return m_color;
}

void DirectionalLight::setColor(const Vector3f & color)
{
	m_color = color;
}

/////////////////////////////
// Point Light Implementation
/////////////////////////////

PointLight::PointLight(const Vector3f& p, const Vector3f& c)
{
	m_position = p;
	m_color = c;
}

PointLight::~PointLight()
{

}

void PointLight::getIllumination(const Vector3f& p, Vector3f& dir, Vector3f& col, float& distanceToLight) const
{
	// the direction to the light is the opposite of the
	// direction of the directional light source
	dir = (m_position - p);
	dir = dir / dir.abs();
	col = m_color;
}

Vector3f PointLight::getPosition() const
{
	return m_position;
}

void PointLight::setPosition(const Vector3f & position)
{
	m_position = position;
}

Vector3f PointLight::getColor() const
{
	return m_color;
}

void PointLight::setColor(const Vector3f & color)
{
	m_color = color;
}