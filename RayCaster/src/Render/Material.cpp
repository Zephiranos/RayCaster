#include "Material.h"
#include "Vector3f.h"
#include "Hit.h"

////////////////////////////////
// Material class Implementation
//
// Nicolas Bordes - 10/2016
////////////////////////////////

Material::Material(const Vector3f& d_color, const Vector3f& s_color, float s) :
	m_diffuseColor(d_color), m_specularColor(s_color), m_shininess(s)
{
}

Material::~Material()
{
}

Vector3f Material::getDiffuseColor() const
{
	return  m_diffuseColor;
}

Vector3f Material::getSpecularColor() const
{
	return m_specularColor;
}

float Material::getShininess() const
{
	return m_shininess;
}

Vector3f Material::Shade(const Ray& ray, const Hit& hit, const Vector3f& dirToLight, const Vector3f& lightColor)
{
	float d = fmax(Vector3f::dot(dirToLight, hit.getNormal()), 0.f);
	float s = 0;
	if (m_shininess != 0)
	{
		Vector3f reflection = 2 * Vector3f::dot(dirToLight, hit.getNormal()) * hit.getNormal() - dirToLight;
		s = pow(fmax(Vector3f::dot(reflection, -ray.getDirection().normalized()), 0.f), m_shininess);
	}
	Vector3f matCol = (hit.hasTex && m_t.valid()) ? m_t(hit.texCoord.x(), hit.texCoord.y()) : m_diffuseColor;
	return d * lightColor * matCol + s * lightColor * m_specularColor;
}

void Material::loadTexture(const char * filename) {
	m_t.load(filename);
}