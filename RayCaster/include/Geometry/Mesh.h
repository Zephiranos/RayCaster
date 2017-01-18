#pragma once
#ifndef MESH_H
#define MESH_H
#include <vector>
#include <cstdlib>
#include "Object3D.h"
#include "Triangle.h"
#include "Vector2f.h"
#include "Vector3f.h"
//#include "Trig.h"

//by default counterclockwise winding is front face
///////////////////////////
// Mesh Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
struct Trig {
	Trig() 
	{ 
		x[0] = 0; 
		x[1] = 0; 
		x[2] = 0; 
	}
	int & operator[](const int i) { return x[i]; }
	int x[3];
	int texID[3];
};

class Mesh :public Object3D {
public:
	Mesh(const char * filename, Material* m);
	~Mesh();
	std::vector<Vector3f>v;
	std::vector<Trig>t;
	std::vector<Vector3f>n;
	std::vector<Vector2f>texCoord;

	virtual bool intersect(const Ray& r, Hit& h, float tmin);
	std::string getFilename() const;

private:
	void compute_norm();
	std::string m_filename;
};

#endif
