#include "BaseStdafx.h"
#include "Component.h"
#include "Transform.h"
#include "ExecutionOrder.h"

Component::Component() : Object()
{
	m_awaked = true;
	m_transform = nullptr;
	m_isRenderer = false;
	m_isBody2D = false;
	m_isCollider2D = false;
	m_executionOrder = EX_ORDER_DEFAULT;
}

Component::~Component()
{	
}

Transform* Component::transform() const
{
	return m_transform;
}

GameObject* Component::gameObject() const
{
	return m_transform->gameObject();
}
