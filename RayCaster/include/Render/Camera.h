#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include <float.h>
#include <cmath>

///////////////////////////
// Camera Header
//
// Nicolas Bordes - 10/2016
///////////////////////////

///////////////////////
// Virtual Camera class
///////////////////////
class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay(const Vector2f& point) = 0;

	virtual float getTMin() const = 0;
	virtual ~Camera() {}
protected:
	Vector3f m_center;
	Vector3f m_direction;
	Vector3f m_up;
	Vector3f m_horizontal;
	float m_aspectRatio;
};

///////////////////////////
// Perspective Camera class
///////////////////////////
class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, float angle, float aspectRatio = 1);

	virtual Ray generateRay(const Vector2f& point);

	virtual float getTMin() const;

	void setAngle(float angle);

private:
	float m_angle;
	float m_Dist2VScreen;	
};

#endif //CAMERA_H
