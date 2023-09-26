#include "BaseStdafx.h"
#include "Machine.h"
#include "GameObject.h"
#include "Component.h"
#include "HDCEx.h"
#include "Camera2D.h"
#include "BitmapManager.h"
#include "SpriteManager.h"
#include "Collider2D.h"
#include "Body2D.h"

Machine::Machine()
{
	DeleteAllGameObjectsAndComponent();
	Reset();
}

Machine::~Machine()
{
	DeleteAllGameObjectsAndComponent();
	Reset();
}

void Machine::UpdateAll()
{
	// 파괴되어야 할 오브젝트들을 파괴합니다.
	// 업데이트 되어야 할 오브젝트들을 벡터에 추가합니다.
	// ===================================================================================================================
	// 모든 게임오브젝트 리스트를 순회합니다.
	for (auto it = GameObject::g_gameObjects.begin(); it != GameObject::g_gameObjects.end();)
	{
		GameObject* gameObject = *it;
		// 해당 게임오브젝트가 파괴되어야 한다면 파괴하고 리스트에서 제거합니다.
		if (gameObject->shouldDestroy())
		{
			it = GameObject::g_gameObjects.erase(it);
			BASE_SAFE_DELETE(gameObject);
		}
		// 파괴될 필요가 없다면 해당 게임오브젝트의 컴포넌트들을
		// 업데이트 리스트와 렌더 리스트에 조건에 따라 등록합니다.
		else
		{
			ComponentsDestroyAndSetTargets(gameObject);
			++it;
		}
	}
	// ===================================================================================================================

	// 업데이트 리스트를 업데이트 순서에 따라 정렬합니다.
	// ===================================================================================================================
	std::sort(m_updateTargets.begin(), m_updateTargets.end(),
		[](Component* a, Component* b) -> bool
		{
			return a->executionOrder() < b->executionOrder();
		});
	// ===================================================================================================================

	// 물리 업데이트를 진행합니다.
	// ===================================================================================================================
	Physics2D::SetProcessDatas(&m_bodyTargets, &m_colliderTargets);
	Physics2D::Process();
	// ===================================================================================================================

	// 정렬된 리스트의 컴포넌트들의 업데이트를 진행합니다.
	// ===================================================================================================================
	for (auto& comp : m_updateTargets)
		comp->Update();
	// ===================================================================================================================

	// 정렬된 리스트의 컴포넌트들의 후 업데이트를 진행합니다.
	// ===================================================================================================================
	for (auto& comp : m_updateTargets)
		comp->LateUpdate();
	// ===================================================================================================================

	// 업데이트 대상 리스트를 비웁니다.
	m_updateTargets.clear();

	// 물리 처리 대상 리스트를 비웁니다.
	Physics2D::ClearProcessDatas();
}

void Machine::Render(HDC hdc)
{
	for (auto& camera : *Camera2D::getCameras())
	{
		if (!camera->gameObject()->active() || !camera->enable()) continue;
		HDCEx* cameraHDCEx = camera->hDCEx();
		// 카메라 HDC 의 내용을 검은색으로 덮어씁니다.
		cameraHDCEx->Fill(RGB(0, 0, 0));
		// 우선순위가 낮은 태그의 렌더 타겟 리스트부터 순회합니다.
		for (auto& renderTargets : m_renderTargets)
		{
			// 해당 태그의 렌터 타겟 리스트를 렌더 순서에 따라 정렬합니다.
			std::sort(renderTargets.begin(), renderTargets.end(),
				[](Renderer2D* a, Renderer2D* b) -> bool
				{
					return a->renderOrder() < b->renderOrder();
				});
			// 렌더러의 렌더 함수를 호출합니다.
			for (auto& renderer : renderTargets)
				renderer->Render(camera);
			// 해당 태그의 렌더 타겟 리스트를 비웁니다.
			renderTargets.clear();
		}
	}
	// 메인 카메라의 HDC 를 메인 HDC 에 씁니다.
	Camera2D* mainCamera = Camera2D::mainCamera();
	if (mainCamera)
	{
		mainCamera->hDCEx()->StrBlt(hdc, 0, 0, *BaseGlobal::pCX, *BaseGlobal::pCY);
	}
}

void Machine::DeleteAllGameObjectsAndComponent()
{
	for (auto& gameObject : GameObject::g_gameObjects)
	{
		// Destroy() 될때 호출되는 함수의 호출을 위하여 Destroy() 를 호출 후 제거합니다.
		gameObject->Destroy();
		BASE_SAFE_DELETE(gameObject);
	}
	GameObject::g_gameObjects.clear();
}

void Machine::Reset()
{
	BitmapManager::instance()->Clear();
	SpriteManager::instance()->Clear();

	for (auto& renderTargets : m_renderTargets)
		renderTargets.clear();
	m_updateTargets.clear();
	m_bodyTargets.clear();
	for (size_t colLayer = 0; colLayer < GO_LAYER_MAX; ++colLayer)
		m_colliderTargets[colLayer].clear();

	Physics2D::Reset();
}

void Machine::ComponentsDestroyAndSetTargets(GameObject* gameObject)
{
	std::vector<Component*>* components = gameObject->GetComponents();
	// 게임오브젝트의 컴포넌트를 순회합니다.
	for (auto it = components->begin(); it != components->end();)
	{
		Component* comp = *it;
		// 컴포넌트가 삭제되어야 한다면 삭제합니다.
		if (comp->shouldDestroy())
		{
			BASE_SAFE_DELETE(comp);
			it = components->erase(it);
			continue;
		}
		// 삭제할 필요가 없는 경우에
		// 컴포넌트의 게임오브젝트가 활성화 상태이며, 컴포넌트 또한 활성화 상태일 때
		else if (gameObject->active() && comp->enable())
		{
			// 방금 생성한 컴포넌트라면 해당 함수들을 부릅니다.
			if (comp->isAwaked())
			{
				comp->Start();
				comp->OnEnable();
				// Awaked 상태를 해제하는 함수입니다.
				comp->AwakedJobDone();
			}
			// 해당 컴포넌트가 렌더러인 경우 렌더 태그를 인덱스로 사용하여 렌더 타겟 리스트에 추가합니다.
			if (comp->m_isRenderer)
			{
				Renderer2D* renderer = static_cast<Renderer2D*>(comp);
				m_renderTargets[renderer->renderTag()].push_back(renderer);
				//				---------------------
				//				렌더 태그를 인덱스로 사용한다.
				//				따라서 이후에 태그 번호가 낮은 렌더러를 먼저 호출하게 된다.
			}
			else if (comp->m_isBody2D || comp->m_isCollider2D)
			{
				GameObject* obj = comp->gameObject();
				if (comp->m_isBody2D)
				{
					Body2D* body = static_cast<Body2D*>(comp);
					m_bodyTargets.push_back(body);
				}
				else if (comp->m_isCollider2D)
				{
					Collider2D* collider = static_cast<Collider2D*>(comp);
					const unsigned char& layer = collider->gameObject()->layer();
					m_colliderTargets[layer].push_back(collider);
				}
			}
			// 업데이트 타겟 리스트에 추가합니다.
			m_updateTargets.push_back(comp);
		}
		++it;
	}
}