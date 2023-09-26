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
	// 오브젝트가 파괴되기 직전에 호출됩니다.
	// object는 파괴될 오브젝트입니다.
	Delegate<void, Object*> OnDestroyCallback;

	// void OnEnableChagneCallback(bool enable, Object* object)
	// 활성화 상태가 변경될 때 호출됩니다.
	// enable은 변경된 상태입니다.
	// object는 파괴될 오브젝트입니다.
	Delegate<void, bool, Object*> OnEnableChangeCallback;
};

#endif
