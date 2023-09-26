#pragma once
#ifndef __Component_h__
#define __Component_h__

#include "Object.h"

class Transform;
class GameObject;
class ComponentManager;

// Behavior 클래스를 구현하기 위한 중간 클래스입니다.
// 사용자 지정 컴포넌트를 구현하시려면 대신 Behavior 클래스를 상속받으십시오.
class Component : public Object
{
	friend class GameObject;
	friend class Machine;
	friend class Renderer2D;
	friend class Body2D;
	friend class Collider2D;

private:
	// 컴포넌트가 처음 생성되었을 때 ture입니다.
	// 이후 첫 Start(), OnEnable() 호출을 위해 사용되며 Start(), OnEnable() 이후에 false가 됩니다.
	bool m_awaked;
	int m_executionOrder;
	bool m_isRenderer;
	bool m_isBody2D;
	bool m_isCollider2D;

protected:
	// 컴포넌트가 부착되어 있는 트랜스폼입니다.
	Transform* m_transform;

protected:
	Component();

protected:
	virtual ~Component();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

	virtual void OnEnable() override = 0;
	virtual void OnDisable() override = 0;
	virtual void OnDestroy() override = 0;

public:
	const bool& isAwaked() const;
	void AwakedJobDone();

	Transform* transform() const;
	GameObject* gameObject() const;

public:
	const int& executionOrder() const;

protected:
	void SetExecutionOrder(int order);
};

inline const bool& Component::isAwaked() const
{
	return m_awaked;
}

inline void Component::AwakedJobDone()
{
	m_awaked = false;
}

inline const int& Component::executionOrder() const
{
	return m_executionOrder;
}

inline void Component::SetExecutionOrder(int order)
{
	m_executionOrder = order;
}

#endif
