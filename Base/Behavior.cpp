#include "BaseStdafx.h"
#include "Behavior.h"
#include "Transform.h"

Behavior::Behavior() : Component()
{
}

Behavior::~Behavior()
{
}

Transform* Behavior::transform() const
{
	return m_transform;
}

GameObject* Behavior::gameObject() const
{
	return m_transform->gameObject();
}
