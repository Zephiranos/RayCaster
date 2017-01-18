#include "Camera.h"

////////////////////////////////////
// Perspective Camera Implementation
//
// Nicolas Bordes - 10/2016
////////////////////////////////////
PerspectiveCamera::PerspectiveCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, float angle, float aspectRatio)
{
	m_center = center;
	m_direction = direction.normalized();
	m_horizontal = Vector3f::cross(m_direction, up).normalized();
	m_up = Vector3f::cross(m_horizontal, m_direction).normalized();
	m_angle = angle;
	m_Dist2VScreen = 1 / tanf(m_angle / 2);
	m_aspectRatio = aspectRatio;
}

Ray PerspectiveCamera::generateRay(const Vector2f& point) 
{
	Vector3f r = point.x() * m_horizontal + m_Dist2VScreen * m_direction + m_aspectRatio * point.y() * m_up;

	return Ray(m_center, r);
}

float PerspectiveCamera::getTMin() const {
	return 0.0f;
}

void PerspectiveCamera::setAngle(float angle) {
	m_angle = angle;
}