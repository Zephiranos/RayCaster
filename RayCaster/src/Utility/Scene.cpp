#include <cstdio>
#include <cstring>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>

#include "Scene.h"
#include "Camera.h" 
#include "Light.h"
#include "Material.h"

#include "Object3D.h"
#include "Group.h" 
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Transform.h"

#define DegreesToRadians(x) ((M_PI * x) / 180.0f)

///////////////////////////
// SceneParser Implementation
//
// Nicolas Bordes - 10/2016
///////////////////////////

///////////////
// Constructors
///////////////
#pragma region Constructors

Scene::Scene()
{
	m_group = new Group();
	m_camera = NULL;
	m_background_color = Vector3f(0.5, 0.5, 0.5);
	m_ambientLight = Vector3f(0, 0, 0);
	m_lights = std::vector<Light*>();
	m_materials = std::vector<Material*>();
	m_currentMaterial = NULL;
}

Scene::~Scene() {
	if (m_group != NULL)
		delete m_group;
	if (m_camera != NULL)
		delete m_camera;
	int i;
	for (i = 0; i < m_materials.size(); i++) {
		delete m_materials[i];
	}
	for (i = 0; i < m_lights.size(); i++) {
		delete m_lights[i];
	}
}
#pragma endregion
//////////
// Utility
//////////
#pragma region Utility

bool Scene::loadScene(const char* filename) {

	// initialize some reasonable default values
	//m_group = NULL;
	m_camera = NULL;
	m_background_color = Vector3f(0.5, 0.5, 0.5);
	m_ambientLight = Vector3f(0, 0, 0);
	m_lights = std::vector<Light*>();
	m_materials = std::vector<Material*>();
	m_currentMaterial = NULL;

	// parse the file
	assert(filename != NULL);
	const char *ext = &filename[strlen(filename) - 4];

	if (strcmp(ext, ".txt") != 0) {
		printf("wrong file name extension\n");
		exit(0);
	}
	fopen_s(&m_file, filename, "r");
	//m_fileParser = new std::ifstream(filename);

	if (m_file == NULL) {
		//if (m_fileParser == NULL) {
		printf("cannot open scene file\n");
		exit(0);
	}
	parseFile();
	//m_fileParser->close();
	fclose(m_file);
	m_file = NULL;
}

Camera* Scene::getCamera() const
{
	return m_camera;
}

void Scene::setCamera(Camera * camera)
{
	m_camera = camera;
}

Vector3f Scene::getBackgroundColor() const
{
	return m_background_color;
}

void Scene::setBackgroundColor(const Vector3f & color)
{
	m_background_color = color;
}

Vector3f Scene::getAmbientLight() const
{
	return m_ambientLight;
}

void Scene::setAmbientLight(const Vector3f & color)
{
	m_ambientLight = color;
}

int Scene::getNumLights() const
{
	return m_lights.size();
}

Light* Scene::getLight(int i) const
{
	assert(i >= 0 && i < m_lights.size());
	return m_lights[i];
}

void Scene::addLight(Light* newLight)
{
	m_lights.push_back(newLight);
}

void Scene::modifyLight(int i, Light * light)
{
	assert(i >= 0 && i < m_lights.size());
	m_lights[i] = light;
}

void Scene::removeLight(int i)
{
	assert(i >= 0 && i < m_lights.size());
	m_lights.erase(m_lights.begin() + i);
}

int Scene::getNumMaterials() const
{
	return m_materials.size();
}

Material* Scene::getMaterial(int i) const
{
	assert(i >= 0 && i < m_materials.size());
	return m_materials[i];
}

void Scene::addMaterial(Material * newMaterial)
{
	m_materials.push_back(newMaterial);
}

void Scene::modifyMaterial(int i, Material * material)
{
	assert(i >= 0 && i < m_materials.size());
	m_materials[i] = material;
}

void Scene::removeMaterial(int i)
{
	assert(i >= 0 && i < m_materials.size());
	m_materials.erase(m_materials.begin() + i);
}

Group* Scene::getGroup() const
{
	return m_group;
}
#pragma endregion
//////////
// Parsers
//////////
#pragma region Parsers

