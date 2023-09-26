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
	// Transform 클래스는 GameObject* 를 저장합니다.
	m_transform = new Transform(this);
	// CreateComponent로 생성하지 않았으므로 직접 Awake()를 호출합니다.
	m_transform->Awake();

	// Transform을 설정합니다.
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
	// 트랜스폼 컴포넌트를 제거 요청합니다.
	m_transform->Destroy();
	// 게임오브젝트에 부착된 모든 컴포넌트를 제거합니다.
	for (auto& comp : m_components)
		comp->Destroy();
	BASE_SAFE_DELETE(m_transform);
	for (auto& comp : m_components)
		BASE_SAFE_DELETE(comp);
	// 게임오브젝트의 컴포넌트 리스트를 비웁니다.
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
