#include "stdafx.h"
#include "MouseTracker.h"

void MouseTracker::Awake()
{
}

void MouseTracker::Start()
{
}

void MouseTracker::Update()
{
}

void MouseTracker::LateUpdate()
{
	Vector2 pt = Input::GetMousePointInScreen();
	const Matrix3x3& m1 = Camera2D::mainCamera()->screenToCameraMatrix();
	const Matrix3x3& m2 = Camera2D::mainCamera()->cameraToWorldMatrix();
	pt = m2 * m1 * pt;
	transform()->setPosition(pt);
}

void MouseTracker::OnEnable()
{
}

void MouseTracker::OnDisable()
{
}

void MouseTracker::OnDestroy()
{
}
