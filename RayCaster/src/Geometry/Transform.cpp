#include "Transform.h"
#include "Vector4f.h"

/////////////////////////////////
// Transform class Implementation
//
// Nicolas Bordes - 10/2016
/////////////////////////////////

Transform::Transform() :
m_obj(),
m_transMatrix()
{
}

Transform::Transform(const Matrix4f& m, Object3D* obj) :
m_obj(obj),
m_transMatrix(m)
{
}

Transform::~Transform()
{
}

Object3D * Transform::getObject() const
{
	return m_obj;
}

Matrix4f Transform::getTransformationMatrix() const
{
	return m_transMatrix;
}

bool Transform::intersect(const Ray& r, Hit& h, float tmin)
{
	Vector4f transfDir = m_transMatrix.inverse() * Vector4f(r.getDirection(), 1.f);
	Vector4f transfOrig = m_transMatrix.inverse() * Vector4f(r.getOrigin(), 1.f);
	Ray transfRay = Ray(transfOrig.xyz(), transfDir.xyz());
	if (m_obj->intersect(transfRay, h, tmin))
	{
		Vector4f transfNormal = m_transMatrix.inverse().transposed() * Vector4f(h.getNormal(), 1.f);
		h.set(h.getT(), h.getMaterial(), transfNormal.xyz().normalized());
		return true;
	}
	return false;
}