void Scene::parseFile() {
	//
	// at the top level, the scene can have a camera, 
	// background color and a group of objects
	// (we add lights and other things in future assignments)
	//
	char token[MAX_PARSER_TOKEN_LENGTH];
	while (getToken(token)) {
		if (!strcmp(token, "PerspectiveCamera")) {
			parsePerspectiveCamera();
		}
		else if (!strcmp(token, "Background")) {
			parseBackground();
		}
		else if (!strcmp(token, "Lights")) {
			parseLights();
		}
		else if (!strcmp(token, "Materials")) {
			parseMaterials();
		}
		else if (!strcmp(token, "Group")) {
			m_group = parseGroup();
		}
		else {
			printf("Unknown token in parseFile: '%s'\n", token);
			exit(0);
		}
	}
}

void Scene::parsePerspectiveCamera() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	// read in the camera parameters
	getToken(token); assert(!strcmp(token, "{"));
	getToken(token); assert(!strcmp(token, "center"));
	Vector3f center = readVector3f();
	getToken(token); assert(!strcmp(token, "direction"));
	Vector3f direction = readVector3f();
	getToken(token); assert(!strcmp(token, "up"));
	Vector3f up = readVector3f();
	getToken(token); assert(!strcmp(token, "angle"));
	float angle_degrees = readFloat();
	float angle_radians = DegreesToRadians(angle_degrees);
	getToken(token); assert(!strcmp(token, "}"));
	m_camera = new PerspectiveCamera(center, direction, up, angle_radians);
}

void Scene::parseBackground() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	// read in the background color
	getToken(token); assert(!strcmp(token, "{"));
	while (1) {
		getToken(token);
		if (!strcmp(token, "}")) {
			break;
		}
		else if (!strcmp(token, "color")) {
			m_background_color = readVector3f();
		}
		else if (!strcmp(token, "ambientLight")) {
			m_ambientLight = readVector3f();
		}
		else {
			printf("Unknown token in parseBackground: '%s'\n", token);
			assert(0);
		}
	}
}

void Scene::parseLights() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));
	// read in the number of objects
	getToken(token); assert(!strcmp(token, "numLights"));
	int numLights = readInt();
	//m_lights = new Light*[m_numLights];
	// read in the objects
	int count = 0;
	while (numLights > count) {
		getToken(token);
		if (!strcmp(token, "DirectionalLight")) {
			m_lights.push_back(parseDirectionalLight());
		}
		else if (strcmp(token, "PointLight") == 0)
		{
			m_lights.push_back(parsePointLight());
		}
		else {
			printf("Unknown token in parseLight: '%s'\n", token);
			exit(0);
		}
		count++;
	}
	getToken(token); assert(!strcmp(token, "}"));
}

Light* Scene::parseDirectionalLight() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));
	getToken(token); assert(!strcmp(token, "direction"));
	Vector3f direction = readVector3f();
	getToken(token); assert(!strcmp(token, "color"));
	Vector3f color = readVector3f();
	getToken(token); assert(!strcmp(token, "}"));
	return new DirectionalLight(direction, color);
}

Light* Scene::parsePointLight() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));
	getToken(token); assert(!strcmp(token, "position"));
	Vector3f position = readVector3f();
	getToken(token); assert(!strcmp(token, "color"));
	Vector3f color = readVector3f();
	getToken(token); assert(!strcmp(token, "}"));
	return new PointLight(position, color);
}

void Scene::parseMaterials() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));
	// read in the number of objects
	getToken(token); assert(!strcmp(token, "numMaterials"));
	int numMaterials = readInt();
	// read in the objects
	int count = 0;
	while (numMaterials > count) {
		getToken(token);
		if (!strcmp(token, "Material") ||
			!strcmp(token, "PhongMaterial")) {
			m_materials[count] = parseMaterial();
		}
		else {
			printf("Unknown token in parseMaterial: '%s'\n", token);
			exit(0);
		}
		count++;
	}
	getToken(token); assert(!strcmp(token, "}"));
}

