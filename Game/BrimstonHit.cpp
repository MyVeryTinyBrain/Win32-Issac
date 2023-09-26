#include "stdafx.h"
#include "BrimstonHit.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"

void BrimstonHit::Awake()
{
	m_sprites[0] = SpriteManager::Find(TEXT("effect_brimstoneimpact/1"));
	m_sprites[1] = SpriteManager::Find(TEXT("effect_brimstoneimpact/2"));
	m_sprites[2] = SpriteManager::Find(TEXT("effect_brimstoneimpact/3"));
	m_sprites[3] = SpriteManager::Find(TEXT("effect_brimstoneimpact/4"));
	m_renderer = gameObject()->AddComponent<SpriteRenderer>();
	m_renderer->setRenderTag(RD_TAG_EFFECT);
	m_renderer->setRenderOrder(RD_ORDER_EFFECT_BRIMSTON_HIT);
	m_renderer->setFixedSize(false);
	m_renderer->setOriginSizeWhenDefixedSize(false);
	m_elasped = 0;

	SetRadius(10);
}

void BrimstonHit::Start()
{
}

void BrimstonHit::Update()
{
	float delay = 0.05f;
	float step = 4;
	float y = fmodf(m_elasped / delay, 2) * 0.5f;
	size_t pulse = (size_t)(y * step);
	m_renderer->setSprite(m_sprites[pulse]);
	m_elasped += Global::deltaTime;
}

void BrimstonHit::LateUpdate()
{
}

void BrimstonHit::OnEnable()
{
}

void BrimstonHit::OnDisable()
{
}

void BrimstonHit::OnDestroy()
{
}

void BrimstonHit::SetRadius(const float& radius)
{
	gameObject()->transform()->setSize({ radius * 4,radius * 4 });
}