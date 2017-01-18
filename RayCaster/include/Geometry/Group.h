#pragma once
#ifndef GROUP_H
#define GROUP_H

#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>
#include <vector>

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
///////////////////////////
// Group Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Group :public Object3D
{
public:
	// Constructors
	Group();
	Group(int num_objects);
	// Destructors
	~Group();

	virtual bool intersect(const Ray& r, Hit& h, float tmin);
	void addObject(Object3D* obj);
	void modifyObject(int i, Object3D * object);
	void removeObject(int i);
	Object3D* getObject(int i) const;
	int getGroupSize();

private:
	std::vector<Object3D*> m_objects;
};

#endif

