#define _USE_MATH_DEFINES // for C++  
#include <cmath> 
#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <qfiledialog.h>
#include "RayCaster.h"
#include "Image.h"


/////////////////////////////
// RayCastr UI Implementation
//
// Nicolas Bordes - 11/2016
/////////////////////////////

#define DegreesToRadians(x) ((M_PI * x) / 180.0f)

float coloritof(int i);
int colorftoi(float f);

RayCaster::RayCaster(QWidget *parent)
	: QMainWindow(parent),
	m_ui(Ui::RayCasterClass())
{
	m_isLoading = false;
	m_ui.setupUi(this);

	// init camera
	updateCam();
	// add default material.
	m_scene.addMaterial(new Material(Vector3f(0)));
	m_ui.m_materialsList->addItem(QString("Default"));
	m_ui.m_materialsList->setCurrentRow(m_ui.m_materialsList->count() - 1);
	m_ui.m_comboMaterial->addItem("Default");
	// add default light
	m_scene.addLight(new PointLight(Vector3f(0), Vector3f(1)));
	m_ui.m_lightList->addItem(QString("PointLight"));
	m_ui.m_lightList->setCurrentRow(m_ui.m_lightList->count() - 1);
	//init graphic view
	m_grScene = new QGraphicsScene(m_ui.m_graphicView);
	m_ui.m_graphicView->setScene(m_grScene);
	m_ui.m_pBarRendering->setHidden(true);
	//////////////////
	// Slot Connection
	//////////////////
	// Camera
	///
	connect(m_ui.m_rBtnPerspectiveCam, SIGNAL(toggled(bool)), this, SLOT(slotCamTypeChanged(bool)));
	// Position
	connect(m_ui.m_dSBoxCamPosX, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_dSBoxCamPosY, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_dSBoxCamPosZ, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	// Direction
	connect(m_ui.m_dSBoxCamDirX, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_dSBoxCamDirY, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_dSBoxCamDirZ, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	// Up
	connect(m_ui.m_dSBoxCamUpX, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_dSBoxCamUpY, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_dSBoxCamUpZ, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	// Angle
	connect(m_ui.m_dSBoxCamAngle, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	// Img
	connect(m_ui.m_SBoxImgW, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_SBoxImgH, SIGNAL(valueChanged(double)), this, SLOT(slotCamValueChanged(double)));
	connect(m_ui.m_BtnBrowseImg, SIGNAL(clicked(bool)), this, SLOT(slotImageFileBrowse(bool)));
	///
	// Light
	///
	connect(m_ui.m_BtnLightAdd, SIGNAL(clicked(bool)), this, SLOT(slotLightAdd(bool)));
	connect(m_ui.m_BtnLightRemove, SIGNAL(clicked(bool)), this, SLOT(slotLightRemove(bool)));
	connect(m_ui.m_lightList, SIGNAL(currentRowChanged(int)), this, SLOT(slotLightSelected(int)));
	// Type
	connect(m_ui.m_rBtnPointLight, SIGNAL(toggled(bool)), this, SLOT(slotLightTypeChanged(bool)));
	// Name
	connect(m_ui.m_LELightName, SIGNAL(textChanged(const QString &)), this, SLOT(slotLightNameChanged(const QString &)));
	// Direction/Position
	connect(m_ui.m_dSBoxLightDirPosX, SIGNAL(valueChanged(double)), this, SLOT(slotLightValueChanged(double)));
	connect(m_ui.m_dSBoxLightDirPosY, SIGNAL(valueChanged(double)), this, SLOT(slotLightValueChanged(double)));
	connect(m_ui.m_dSBoxLightDirPosZ, SIGNAL(valueChanged(double)), this, SLOT(slotLightValueChanged(double)));
	// Color
	connect(m_ui.m_SBoxLightColR, SIGNAL(valueChanged(int)), this, SLOT(slotLightValueChanged(int)));
	connect(m_ui.m_SBoxLightColG, SIGNAL(valueChanged(int)), this, SLOT(slotLightValueChanged(int)));
	connect(m_ui.m_SBoxLightColB, SIGNAL(valueChanged(int)), this, SLOT(slotLightValueChanged(int)));
	///
	// Object
	///
	connect(m_ui.m_btnAddObj, SIGNAL(clicked(bool)), this, SLOT(slotObjectAdd(bool)));
	connect(m_ui.m_btnRemoveObj, SIGNAL(clicked(bool)), this, SLOT(slotObjectRemove(bool)));
	connect(m_ui.m_objList, SIGNAL(currentRowChanged(int)), this, SLOT(slotObjectSelected(int)));
	connect(m_ui.m_objTab, SIGNAL(currentChanged(int)), this, SLOT(slotObjectChanged(int)));
	// Name
	connect(m_ui.m_LEObjName, SIGNAL(textChanged(const QString &)), this, SLOT(slotObjectNameChanged(const QString &)));
	// Sphere
	connect(m_ui.m_dSBoxSphereCenterX, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxSphereCenterY, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxSphereCenterZ, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxSphereRadius, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	// Plane
	connect(m_ui.m_dSBoxPlaneNormalX, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxPlaneNormalY, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxPlaneNormalZ, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxPlaneOffset, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	// Mesh
	connect(m_ui.m_btnBrowseMeshFile, SIGNAL(clicked(bool)), this, SLOT(slotObjectMeshBrowse(bool)));
	connect(m_ui.m_LEMeshFile, SIGNAL(textChanged(const QString &)), this, SLOT(slotObjectNameChanged(const QString &)));
	// Tranform
	connect(m_ui.m_CBObjTransform, SIGNAL(clicked(bool)), this, SLOT(slotObjectTransChecked(bool)));
	//Rotation
	connect(m_ui.m_dSBoxTransformRotationX, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxTransformRotationY, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxTransformRotationZ, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	//Scale
	connect(m_ui.m_dSBoxTransformScaleX, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxTransformScaleY, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxTransformScaleZ, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	//Translation
	connect(m_ui.m_dSBoxTransformTranslateX, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxTransformTranslateY, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	connect(m_ui.m_dSBoxTransformTranslateZ, SIGNAL(valueChanged(double)), this, SLOT(slotObjectValueChanged(double)));
	//object mat
	connect(m_ui.m_comboMaterial, SIGNAL(currentIndexChanged(int)), this, SLOT(slotObjectMaterialChanged(int)));
	///
	// Material
	///
	connect(m_ui.m_BtnMaterialAdd, SIGNAL(clicked(bool)), this, SLOT(slotMaterialAdd(bool)));
	connect(m_ui.m_BtnMaterialRemove, SIGNAL(clicked(bool)), this, SLOT(slotMaterialRemove(bool)));
	connect(m_ui.m_materialsList, SIGNAL(currentRowChanged(int)), this, SLOT(slotMaterialSelected(int)));
	// Name
	connect(m_ui.m_LEMaterialName, SIGNAL(textChanged(const QString &)), this, SLOT(slotMaterialNameChanged(const QString &)));
	// Diffuse Color
	connect(m_ui.m_SBoxDifColR, SIGNAL(valueChanged(int)), this, SLOT(slotMaterialValueChanged(int)));
	connect(m_ui.m_SBoxDifColG, SIGNAL(valueChanged(int)), this, SLOT(slotMaterialValueChanged(int)));
	connect(m_ui.m_SBoxDifColB, SIGNAL(valueChanged(int)), this, SLOT(slotMaterialValueChanged(int)));
	// Specular Color
	connect(m_ui.m_SBoxSpecColR, SIGNAL(valueChanged(int)), this, SLOT(slotMaterialValueChanged(int)));
	connect(m_ui.m_SBoxSpecColG, SIGNAL(valueChanged(int)), this, SLOT(slotMaterialValueChanged(int)));
	connect(m_ui.m_SBoxSpecColB, SIGNAL(valueChanged(int)), this, SLOT(slotMaterialValueChanged(int)));
	// Shininess
	connect(m_ui.m_SBoxShininess, SIGNAL(valueChanged(int)), this, SLOT(slotMaterialValueChanged(int)));
	connect(m_ui.m_CBoxIsSpec, SIGNAL(clicked(bool)), this, SLOT(slotMaterialSpecChecked(bool)));
	// Texture
	connect(m_ui.m_BtnBrowseTextFile, SIGNAL(clicked(bool)), this, SLOT(slotMaterialBrowseTextFile(bool)));
	connect(m_ui.m_LETextureFile, SIGNAL(textChanged(const QString &)), this, SLOT(slotMaterialNameChanged(const QString &)));
	///
	// Render
	///
	connect(m_ui.m_BtnRender, SIGNAL(clicked(bool)), this, SLOT(slotRender(bool)));
	///
}

void RayCaster::updateCam()
{
	Vector3f pos(m_ui.m_dSBoxCamPosX->value(), m_ui.m_dSBoxCamPosY->value(), m_ui.m_dSBoxCamPosZ->value());
	Vector3f direction(m_ui.m_dSBoxCamDirX->value(), m_ui.m_dSBoxCamDirY->value(), m_ui.m_dSBoxCamDirZ->value());
	Vector3f up(m_ui.m_dSBoxCamUpX->value(), m_ui.m_dSBoxCamUpY->value(), m_ui.m_dSBoxCamUpZ->value());
	
	float angle_degrees = m_ui.m_dSBoxCamAngle->value();
	float angle_radians = DegreesToRadians(angle_degrees);

	if (m_ui.m_rBtnPerspectiveCam->isChecked())
	{
		m_scene.setCamera(new PerspectiveCamera(pos, direction, up, angle_radians, m_ui.m_SBoxImgW->value() / m_ui.m_SBoxImgH->value()));
	}
	else
	{
	}
}

void RayCaster::updateLight()
{
	if (m_isLoading) return;
	int currLight = m_ui.m_lightList->currentRow();
	if (currLight < 0) return;

	Vector3f dirPos = Vector3f(m_ui.m_dSBoxLightDirPosX->value(), m_ui.m_dSBoxLightDirPosY->value(), m_ui.m_dSBoxLightDirPosZ->value());
	Vector3f color = Vector3f(coloritof(m_ui.m_SBoxLightColR->value()), coloritof(m_ui.m_SBoxLightColG->value()), coloritof(m_ui.m_SBoxLightColB->value()));

	if (m_ui.m_rBtnPointLight->isChecked())
	{
		m_scene.modifyLight(currLight, new PointLight(dirPos, color));
	}
	else
	{
		m_scene.modifyLight(currLight, new DirectionalLight(dirPos, color));
	}

	m_ui.m_lightList->item(currLight)->setText(m_ui.m_LELightName->text());
}

void RayCaster::updateObject()
{
	if (m_isLoading) return;
	int currObj = m_ui.m_objList->currentRow();
	if (currObj < 0) return;
	bool isTransChecked = m_ui.m_CBObjTransform->isChecked();

	m_ui.m_dSBoxTransformRotationX->setEnabled(isTransChecked);
	m_ui.m_dSBoxTransformRotationY->setEnabled(isTransChecked);
	m_ui.m_dSBoxTransformRotationZ->setEnabled(isTransChecked);

	m_ui.m_dSBoxTransformScaleX->setEnabled(isTransChecked);
	m_ui.m_dSBoxTransformScaleY->setEnabled(isTransChecked);
	m_ui.m_dSBoxTransformScaleZ->setEnabled(isTransChecked);

	m_ui.m_dSBoxTransformTranslateX->setEnabled(isTransChecked);
	m_ui.m_dSBoxTransformTranslateY->setEnabled(isTransChecked);
	m_ui.m_dSBoxTransformTranslateZ->setEnabled(isTransChecked);

	Material * selectedMat = m_scene.getMaterial(m_ui.m_comboMaterial->currentIndex());
	int curTab = m_ui.m_objTab->currentIndex();
	Object3D * object = NULL;

	if (m_ui.m_objTab->tabText(curTab) == "Sphere")
	{
		Vector3f center = Vector3f(m_ui.m_dSBoxSphereCenterX->value(), m_ui.m_dSBoxSphereCenterY->value(), m_ui.m_dSBoxSphereCenterZ->value());
		float radius = m_ui.m_dSBoxSphereRadius->value();
		object = new Sphere(center, radius, selectedMat);
	}
	else if (m_ui.m_objTab->tabText(curTab) == "Plane")
	{
		Vector3f normal = Vector3f(m_ui.m_dSBoxPlaneNormalX->value(), m_ui.m_dSBoxPlaneNormalY->value(), m_ui.m_dSBoxPlaneNormalZ->value());
		float offset = m_ui.m_dSBoxPlaneOffset->value();
		object = new Plane(normal, offset, selectedMat);
	}
	else if (m_ui.m_objTab->tabText(curTab) == "Mesh")
	{
		struct stat buffer;
		if (stat(m_ui.m_LEMeshFile->text().toStdString().c_str(), &buffer) == 0) // check file existence
		{
			object = new Mesh(m_ui.m_LEMeshFile->text().toStdString().c_str(), selectedMat);
		}
	}

	if (isTransChecked)
	{
		Vector3f rotation = Vector3f(m_ui.m_dSBoxTransformRotationX->value(), m_ui.m_dSBoxTransformRotationY->value(), m_ui.m_dSBoxTransformRotationZ->value());
		Vector3f scale = Vector3f(m_ui.m_dSBoxTransformScaleX->value(), m_ui.m_dSBoxTransformScaleY->value(), m_ui.m_dSBoxTransformScaleZ->value());
		Vector3f translation = Vector3f(m_ui.m_dSBoxTransformTranslateX->value(), m_ui.m_dSBoxTransformTranslateY->value(), m_ui.m_dSBoxTransformTranslateZ->value());

		Matrix4f mat = Matrix4f::identity();
		mat = mat * Matrix4f::scaling(scale[0], scale[1], scale[2]);
		mat = mat * Matrix4f::rotateX(DegreesToRadians(rotation[0]));
		mat = mat * Matrix4f::rotateY(DegreesToRadians(rotation[1]));
		mat = mat * Matrix4f::rotateZ(DegreesToRadians(rotation[2]));
		mat = mat * Matrix4f::translation(translation);

		object = new Transform(mat, object);
	}

	m_scene.getGroup()->modifyObject(currObj, object);

	m_ui.m_objList->item(currObj)->setText(m_ui.m_LEObjName->text());
}

void RayCaster::updateMaterial()
{
	if (m_isLoading) return;
	int currMat = m_ui.m_materialsList->currentRow();
	if (currMat < 0) return;

	bool isSpecChecked = m_ui.m_CBoxIsSpec->isChecked();

	m_ui.m_SBoxSpecColR->setEnabled(isSpecChecked);
	m_ui.m_SBoxSpecColG->setEnabled(isSpecChecked);
	m_ui.m_SBoxSpecColB->setEnabled(isSpecChecked);
	m_ui.m_SBoxShininess->setEnabled(isSpecChecked);

	Vector3f difColor = Vector3f(coloritof(m_ui.m_SBoxDifColR->value()), coloritof(m_ui.m_SBoxDifColG->value()), coloritof(m_ui.m_SBoxDifColB->value()));
	Vector3f specColor = (isSpecChecked) ? Vector3f(coloritof(m_ui.m_SBoxSpecColR->value()), coloritof(m_ui.m_SBoxSpecColG->value()), coloritof(m_ui.m_SBoxSpecColB->value())) : Vector3f::ZERO;
	float shininess = (isSpecChecked) ? m_ui.m_SBoxShininess->value() : 0;

	Material * newmat = new Material(difColor, specColor, shininess);

	// add texture if defined
	std::string filename = m_ui.m_LETextureFile->text().toStdString();
	struct stat buffer;
	if (filename != "" && stat(filename.c_str(), &buffer) == 0) // check file existence
	{
		newmat->loadTexture(filename.c_str());
	}

	m_scene.modifyMaterial(currMat, newmat);

	m_ui.m_materialsList->item(currMat)->setText(m_ui.m_LEMaterialName->text());
	m_ui.m_comboMaterial->setItemText(currMat, m_ui.m_LEMaterialName->text());
}

////////
// Slots
////////
#pragma region Slots

/////////
// Camera
/////////
void RayCaster::slotCamTypeChanged(bool isChecked)
{
	m_ui.m_dSBoxCamAngle->setEnabled(isChecked);
	updateCam();
}

void RayCaster::slotCamValueChanged(double value)
{
	updateCam();
}

void RayCaster::slotImageFileBrowse(bool clicked)
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Image file"), "C:/", tr("Image Files (*.png, *.jpg, *.bmp, *.tga)"));
	m_ui.m_LEImgFilename->setText(filename);
}

////////
// Light
////////
void RayCaster::slotLightAdd(bool clicked)
{
	m_scene.addLight(new PointLight(Vector3f(0), Vector3f(1)));
	m_ui.m_lightList->addItem(QString("Light"));
	m_ui.m_lightList->setCurrentRow(m_ui.m_lightList->count() - 1);
}

void RayCaster::slotLightRemove(bool clicked)
{
	qDeleteAll(m_ui.m_lightList->selectedItems());
	int currRow = m_ui.m_lightList->currentRow();
	(currRow < 0) ? m_scene.removeLight(0) : m_scene.removeLight(currRow);
	m_ui.m_lightList->setCurrentRow(m_ui.m_lightList->count() - 1);
}

void RayCaster::slotLightSelected(int currentRow)
{
	if (currentRow < 0) return;
	Vector3f dirPos;
	Vector3f color;

	PointLight * curlight = dynamic_cast<PointLight*> (m_scene.getLight(currentRow));
	if (curlight == NULL)
	{
		m_ui.m_rBtnDirLight->setChecked(true);
		DirectionalLight * dirlight = dynamic_cast<DirectionalLight*> (m_scene.getLight(currentRow));
		dirPos = dirlight->getDirection();
		color = dirlight->getColor() * 255;
	}
	else
	{
		m_ui.m_rBtnPointLight->setChecked(true);
		dirPos = curlight->getPosition();
		color = curlight->getColor() * 255;
	}
	m_isLoading = true;
	m_ui.m_LELightName->setText(m_ui.m_lightList->item(currentRow)->text());

	m_ui.m_dSBoxLightDirPosX->setValue(dirPos.x());
	m_ui.m_dSBoxLightDirPosY->setValue(dirPos.y());
	m_ui.m_dSBoxLightDirPosZ->setValue(dirPos.z());

	m_ui.m_SBoxLightColR->setValue(color.x());
	m_ui.m_SBoxLightColG->setValue(color.y());
	m_ui.m_SBoxLightColB->setValue(color.z());
	m_isLoading = false;
}

void RayCaster::slotLightValueChanged(double value)
{
	updateLight();
}

void RayCaster::slotLightNameChanged(const QString &)
{
	updateLight();
}

void RayCaster::slotLightTypeChanged(bool isChecked)
{
	updateLight();
}

//////////
// Objects
//////////
void RayCaster::slotObjectAdd(bool clicked)
{
	Object3D * object = NULL;
	Material * selectedMat = m_scene.getMaterial(m_ui.m_comboMaterial->currentIndex());
	int curTab = m_ui.m_objTab->currentIndex();

	if (m_ui.m_objTab->tabText(curTab) == "Sphere")
	{
		Vector3f center = Vector3f(m_ui.m_dSBoxSphereCenterX->value(), m_ui.m_dSBoxSphereCenterY->value(), m_ui.m_dSBoxSphereCenterZ->value());
		float radius = m_ui.m_dSBoxSphereRadius->value();
		object = new Sphere(center, radius, selectedMat);
	}
	else if (m_ui.m_objTab->tabText(curTab) == "Plane")
	{
		Vector3f normal = Vector3f(m_ui.m_dSBoxPlaneNormalX->value(), m_ui.m_dSBoxPlaneNormalY->value(), m_ui.m_dSBoxPlaneNormalZ->value());
		float offset = m_ui.m_dSBoxPlaneOffset->value();
		object = new Plane(normal, offset, selectedMat);
	}
	else if (m_ui.m_objTab->tabText(curTab) == "Mesh")
	{
		struct stat buffer;
		if (stat(m_ui.m_LEMeshFile->text().toStdString().c_str(), &buffer) == 0) // check file existence
		{
			object = new Mesh(m_ui.m_LEMeshFile->text().toStdString().c_str(), selectedMat);
		}
	}
	//Sphere* newObj = new Sphere(Vector3f(0), 1, m_scene.getMaterial());
	m_scene.getGroup()->addObject((Object3D*)object);
	m_ui.m_objList->addItem(QString("Object"));
	m_ui.m_objList->setCurrentRow(m_ui.m_objList->count() - 1);
}

void RayCaster::slotObjectRemove(bool clicked)
{
	qDeleteAll(m_ui.m_objList->selectedItems());
	int currRow = m_ui.m_objList->currentRow();
	(currRow < 0) ? m_scene.getGroup()->removeObject(0) : m_scene.getGroup()->removeObject(currRow);
	m_ui.m_objList->setCurrentRow(m_ui.m_objList->count() - 1);
}

void RayCaster::slotObjectSelected(int currentRow)
{
	if (currentRow < 0) return;
	//Object3D * obj = NULL;
	//Transform * transf = dynamic_cast<Transform*> (m_scene.getGroup()->getObject(currentRow));

	//if (transf != NULL) //obj is transform
	//{
	//	obj = transf->getObject();
	//}

	Object3D* currObj = m_scene.getGroup()->getObject(currentRow);
	m_isLoading = true;

	Transform * transf = dynamic_cast<Transform*> (currObj);
	if (transf != NULL) //obj is transform
	{
		currObj = transf->getObject();
		m_ui.m_CBObjTransform->setChecked(true);
		Matrix4f mat = transf->getTransformationMatrix();

	}

	Sphere * sphere = dynamic_cast<Sphere*> (currObj);
	if (sphere != NULL)
	{
		Vector3f center = sphere->getCenter();
		float radius = sphere->getRadius();

		m_ui.m_dSBoxSphereCenterX->setValue(center.x());
		m_ui.m_dSBoxSphereCenterY->setValue(center.y());
		m_ui.m_dSBoxSphereCenterZ->setValue(center.z());
		m_ui.m_dSBoxSphereRadius->setValue(radius);

		m_ui.m_objTab->setCurrentIndex(0);
	}

	Plane * plane = dynamic_cast<Plane*> (currObj);
	if (plane != NULL)
	{
		Vector3f normal = plane->getNormal();
		float offset = plane->getOffset();

		m_ui.m_dSBoxPlaneNormalX->setValue(normal.x());
		m_ui.m_dSBoxPlaneNormalY->setValue(normal.y());
		m_ui.m_dSBoxPlaneNormalZ->setValue(normal.z());
		m_ui.m_dSBoxPlaneOffset->setValue(offset);
		m_ui.m_objTab->setCurrentIndex(1);
	}

	Mesh * mesh = dynamic_cast<Mesh*> (currObj);
	if (mesh != NULL)
	{
		m_ui.m_LEMeshFile->setText(QString(mesh->getFilename().c_str()));
		m_ui.m_objTab->setCurrentIndex(2);
	}

	
	
	m_ui.m_LEObjName->setText(m_ui.m_objList->item(currentRow)->text());

	m_isLoading = false;
}

void RayCaster::slotObjectValueChanged(double value)
{
	updateObject();
}

void RayCaster::slotObjectNameChanged(const QString &)
{
	updateObject();
}

void RayCaster::slotObjectTransChecked(bool isChecked)
{
	updateObject();
}

void RayCaster::slotObjectMaterialChanged(int value)
{
	updateObject();
}

void RayCaster::slotObjectMeshBrowse(bool clicked)
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Mesh file"), "C:/", tr("Object Files (*.obj)"));
	m_ui.m_LEMeshFile->setText(filename);

}

void RayCaster::slotObjectChanged(int index)
{
	updateObject();
}

///////////
// Material
///////////
void RayCaster::slotMaterialAdd(bool clicked)
{
	m_scene.addMaterial(new Material(Vector3f(0)));
	m_ui.m_materialsList->addItem(QString("Material"));
	m_ui.m_materialsList->setCurrentRow(m_ui.m_materialsList->count() - 1);
	m_ui.m_comboMaterial->addItem("Material");
}

void RayCaster::slotMaterialRemove(bool clicked)
{
	qDeleteAll(m_ui.m_materialsList->selectedItems());
	int currRow = m_ui.m_materialsList->currentRow();
	(currRow < 0) ? m_scene.removeMaterial(0) : m_scene.removeMaterial(currRow);
	(currRow < 0) ? m_ui.m_comboMaterial->removeItem(0) : m_ui.m_comboMaterial->removeItem(currRow);
	m_ui.m_materialsList->setCurrentRow(m_ui.m_materialsList->count() - 1);
}

void RayCaster::slotMaterialSelected(int currentRow)
{
	if (currentRow < 0) return;

	Material * currMat = m_scene.getMaterial(currentRow);

	float shininess = currMat->getShininess();
	Vector3f diffColor = currMat->getDiffuseColor() * 255;
	Vector3f specColor = currMat->getSpecularColor() * 255;

	m_isLoading = true;
	m_ui.m_LEMaterialName->setText(m_ui.m_materialsList->item(currentRow)->text());

	m_ui.m_SBoxDifColR->setValue(diffColor.x());
	m_ui.m_SBoxDifColG->setValue(diffColor.y());
	m_ui.m_SBoxDifColB->setValue(diffColor.z());

	m_ui.m_SBoxSpecColR->setValue(specColor.x());
	m_ui.m_SBoxSpecColG->setValue(specColor.y());
	m_ui.m_SBoxSpecColB->setValue(specColor.z());

	m_ui.m_SBoxShininess->setValue(shininess);

	bool isSpec = (shininess != 0 || specColor != Vector3f::ZERO);

	m_ui.m_CBoxIsSpec->setChecked(isSpec);
	m_ui.m_SBoxSpecColR->setEnabled(isSpec);
	m_ui.m_SBoxSpecColG->setEnabled(isSpec);
	m_ui.m_SBoxSpecColB->setEnabled(isSpec);

	m_ui.m_SBoxShininess->setEnabled(isSpec);

	m_isLoading = false;
}

void RayCaster::slotMaterialValueChanged(double value)
{
	updateMaterial();
}

void RayCaster::slotMaterialValueChanged(int value)
{
	updateMaterial();
}

void RayCaster::slotMaterialNameChanged(const QString &)
{
	updateMaterial();
}

void RayCaster::slotMaterialSpecChecked(bool isChecked)
{
	updateMaterial();
}

void RayCaster::slotMaterialBrowseTextFile(bool clicked)
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Load Texture file"), "C:/", tr("Texture Files (*.png, *.jpg, *.bmp, *.tga)"));
	m_ui.m_LETextureFile->setText(filename);
}

/////////
// Render
/////////
void RayCaster::slotRender(bool clicked)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	int width = m_ui.m_SBoxImgW->value();
	int height = m_ui.m_SBoxImgH->value();
	m_scene.setBackgroundColor(Vector3f(coloritof(m_ui.m_SBoxBackColR->value()), coloritof(m_ui.m_SBoxBackColG->value()), coloritof(m_ui.m_SBoxBackColB->value())));
	m_scene.setAmbientLight(Vector3f(coloritof(m_ui.m_SBoxAmbLightR->value()), coloritof(m_ui.m_SBoxAmbLightG->value()), coloritof(m_ui.m_SBoxAmbLightB->value())));
	Image image(width, height);
	m_ui.m_pBarRendering->setHidden(false);

	//float currt;
	//float minT = FLT_MAX;
	//float maxT = -FLT_MAX;

	Vector3f dirToLight;
	Vector3f lightCol;
	float distToLight;

	for (float x = 0.f; x < width; ++x)
	{
		for (float y = 0.f; y < height; ++y)
		{
			Hit hit;
			Ray ray = m_scene.getCamera()->generateRay(Vector2f(2 * x / (width - 1) - 1, 2 * y / (height - 1) - 1));
			m_scene.getGroup()->intersect(ray, hit, m_scene.getCamera()->getTMin());
			Vector3f pixCol(0.f, 0.f, 0.f);
			if (hit.getT() < FLT_MAX)
			{
				for (int i = 0; i < m_scene.getNumLights(); ++i)
				{
					m_scene.getLight(i)->getIllumination(ray.pointAtParameter(hit.getT()), dirToLight, lightCol, distToLight);
					pixCol += hit.getMaterial()->Shade(ray, hit, dirToLight, lightCol);
				}

				pixCol += m_scene.getAmbientLight() * hit.getMaterial()->getDiffuseColor();
			}
			else
			{
				pixCol = m_scene.getBackgroundColor();
			}

			image.SetPixel(x, y, pixCol);
			m_ui.m_pBarRendering->setValue((int)((x * height + y) * 100) / (width * height));
		}
	}
	m_ui.m_pBarRendering->setValue(100);
	image.SaveImage(m_ui.m_LEImgFilename->text().toStdString().c_str());
	QImage qimage(m_ui.m_LEImgFilename->text());
	//QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
	m_grScene->clear();
	m_grScene->addPixmap(QPixmap::fromImage(qimage));
	m_ui.m_graphicView->show();
	m_ui.m_pBarRendering->setValue(0);
	m_ui.m_pBarRendering->setHidden(true);
	QApplication::restoreOverrideCursor();
}
#pragma endregion

//////////
// Utility
//////////
float coloritof(int i)
{
	return (float)(i / 255.f);
}

int colorftoi(float f)
{
	return (int)(f * 255);
}