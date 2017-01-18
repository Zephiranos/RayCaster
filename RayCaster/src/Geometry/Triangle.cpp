#include "Triangle.h"

////////////////////////////////
// Triangle class Implementation
//
// Nicolas Bordes - 10/2016
////////////////////////////////

Triangle::Triangle():
Object3D()
{
}

Triangle::Triangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) :
Object3D(m),
m_a(a),
m_b(b),
m_c(c)
{
}

bool Triangle::intersect(const Ray& ray, Hit& hit, float tmin)
{
	Matrix3f barMat = Matrix3f(m_a - m_b, m_a - m_c, ray.getDirection().normalized());

	Matrix3f tMat = barMat;
	tMat.setCol(2, m_a - ray.getOrigin());
	float t = tMat.determinant() / barMat.determinant();

	if (t >= tmin && t < hit.getT())
	{
		Matrix3f betaMat = barMat;
		Matrix3f gamMat = barMat;

		betaMat.setCol(0, m_a - ray.getOrigin());
		gamMat.setCol(1, m_a - ray.getOrigin());

		float beta = betaMat.determinant() / barMat.determinant();
		float gamma = gamMat.determinant() / barMat.determinant();

		if (beta >= 0 && gamma >= 0 && beta + gamma <= 1)
		{
			hit.set(t, m_material, (1 - beta - gamma) * normals[0] + beta * normals[1] + gamma * normals[2]);
			if (hasTex)
			{
				hit.setTexCoord((1 - beta - gamma) * texCoords[0] + beta * texCoords[1] + gamma * texCoords[2]);
			}

		}
	}

	return false;
}