#include "BaseStdafx.h"
#include "Transform.h"
#include "GameObject.h"
#include <stack>

Transform::Transform(GameObject* gameObject) : Behavior()
{
	m_parentEnable = true;
	m_transform = this;
	m_gameObject = gameObject;
	m_position = Vector2::zero();
	m_angle = 0;
	m_size = Vector2::one();
	m_localPosition = Vector2::zero();
	m_localAngle = 0;
	m_localSize = Vector2::one();
	m_parent = nullptr;
	m_childs.clear();
}

Transform::~Transform()
{
}

void Transform::Awake()
{
}

void Transform::Start()
{
}

void Transform::Update()
{
}

void Transform::LateUpdate()
{
}

void Transform::OnEnable()
{
	m_gameObject->setEnable(true);

	std::stack<Transform*> s;
	s.push(this);
	while (!s.empty())
	{
		Transform* t = s.top();
		s.pop();

		if (t->enable() == false) continue;
		t->m_parentEnable = true;
		for (auto& child : t->m_childs)
			s.push(child);
	}
	UpdateSubEnable();
}

void Transform::OnDisable()
{
	m_gameObject->setEnable(false);

	std::stack<Transform*> s;
	s.push(this);
	while (!s.empty())
	{
		Transform* t = s.top();
		s.pop();

		if (t->m_parentEnable == false) continue;
		t->m_parentEnable = false;
		for (auto& child : t->m_childs)
			s.push(child);
	}
	UpdateSubEnable();
}

void Transform::OnDestroy()
{
	gameObject()->Destroy();
	for (auto& child : m_childs)
		child->Destroy();

	if (m_parent)
		m_parent->detachChild(this);
	detachAllChilds();
}

GameObject* Transform::gameObject()
{
	return m_gameObject;
}

Matrix3x3 Transform::localToWorldMatrix() const
{
	Matrix3x3 t = Matrix3x3::Translate(m_position.x, m_position.y);
	Matrix3x3 r = Matrix3x3::Rotate(m_angle);
	Matrix3x3 s = Matrix3x3::Scale(m_size.x, m_size.y);
	return t * r * s;
}

Matrix3x3 Transform::worldToLocalMatrix() const
{
	Matrix3x3 t = Matrix3x3::Translate(-m_position.x, -m_position.y);
	Matrix3x3 r = Matrix3x3::Rotate(-m_angle);
	Matrix3x3 s = Matrix3x3::Scale(1.0f / m_size.x, 1.0f / m_size.y);
	return s * r * t;
}

Vector2 Transform::up() const
{
	return Matrix3x3::Rotate(m_angle) * Vector2::up();
}

Vector2 Transform::right() const
{
	return Matrix3x3::Rotate(m_angle) * Vector2::right();
}

Transform* Transform::root() const
{
	const Transform* cur = this;
	while (cur->m_parent)
	{
		cur = cur->m_parent;
	}
	return const_cast<Transform*>(cur);
}

void Transform::ForceUpdate(Transform* _root)
{
	std::stack<Transform*> s;
	if (_root) s.push(_root);
	else s.push(root());
	while (!s.empty())
	{
		Transform* t = s.top();
		s.pop();

		for (auto& child : t->m_childs)
		{
			child->UpdateGlobalPosition();
			child->UpdateGlobalAngle();
			child->UpdateGlobalSize();
			s.push(child);
		}
	}
}

size_t Transform::childCount() const
{
	return m_childs.size();
}

Transform* Transform::getChild(size_t index) const
{
	return m_childs[index];
}

void Transform::addChild(Transform* transform)
{
	transform->m_parent = this;
	transform->UpdateLocalPosition();
	transform->UpdateLocalAngle();
	transform->UpdateLocalSize();
	transform->UpdateSubEnable();
	m_childs.push_back(transform);
}

void Transform::detachChild(Transform* transform)
{
	if (!transform)
		return;
	transform->m_parent = nullptr;
	transform->UpdateLocalPosition();
	transform->UpdateLocalAngle();
	transform->UpdateLocalSize();
	transform->UpdateSubEnable();
	auto iterator = std::find(m_childs.begin(), m_childs.end(), transform);
	m_childs.erase(iterator);
}

void Transform::detachAllChilds()
{
	for (auto& child : m_childs)
	{
		child->m_parent = nullptr;
		child->UpdateLocalPosition();
		child->UpdateLocalAngle();
		child->UpdateLocalSize();
		child->UpdateSubEnable();
	}
	m_childs.clear();
}

Transform* Transform::parent() const
{
	return m_parent;
}

void Transform::setParent(Transform* transform)
{
	if (m_parent == transform)
		return;

	if (m_parent)
		m_parent->detachChild(this);

	if (transform)
		transform->addChild(this);
	else
		m_parent = nullptr;
}

const bool& Transform::parentEnable() const
{
	return m_parentEnable;
}

const Vector2& Transform::position() const
{
	return m_position;
}

const float& Transform::angle() const
{
	return m_angle;
}

const Vector2& Transform::size() const
{
	return m_size;
}

const Vector2& Transform::localPosition() const
{
	return m_localPosition;
}

const float& Transform::localAngle() const
{
	return m_localAngle;
}

const Vector2& Transform::localSize() const
{
	return m_localSize;
}

void Transform::setPosition(const Vector2& position)
{
	m_position = position;
	UpdateLocalPosition();
	ForceUpdate();
}

void Transform::setAngle(const float& radian)
{
	m_angle = radian;
	UpdateLocalAngle();
	ForceUpdate();
}

void Transform::setSize(const Vector2& size)
{
	m_size = size;
	UpdateLocalSize();
	ForceUpdate();
}

void Transform::setLocalPosition(const Vector2& localPosition)
{
	m_localPosition = localPosition;
	UpdateGlobalPosition();
	ForceUpdate();
}

void Transform::setLocalAngle(const float& localRadian)
{
	m_localAngle = localRadian;
	UpdateGlobalAngle();
	ForceUpdate();
}

void Transform::setLocalSize(const Vector2& localSize)
{
	m_localSize = localSize;
	UpdateGlobalSize();
	ForceUpdate();
}

void Transform::UpdateGlobalPosition()
{
	if (m_parent)
		m_position = m_parent->localToWorldMatrix() * m_localPosition;
	else
		m_position = m_localPosition;
}

void Transform::UpdateGlobalAngle()
{
	if (m_parent)
		m_angle = m_parent->m_angle + m_localAngle;
	else
		m_angle = m_localAngle;
}

void Transform::UpdateGlobalSize()
{
	if (m_parent)
		m_size = Vector2(m_localSize.x * m_parent->m_size.x, m_localSize.y * m_parent->m_size.y);
	else
		m_size = m_localSize;
}

void Transform::UpdateLocalPosition()
{
	if (m_parent)
		m_localPosition = m_parent->worldToLocalMatrix() * m_position;
	else
		m_localPosition = m_position;
}

void Transform::UpdateLocalAngle()
{
	if (m_parent)
		m_localAngle = m_angle - m_parent->m_angle;
	else
		m_localAngle = m_angle;
}

void Transform::UpdateLocalSize()
{
	if (m_parent)
		m_localSize = Vector2(m_size.x / m_parent->m_size.x, m_size.y / m_parent->m_size.y);
	else
		m_localSize = m_size;
}

void Transform::UpdateSubEnable()
{
	if (m_parent)
	{
		if (m_parent->enable() == false || m_parent->m_parentEnable == false)
			m_parentEnable = false;
		else
			m_parentEnable = true;
	}
	else
	{
		m_parentEnable = true;
	}
}