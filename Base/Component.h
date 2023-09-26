#pragma once
#ifndef __Component_h__
#define __Component_h__

#include "Object.h"

class Transform;
class GameObject;
class ComponentManager;

// Behavior Ŭ������ �����ϱ� ���� �߰� Ŭ�����Դϴ�.
// ����� ���� ������Ʈ�� �����Ͻ÷��� ��� Behavior Ŭ������ ��ӹ����ʽÿ�.
class Component : public Object
{
	friend class GameObject;
	friend class Machine;
	friend class Renderer2D;
	friend class Body2D;
	friend class Collider2D;

private:
	// ������Ʈ�� ó�� �����Ǿ��� �� ture�Դϴ�.
	// ���� ù Start(), OnEnable() ȣ���� ���� ���Ǹ� Start(), OnEnable() ���Ŀ� false�� �˴ϴ�.
	bool m_awaked;
	int m_executionOrder;
	bool m_isRenderer;
	bool m_isBody2D;
	bool m_isCollider2D;

protected:
	// ������Ʈ�� �����Ǿ� �ִ� Ʈ�������Դϴ�.
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