Material* Scene::parseMaterial() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	char filename[MAX_PARSER_TOKEN_LENGTH];
	filename[0] = 0;
	Vector3f diffuseColor(1, 1, 1), specularColor(0, 0, 0);
	float shininess = 0;
	getToken(token); assert(!strcmp(token, "{"));
	while (1) {
		getToken(token);
		if (strcmp(token, "diffuseColor") == 0) {
			diffuseColor = readVector3f();
		}
		else if (strcmp(token, "specularColor") == 0) {
			specularColor = readVector3f();
		}
		else if (strcmp(token, "shininess") == 0) {
			shininess = readFloat();
		}
		else if (strcmp(token, "texture") == 0) {
			getToken(filename);
		}
		else {
			assert(!strcmp(token, "}"));
			break;
		}
	}
	Material *answer = new Material(diffuseColor, specularColor, shininess);
	if (filename[0] != 0) {
		answer->loadTexture(filename);
	}
	return answer;
}

Object3D* Scene::parseObject(char token[MAX_PARSER_TOKEN_LENGTH]) {
	Object3D *answer = NULL;
	if (!strcmp(token, "Group")) {
		answer = (Object3D*)parseGroup();
	}
	else if (!strcmp(token, "Sphere")) {
		answer = (Object3D*)parseSphere();
	}
	else if (!strcmp(token, "Plane")) {
		answer = (Object3D*)parsePlane();
	}
	else if (!strcmp(token, "Triangle")) {
		answer = (Object3D*)parseTriangle();
	}
	else if (!strcmp(token, "TriangleMesh")) {
		answer = (Object3D*)parseTriangleMesh();
	}
	else if (!strcmp(token, "Transform")) {
		answer = (Object3D*)parseTransform();
	}
	else {
		printf("Unknown token in parseObject: '%s'\n", token);
		exit(0);
	}
	return answer;
}

Group* Scene::parseGroup() {
	//
	// each group starts with an integer that specifies
	// the number of objects in the group
	//
	// the material index sets the material of all objects which follow,
	// until the next material index (scoping for the materials is very
	// simple, and essentially ignores any tree hierarchy)
	//
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));

	// read in the number of objects
	getToken(token); assert(!strcmp(token, "numObjects"));
	int num_objects = readInt();

	//Group *answer = new Group(num_objects);
	Group *answer = new Group();

	// read in the objects
	int count = 0;
	while (num_objects > count) {
		getToken(token);
		if (!strcmp(token, "MaterialIndex")) {
			// change the current material
			int index = readInt();
			assert(index >= 0 && index <= getNumMaterials());
			m_currentMaterial = getMaterial(index);
		}
		else {
			Object3D *object = parseObject(token);
			assert(object != NULL);
			answer->addObject(object);

			count++;
		}
	}
	getToken(token); assert(!strcmp(token, "}"));

	// return the group
	return answer;
}

Sphere* Scene::parseSphere() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));
	getToken(token); assert(!strcmp(token, "center"));
	Vector3f center = readVector3f();
	getToken(token); assert(!strcmp(token, "radius"));
	float radius = readFloat();
	getToken(token); assert(!strcmp(token, "}"));
	assert(m_currentMaterial != NULL);
	return new Sphere(center, radius, m_currentMaterial);
}

Plane* Scene::parsePlane() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));
	getToken(token); assert(!strcmp(token, "normal"));
	Vector3f normal = readVector3f();
	getToken(token); assert(!strcmp(token, "offset"));
	float offset = readFloat();
	getToken(token); assert(!strcmp(token, "}"));
	assert(m_currentMaterial != NULL);
	return new Plane(normal, offset, m_currentMaterial);
}

Triangle* Scene::parseTriangle() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert(!strcmp(token, "{"));
	getToken(token);
	assert(!strcmp(token, "vertex0"));
	Vector3f v0 = readVector3f();
	getToken(token);
	assert(!strcmp(token, "vertex1"));
	Vector3f v1 = readVector3f();
	getToken(token);
	assert(!strcmp(token, "vertex2"));
Vector3f v2 = readVector3f();
getToken(token); assert(!strcmp(token, "}"));
assert(m_currentMaterial != NULL);
return new Triangle(v0, v1, v2, m_currentMaterial);
}

