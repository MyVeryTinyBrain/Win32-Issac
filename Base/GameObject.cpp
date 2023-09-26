#include "BaseStdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "GameObjectTag.h"
#include "GameObjectLayer.h"

std::vector<GameObject*> GameObject::g_gameObjects;

GameObject::GameObject(Transform* parent) : 
	GameObject(Vector2::zero(), 0, Vector2::one(), parent)
{
}

GameObject::GameObject(Vector2 position, Transform* parent) : 
	GameObject(position, 0, Vector2::one(), parent)
{
}

GameObject::GameObject(Vector2 position, float angle, Transform* parent) :
	GameObject(position, angle, Vector2::one(), parent)
{
}

GameObject::GameObject(Vector2 position, float angle, Vector2 size, Transform* parent)
{
	// Transform Ŭ������ GameObject* �� �����մϴ�.
	m_transform = new Transform(this);
	// CreateComponent�� �������� �ʾ����Ƿ� ���� Awake()�� ȣ���մϴ�.
	m_transform->Awake();

	// Transform�� �����մϴ�.
	m_transform->setPosition(position);
	m_transform->setAngle(angle);
	m_transform->setSize(size);
	if (parent) m_transform->setParent(parent);

	m_tag = GO_TAG_DEFAULT;
	m_layer = GO_LAYER_DEFAULT;

	g_gameObjects.push_back(this);
}

GameObject::~GameObject()
{
	// Ʈ������ ������Ʈ�� ���� ��û�մϴ�.
	m_transform->Destroy();
	// ���ӿ�����Ʈ�� ������ ��� ������Ʈ�� �����մϴ�.
	for (auto& comp : m_components)
		comp->Destroy();
	BASE_SAFE_DELETE(m_transform);
	for (auto& comp : m_components)
		BASE_SAFE_DELETE(comp);
	// ���ӿ�����Ʈ�� ������Ʈ ����Ʈ�� ���ϴ�.
	m_components.clear();
}

Transform* GameObject::transform() const
{
	return m_transform;
}

bool GameObject::active() const
{
	return enable() && m_transform->parentEnable();
}

const unsigned char& GameObject::tag() const
{
	return m_tag;
}

void GameObject::setTag(const unsigned char& Tag)
{
	m_tag = Tag;
}

const unsigned char& GameObject::layer() const
{
	return m_layer;
}

void GameObject::setLayer(const unsigned char& Layer)
{
	m_layer = Layer;
}

void GameObject::OnEnable()
{
	m_transform->setEnable(true);
}

void GameObject::OnDisable()
{
	m_transform->setEnable(false);
}

void GameObject::OnDestroy()
{

}

void GameObject::RemoveComponent(Component* component)
{
	component->Destroy();
}

std::vector<Component*>* GameObject::GetComponents()
{
	return &m_components;
}
