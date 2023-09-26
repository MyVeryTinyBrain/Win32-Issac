#include "BaseStdafx.h"
#include "Input.h"
#include "Camera2D.h"

void Input::SetKeyDown(unsigned char key)
{
	m_hasDown = true;
	m_downState[key] = true;
	m_keyState[key] = true;
}

void Input::SetKeyUp(unsigned char key)
{
	m_hasUp = true;
	m_upState[key] = true;
	m_keyState[key] = false;
}

void Input::SetUsed()
{
	if (m_hasDown)
		ZeroMemory(m_downState, sizeof(m_downState));
	if (m_hasUp)
		ZeroMemory(m_upState, sizeof(m_upState));
	m_hasDown = false;
	m_hasUp = false;
}

Input Input::g_instance;

Input* Input::instance()
{
	return &g_instance;
}

const bool& Input::GetKey(const Key& key)
{
	return g_instance.m_keyState[(unsigned char)key];
}

const bool& Input::GetKeyDown(const Key& key)
{
	return g_instance.m_downState[(unsigned char)key];
}

const bool& Input::GetKeyUp(const Key& key)
{
	return g_instance.m_upState[(unsigned char)key];
}

Vector2 Input::GetMousePointInScreen()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(*BaseGlobal::pHWND, &pt);
	return { (float)pt.x,(float)pt.y };
}

Vector2 Input::GetMousePointInWorld()
{
	Vector2 pt = Input::GetMousePointInScreen();
	const Matrix3x3& m1 = Camera2D::mainCamera()->screenToCameraMatrix();
	const Matrix3x3& m2 = Camera2D::mainCamera()->cameraToWorldMatrix();
	pt = m2 * m1 * pt;
	return pt;
}