Mesh* Scene::parseTriangleMesh() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	char filename[MAX_PARSER_TOKEN_LENGTH];
	// get the filename
	getToken(token); assert(!strcmp(token, "{"));
	getToken(token); assert(!strcmp(token, "obj_file"));
	getToken(filename);
	getToken(token); assert(!strcmp(token, "}"));
	const char *ext = &filename[strlen(filename) - 4];
	assert(!strcmp(ext, ".obj"));
	Mesh *answer = new Mesh(filename, m_currentMaterial);

	return answer;
}

Transform* Scene::parseTransform() {
	char token[MAX_PARSER_TOKEN_LENGTH];
	Matrix4f matrix = Matrix4f::identity();
	Object3D *object = NULL;
	getToken(token); assert(!strcmp(token, "{"));
	// read in transformations: 
	// apply to the LEFT side of the current matrix (so the first
	// transform in the list is the last applied to the object)
	getToken(token);

	while (1) {
		if (!strcmp(token, "Scale")) {
			Vector3f s = readVector3f();
			matrix = matrix * Matrix4f::scaling(s[0], s[1], s[2]);
		}
		else if (!strcmp(token, "UniformScale")) {
			float s = readFloat();
			matrix = matrix * Matrix4f::uniformScaling(s);
		}
		else if (!strcmp(token, "Translate")) {
			matrix = matrix * Matrix4f::translation(readVector3f());
		}
		else if (!strcmp(token, "XRotate")) {
			matrix = matrix * Matrix4f::rotateX(DegreesToRadians(readFloat()));
		}
		else if (!strcmp(token, "YRotate")) {
			matrix = matrix * Matrix4f::rotateY(DegreesToRadians(readFloat()));
		}
		else if (!strcmp(token, "ZRotate")) {
			matrix = matrix * Matrix4f::rotateZ(DegreesToRadians(readFloat()));
		}
		else if (!strcmp(token, "Rotate")) {
			getToken(token); assert(!strcmp(token, "{"));
			Vector3f axis = readVector3f();
			float degrees = readFloat();
			float radians = DegreesToRadians(degrees);
			matrix = matrix * Matrix4f::rotation(axis, radians);
			getToken(token); assert(!strcmp(token, "}"));
		}
		else if (!strcmp(token, "Matrix4f")) {
			Matrix4f matrix2 = Matrix4f::identity();
			getToken(token); assert(!strcmp(token, "{"));
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					float v = readFloat();
					matrix2(i, j) = v;
				}
			}
			getToken(token); assert(!strcmp(token, "}"));
			matrix = matrix2 * matrix;
		}
		else {
			// otherwise this must be an object,
			// and there are no more transformations
			object = parseObject(token);
			break;
		}
		getToken(token);
	}

	assert(object != NULL);
	getToken(token); assert(!strcmp(token, "}"));
	return new Transform(matrix, object);
}
#pragma endregion
/////////
// Reader
/////////
#pragma region Reader

int Scene::getToken(char token[MAX_PARSER_TOKEN_LENGTH]) {
	// for simplicity, tokens must be separated by whitespace
	assert(m_file != NULL);
	//std::string buf;
	int success = fscanf_s(m_file, "%s ", token, MAX_PARSER_TOKEN_LENGTH);
	if (success == EOF) {
		token[0] = '\0';
		return 0;
	}
	//if (m_fileParser >> buf)
	//{

	//}
	return 1;
}

Vector3f Scene::readVector3f() {
	float x, y, z;
	int count = fscanf_s(m_file, "%f %f %f", &x, &y, &z);
	if (count != 3) {
		printf("Error trying to read 3 floats to make a Vector3f\n");
		assert(0);
	}
	return Vector3f(x, y, z);
}

Vector2f Scene::readVec2f() {
	float u, v;
	int count = fscanf_s(m_file, "%f %f", &u, &v);
	if (count != 2) {
		printf("Error trying to read 2 floats to make a Vec2f\n");
		assert(0);
	}
	return Vector2f(u, v);
}

float Scene::readFloat() {
	float answer;
	int count = fscanf_s(m_file, "%f", &answer);
	if (count != 1) {
		printf("Error trying to read 1 float\n");
		assert(0);
	}
	return answer;
}

int Scene::readInt() {
	int answer;
	int count = fscanf_s(m_file, "%d", &answer);
	if (count != 1) {
		printf("Error trying to read 1 int\n");
		assert(0);
	}
	return answer;
}
#pragma endregion