#pragma once
#ifndef __GameObject_h__
#define __GameObject_h__

#define _TMP_COMP_T_	template <typename ComponentType>

#include "Object.h"
#include "Transform.h"

#include <stack>

class Component;
class GameObjectManager;

class GameObject : public Object
{
	friend class Transform;
	friend class GameObjectManager;
	friend class Machine;

private:
	static std::vector<GameObject*> g_gameObjects;

private:
	Transform* m_transform;
	std::vector<Component*> m_components;
	unsigned char m_tag;
	unsigned char m_layer;

public:
	GameObject(Transform* parent = nullptr);
	GameObject(Vector2 position, Transform* parent = nullptr);
	GameObject(Vector2 posiition, float angle, Transform* parent = nullptr);
	GameObject(Vector2 position, float angle, Vector2 size, Transform* parent = nullptr);

protected:
	// ���ӿ�����Ʈ�� ������ Destroy() �Լ��� ����մϴ�.
	// ���� �����Ϸ��� �õ����� ���ʽÿ�.
	virtual ~GameObject();

public:
	// ���ӿ�����Ʈ�� Ʈ�������� ��ȯ�մϴ�.
	Transform* transform() const;
	bool active() const;

	const unsigned char& tag() const;
	void setTag(const unsigned char& Tag);
	const unsigned char& layer() const;
	void setLayer(const unsigned char& Layer);

private:
	std::vector<Component*>* GetComponents();

private:
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

public:
	// �� ���ӿ�����Ʈ�� ������Ʈ�� ���� ������ �����մϴ�.
	_TMP_COMP_T_ ComponentType* AddComponent();

	// �� ���ӿ�����Ʈ���� ������Ʈ�� �����մϴ�.
	void RemoveComponent(Component* component);
	// �� ���ӿ�����Ʈ���� ������Ʈ�� �����մϴ�.
	_TMP_COMP_T_ void RemoveComponent();

	// �� ���ӿ�����Ʈ�� ������ ������Ʈ�� ��ȯ�մϴ�.
	_TMP_COMP_T_ ComponentType* GetComponent();

	// �� ���ӿ�����Ʈ�� ������ ������Ʈ���� ��ȯ�մϴ�.
	_TMP_COMP_T_ size_t GetComponents(std::vector<ComponentType*>* out_vec);

	// �� ���ӿ�����Ʈ�� �ڽĵ鿡 ������ ������Ʈ�� ��ȯ�մϴ�.
	_TMP_COMP_T_ size_t GetComponentsInChild(std::vector<ComponentType*>* out_vec);

private:
	// �� ������Ʈ�� ������ �� �ִ� ������Ʈ�� �����մϴ�.
	_TMP_COMP_T_ ComponentType* CreateComponent();
};

// Template functions
// ============================================================================================

_TMP_COMP_T_ ComponentType* GameObject::AddComponent()
{
	ComponentType* component = CreateComponent<ComponentType>();
	m_components.push_back(static_cast<Component*>(component));
	return component;
}

_TMP_COMP_T_ void GameObject::RemoveComponent()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = *it;
		ComponentType* casting = dynamic_cast<ComponentType*>(component);
		if (casting)
		{
			m_components.erase(it);
			return;
		}
	}
}

_TMP_COMP_T_ ComponentType* GameObject::GetComponent()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = *it;
		ComponentType* casting = dynamic_cast<ComponentType*>(component);
		if (casting)
			return static_cast<ComponentType*>(component);
	}
	return nullptr;
}

_TMP_COMP_T_ ComponentType* GameObject::CreateComponent()
{
	Component* component = new ComponentType();
	component->m_transform = m_transform;
	component->Awake();
	return static_cast<ComponentType*>(component);
}

_TMP_COMP_T_ size_t GameObject::GetComponents(std::vector<ComponentType*>* out_vec)
{
	out_vec->clear();

	for (auto& comp : m_components)
	{
		ComponentType* casting = dynamic_cast<ComponentType*>(comp);
		if (casting)
			out_vec->push_back(casting);
	}

	return out_vec->size();
}

_TMP_COMP_T_ size_t GameObject::GetComponentsInChild(std::vector<ComponentType*>* out_vec)
{
	out_vec->clear();

	std::stack<Transform*> s;
	s.push(m_transform);
	while (!s.empty())
	{
		Transform* t = s.top();
		s.pop();

		for (auto& comp : t->gameObject()->m_components)
		{
			ComponentType* casting = dynamic_cast<ComponentType*>(comp);
			if (casting)
				out_vec->push_back(casting);
		}

		for (auto& child : t->m_childs)
			s.push(child);
	}

	return out_vec->size();
}

// =============================================================================================

#endif
