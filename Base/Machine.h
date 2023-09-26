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

// 메모리에 존재하는 모든 오브젝트들이 지정된 동작을 하도록 합니다.
// 함수는 준비된 순서로 실행하도록 합니다.
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
	// 모든 오브젝트의 삭제, 업데이트, 후 업데이트를 진행합니다.
	void UpdateAll();
	// 모든 오브젝트의 그리기를 진행합니다.
	void Render(HDC hdc);

	// 모든 게임오브젝트와 컴포넌트를 제거합니다.
	// 씬을 변경하거나 프로그램을 종료할 때 호출하도록 합니다.
	void DeleteAllGameObjectsAndComponent();
	void Reset();

private:
	void ComponentsDestroyAndSetTargets(GameObject* gameObject);
};

#endif
