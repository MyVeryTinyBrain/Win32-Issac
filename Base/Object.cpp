#include "BaseStdafx.h"
#include "Object.h"

Object::Object()
{
	m_enable = true;
	m_shouldDestroy = false;
}

Object::~Object()
{
}

void Object::Destroy()
{
	if (m_shouldDestroy == true) return;
	m_shouldDestroy = true;
	setEnable(false);
	OnDestroy();
	OnDestroyCallback(this);
}

const bool& Object::shouldDestroy() const
{
	return m_shouldDestroy;
}

const bool& Object::enable() const
{
	return m_enable;
}

void Object::setEnable(const bool& enable)
{
	if (m_enable != enable)
	{
		m_enable = enable;
		if (enable) OnEnable();
		else OnDisable();
		OnEnableChangeCallback(enable, this);
	}
}
