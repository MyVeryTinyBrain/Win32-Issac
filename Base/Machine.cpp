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
	// �ı��Ǿ�� �� ������Ʈ���� �ı��մϴ�.
	// ������Ʈ �Ǿ�� �� ������Ʈ���� ���Ϳ� �߰��մϴ�.
	// ===================================================================================================================
	// ��� ���ӿ�����Ʈ ����Ʈ�� ��ȸ�մϴ�.
	for (auto it = GameObject::g_gameObjects.begin(); it != GameObject::g_gameObjects.end();)
	{
		GameObject* gameObject = *it;
		// �ش� ���ӿ�����Ʈ�� �ı��Ǿ�� �Ѵٸ� �ı��ϰ� ����Ʈ���� �����մϴ�.
		if (gameObject->shouldDestroy())
		{
			it = GameObject::g_gameObjects.erase(it);
			BASE_SAFE_DELETE(gameObject);
		}
		// �ı��� �ʿ䰡 ���ٸ� �ش� ���ӿ�����Ʈ�� ������Ʈ����
		// ������Ʈ ����Ʈ�� ���� ����Ʈ�� ���ǿ� ���� ����մϴ�.
		else
		{
			ComponentsDestroyAndSetTargets(gameObject);
			++it;
		}
	}
	// ===================================================================================================================

	// ������Ʈ ����Ʈ�� ������Ʈ ������ ���� �����մϴ�.
	// ===================================================================================================================
	std::sort(m_updateTargets.begin(), m_updateTargets.end(),
		[](Component* a, Component* b) -> bool
		{
			return a->executionOrder() < b->executionOrder();
		});
	// ===================================================================================================================

	// ���� ������Ʈ�� �����մϴ�.
	// ===================================================================================================================
	Physics2D::SetProcessDatas(&m_bodyTargets, &m_colliderTargets);
	Physics2D::Process();
	// ===================================================================================================================

	// ���ĵ� ����Ʈ�� ������Ʈ���� ������Ʈ�� �����մϴ�.
	// ===================================================================================================================
	for (auto& comp : m_updateTargets)
		comp->Update();
	// ===================================================================================================================

	// ���ĵ� ����Ʈ�� ������Ʈ���� �� ������Ʈ�� �����մϴ�.
	// ===================================================================================================================
	for (auto& comp : m_updateTargets)
		comp->LateUpdate();
	// ===================================================================================================================

	// ������Ʈ ��� ����Ʈ�� ���ϴ�.
	m_updateTargets.clear();

	// ���� ó�� ��� ����Ʈ�� ���ϴ�.
	Physics2D::ClearProcessDatas();
}

void Machine::Render(HDC hdc)
{
	for (auto& camera : *Camera2D::getCameras())
	{
		if (!camera->gameObject()->active() || !camera->enable()) continue;
		HDCEx* cameraHDCEx = camera->hDCEx();
		// ī�޶� HDC �� ������ ���������� ����ϴ�.
		cameraHDCEx->Fill(RGB(0, 0, 0));
		// �켱������ ���� �±��� ���� Ÿ�� ����Ʈ���� ��ȸ�մϴ�.
		for (auto& renderTargets : m_renderTargets)
		{
			// �ش� �±��� ���� Ÿ�� ����Ʈ�� ���� ������ ���� �����մϴ�.
			std::sort(renderTargets.begin(), renderTargets.end(),
				[](Renderer2D* a, Renderer2D* b) -> bool
				{
					return a->renderOrder() < b->renderOrder();
				});
			// �������� ���� �Լ��� ȣ���մϴ�.
			for (auto& renderer : renderTargets)
				renderer->Render(camera);
			// �ش� �±��� ���� Ÿ�� ����Ʈ�� ���ϴ�.
			renderTargets.clear();
		}
	}
	// ���� ī�޶��� HDC �� ���� HDC �� ���ϴ�.
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
		// Destroy() �ɶ� ȣ��Ǵ� �Լ��� ȣ���� ���Ͽ� Destroy() �� ȣ�� �� �����մϴ�.
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
	// ���ӿ�����Ʈ�� ������Ʈ�� ��ȸ�մϴ�.
	for (auto it = components->begin(); it != components->end();)
	{
		Component* comp = *it;
		// ������Ʈ�� �����Ǿ�� �Ѵٸ� �����մϴ�.
		if (comp->shouldDestroy())
		{
			BASE_SAFE_DELETE(comp);
			it = components->erase(it);
			continue;
		}
		// ������ �ʿ䰡 ���� ��쿡
		// ������Ʈ�� ���ӿ�����Ʈ�� Ȱ��ȭ �����̸�, ������Ʈ ���� Ȱ��ȭ ������ ��
		else if (gameObject->active() && comp->enable())
		{
			// ��� ������ ������Ʈ��� �ش� �Լ����� �θ��ϴ�.
			if (comp->isAwaked())
			{
				comp->Start();
				comp->OnEnable();
				// Awaked ���¸� �����ϴ� �Լ��Դϴ�.
				comp->AwakedJobDone();
			}
			// �ش� ������Ʈ�� �������� ��� ���� �±׸� �ε����� ����Ͽ� ���� Ÿ�� ����Ʈ�� �߰��մϴ�.
			if (comp->m_isRenderer)
			{
				Renderer2D* renderer = static_cast<Renderer2D*>(comp);
				m_renderTargets[renderer->renderTag()].push_back(renderer);
				//				---------------------
				//				���� �±׸� �ε����� ����Ѵ�.
				//				���� ���Ŀ� �±� ��ȣ�� ���� �������� ���� ȣ���ϰ� �ȴ�.
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
			// ������Ʈ Ÿ�� ����Ʈ�� �߰��մϴ�.
			m_updateTargets.push_back(comp);
		}
		++it;
	}
}