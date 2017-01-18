#pragma once
#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <QtWidgets/QMainWindow>
#include "ui_RayCaster.h"
#include "Scene.h"

///////////////////////////
// RayCastr UI Header
//
// Nicolas Bordes - 11/2016
///////////////////////////

class RayCaster : public QMainWindow
{
    Q_OBJECT

public:
    RayCaster(QWidget *parent = Q_NULLPTR);

private slots:
	// Camera
	void slotCamTypeChanged(bool isChecked);
	void slotCamValueChanged(double value);
	void slotImageFileBrowse(bool clicked);
	// Light
	void slotLightAdd(bool clicked);
	void slotLightRemove(bool clicked);
	void slotLightSelected(int currentRow);
	void slotLightValueChanged(double value);
	void slotLightNameChanged(const QString &);
	void slotLightTypeChanged(bool isChecked);
	// Object
	void slotObjectAdd(bool clicked);
	void slotObjectRemove(bool clicked);
	void slotObjectSelected(int currentRow);
	void slotObjectValueChanged(double value);
	void slotObjectNameChanged(const QString &);
	void slotObjectTransChecked(bool isChecked);
	void slotObjectMaterialChanged(int value);
	void slotObjectMeshBrowse(bool clicked);
	void slotObjectChanged(int index);
	// Material
	void slotMaterialAdd(bool clicked);
	void slotMaterialRemove(bool clicked);
	void slotMaterialSelected(int currentRow);
	void slotMaterialValueChanged(double value);
	void slotMaterialValueChanged(int value);
	void slotMaterialNameChanged(const QString &);
	void slotMaterialSpecChecked(bool isChecked);
	void slotMaterialBrowseTextFile(bool clicked);
	// Render
	void slotRender(bool clicked);

private:
    Ui::RayCasterClass m_ui;
	Scene m_scene;
	bool m_isLoading;
	QGraphicsScene* m_grScene;

	void updateCam();
	void updateLight();
	void updateObject();
	void updateMaterial();
};

#endif //RAYCASTER_H 
