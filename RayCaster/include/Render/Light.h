#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <Vector3f.h>
#include "Object3D.h"

/////////////////////////////
// Light Virtual Class Header
//
// Nicolas Bordes - 10/2016
/////////////////////////////
class Light
{
public:

	Light()
	{

	}

	virtual ~Light()
	{

	}

	virtual void getIllumination(const Vector3f& p, Vector3f& dir, Vector3f& col, float& distanceToLight) const = 0;

};

class DirectionalLight : public Light
{
public:

	DirectionalLight(const Vector3f& d, const Vector3f& c);
	~DirectionalLight();
	///@param p unsed in this function
	///@param distanceToLight not well defined because it's not a point light
	virtual void getIllumination(const Vector3f& p, Vector3f& dir, Vector3f& col, float& distanceToLight) const;

	Vector3f getDirection() const;
	void setDirection(const Vector3f & direction);

	Vector3f getColor() const;
	void setColor(const Vector3f & color);

private:

	DirectionalLight(); // don't use

	Vector3f m_direction;
	Vector3f m_color;

};

class PointLight : public Light
{
public:

	PointLight(const Vector3f& p, const Vector3f& c);
	~PointLight();

	virtual void getIllumination(const Vector3f& p, Vector3f& dir, Vector3f& col, float& distanceToLight) const;

	Vector3f getPosition() const;
	void setPosition(const Vector3f & position);

	Vector3f getColor() const;
	void setColor(const Vector3f & color);

private:

	PointLight(); // don't use

	Vector3f m_position;
	Vector3f m_color;

};

#endif // LIGHT_H
