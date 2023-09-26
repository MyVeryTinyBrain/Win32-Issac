#include "stdafx.h"
#include "Bomb.h"
#include "MyRenderTag.h"
#include "Explosion.h"

void Bomb::Awake()
{
	m_rendererObj = new GameObject(this->transform());
	m_rendererObj->transform()->setLocalPosition({});
	m_renderer = m_rendererObj->AddComponent<SpriteRenderer>();
	m_renderer->setSprite(SpriteManager::Find(TEXT("pickup_016_bomb/default")));
	m_renderer->setRenderTag(RD_TAG_OBJ);
	m_renderer->setFixedSize(false);
	m_renderer->setOriginSizeWhenDefixedSize(true);
	m_renderer->setFillMode(true);

	GameObject* shadowObj = new GameObject(this->transform());
	shadowObj->transform()->setLocalPosition({ 0, -10 });
	SpriteRenderer* shadowRenderer = shadowObj->AddComponent<SpriteRenderer>();
	shadowRenderer->setSprite(SpriteManager::Find(TEXT("shadow")));
	shadowRenderer->setRenderTag(RD_TAG_SHADOW);
	shadowRenderer->setFixedSize(false);
	shadowRenderer->setOriginSizeWhenDefixedSize(false);
	shadowObj->transform()->setSize({ 20,7 });

	m_delay = 2.0f;
	m_accumulated = 0;
}

void Bomb::Start()
{
}

void Bomb::Update()
{
	float h = 0.3f;
	float g = 2.0f;
	float s = sinf(TAU * powf(m_accumulated, 2) * g) * h * 0.5f + h * 0.5f + 1;
	m_rendererObj->transform()->setLocalSize({ 2.0f + h - s,s });

	float per = m_accumulated / m_delay;
	Vector3 color = Vector3::Lerp({ 1,1,1 }, { 1,0,0 }, per);
	m_renderer->setFillColor(RGB(color.x * 255, color.y * 255, color.z * 255));

	m_accumulated += Global::deltaTime;
	if (m_accumulated > m_delay)
	{
		m_rendererObj->transform()->setLocalSize({ 1,1 });
		GameObject* explosionObj = new GameObject(this->transform()->position());
		Explosion* explosion = explosionObj->AddComponent<Explosion>();
		gameObject()->Destroy();
	}
}

void Bomb::LateUpdate()
{
}

void Bomb::OnEnable()
{
}

void Bomb::OnDisable()
{
}

void Bomb::OnDestroy()
{
}
