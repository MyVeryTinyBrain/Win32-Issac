#pragma once
#ifndef __Machine_h__
#define __Machine_h__

#include "Renderer2D.h"
#include "Renderer2DTag.h"
#include "Physics2D.h"
#include "GameObjectLayer.h"

class Component;
class GameObject;
class HDCEx;
class Body2D;
class Collider2D;

// �޸𸮿� �����ϴ� ��� ������Ʈ���� ������ ������ �ϵ��� �մϴ�.
// �Լ��� �غ�� ������ �����ϵ��� �մϴ�.
class Machine
{
	std::vector<Component*> m_updateTargets;
	std::vector<Renderer2D*> m_renderTargets[RD_TAG_MAX];
	std::vector<Body2D*> m_bodyTargets;
	std::vector<Collider2D*> m_colliderTargets[GO_LAYER_MAX];

public:
	Machine();
	~Machine();

public:
	// ��� ������Ʈ�� ����, ������Ʈ, �� ������Ʈ�� �����մϴ�.
	void UpdateAll();
	// ��� ������Ʈ�� �׸��⸦ �����մϴ�.
	void Render(HDC hdc);

	// ��� ���ӿ�����Ʈ�� ������Ʈ�� �����մϴ�.
	// ���� �����ϰų� ���α׷��� ������ �� ȣ���ϵ��� �մϴ�.
	void DeleteAllGameObjectsAndComponent();
	void Reset();

private:
	void ComponentsDestroyAndSetTargets(GameObject* gameObject);
};

#endif
