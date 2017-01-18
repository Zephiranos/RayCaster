#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <cassert>
#include "Vector2f.h"
#include "Vector3f.h"

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Object3D.h"
#include "Mesh.h"
#include "Group.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Transform.h"
#include <vector>

#define MAX_PARSER_TOKEN_LENGTH 100


///////////////////////////
// Scene Parser Header
//
// Nicolas Bordes - 10/2016
///////////////////////////
class Scene
{
public:
	// Constructors
	Scene();
	~Scene();

	// Utility
	Camera* getCamera() const;
	void setCamera(Camera * camera);

	Vector3f getBackgroundColor() const;
	void setBackgroundColor(const Vector3f & color);

	Vector3f getAmbientLight() const;
	void setAmbientLight(const Vector3f & color);

	int getNumLights() const;
	Light* getLight(int i) const;
	void addLight(Light * newLight);
	void modifyLight(int i, Light * light);
	void removeLight(int i);
	int getNumMaterials() const;
	Material* getMaterial(int i) const;
	void addMaterial(Material * newMaterial);
	void modifyMaterial(int i, Material * material);
	void removeMaterial(int i);
	Group* getGroup() const;

	bool loadScene(const char* filename);

private:


	//Control class copy
	Scene(const Scene & sp);
	Scene & operator= (const Scene & sp);

	// Parser
	void parseFile();
	void parsePerspectiveCamera();
	void parseBackground();
	void parseLights();
	Light* parseDirectionalLight();
	Light* parsePointLight();
	void parseMaterials();
	Material* parseMaterial();
	Object3D* parseObject(char token[MAX_PARSER_TOKEN_LENGTH]);
	Group* parseGroup();
	Sphere* parseSphere();
	Plane* parsePlane();
	Triangle* parseTriangle();
	Mesh* parseTriangleMesh();
	Transform* parseTransform();

	// Reader
	int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);
	Vector3f readVector3f();
	Vector2f readVec2f();
	float readFloat();
	int readInt();

	// Member
	FILE* m_file;
	std::ifstream m_fileParser;
	Camera* m_camera;
	Vector3f m_background_color;
	Vector3f m_ambientLight;
	std::vector<Light*> m_lights;
	std::vector<Material*> m_materials;
	Material* m_currentMaterial;
	Group* m_group;
};

#endif // SCENE_H
