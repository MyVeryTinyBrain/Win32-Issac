#pragma once
#ifndef __Camera_h__
#define __Camera_h__

#include "Behavior.h"

class HDCEx;

class Camera2D : public Behavior
{
	static Camera2D* g_mainCamera;
	static std::vector<Camera2D*> g_cameras;

private:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	HDCEx* m_HDCEx = nullptr;
	float m_horizontal = 0;
	float m_vertical = 0;
	float m_halfWidth = 0;
	float m_halfHeight = 0;

	Matrix3x3 m_worldToCameraMatrix;
	Matrix3x3 m_cameraToWorldMatrix;
	Matrix3x3 m_cameraToScreenMatrix;
	Matrix3x3 m_screenToCameraMatrix;

public:
	const Matrix3x3& worldToCameraMatrix() const;
	const Matrix3x3& cameraToWorldMatrix() const;
	const Matrix3x3& cameraToScreenMatrix() const;
	const Matrix3x3& screenToCameraMatrix() const;

	const float& horizontal() const;
	void setHorizontal(const float& Horizontal);
	const float& vertical() const;
	void setVertical(const float& Vertical);
	const float& halfWidth() const;
	const float& halfHeight() const;

	HDCEx* hDCEx() const;

public:
	static Camera2D* mainCamera();
	static std::vector<Camera2D*>* getCameras();

private:
	void SetHDCEx();
	void MakeWorldToCameraMatrix();
	void MakeCameraToWorldMatrix();
	void MakeCameraToScrenMatrix();
	void MakeScreenToCameraMatrix();
};

#endif
