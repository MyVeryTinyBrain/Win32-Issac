#pragma once
#ifndef __Object_h__
#define __Object_h__

#include "Delegate.h"

class Object
{
	bool m_enable;
	bool m_shouldDestroy;

protected:
	Object();

protected:
	virtual ~Object();

public:
	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;
	virtual void OnDestroy() = 0;

	void Destroy();
	const bool& shouldDestroy() const;
	const bool& enable() const;
	void setEnable(const bool& enable);

public:
	// void OnDestroyCallback(Object* object)
	// ������Ʈ�� �ı��Ǳ� ������ ȣ��˴ϴ�.
	// object�� �ı��� ������Ʈ�Դϴ�.
	Delegate<void, Object*> OnDestroyCallback;

	// void OnEnableChagneCallback(bool enable, Object* object)
	// Ȱ��ȭ ���°� ����� �� ȣ��˴ϴ�.
	// enable�� ����� �����Դϴ�.
	// object�� �ı��� ������Ʈ�Դϴ�.
	Delegate<void, bool, Object*> OnEnableChangeCallback;
};

#endif
