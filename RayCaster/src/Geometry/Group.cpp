#include "Group.h"

/////////////////////////////
// Group class Implementation
//
// Nicolas Bordes - 10/2016
/////////////////////////////

Group::Group() :
m_objects()
{
}

Group::Group(int num_objects) :
m_objects(num_objects)
{
}

Group::~Group() 
{
}

bool Group::intersect(const Ray& r, Hit& h, float tmin) 
{ 
	bool isHit = false;
	for (int i = 0; i < m_objects.size(); ++i) {
		if(m_objects[i]->intersect(r, h, tmin))
			isHit = true;
	}
	return isHit;
}

void Group::addObject(Object3D* obj) 
{
	m_objects.push_back(obj);
}

void Group::modifyObject(int i, Object3D * object)
{
	assert(i >= 0 && i < m_objects.size());
	m_objects[i] = object;
}

void Group::removeObject(int i)
{
	assert(i >= 0 && i < m_objects.size());
	m_objects.erase(m_objects.begin() + i);
}

int Group::getGroupSize() 
{
	return m_objects.size();
}

Object3D* Group::getObject(int i) const
{
	assert(i >= 0 && i < m_objects.size());
	return m_objects[i];
}