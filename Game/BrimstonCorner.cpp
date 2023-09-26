#include "stdafx.h"
#include "BrimstonCorner.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"

void BrimstonCorner::Awake()
{
	m_sprites[0] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/sphere1"));
	m_sprites[1] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/sphere2"));
	m_sprites[2] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/sphere3"));
	m_sprites[3] = SpriteManager::Find(TEXT("effect_018_brimstonelaser/sphere4"));
	m_renderer = gameObject()->AddComponent<SpriteRenderer>();
	m_renderer->setRenderTag(RD_TAG_EFFECT);
	m_renderer->setRenderOrder(RD_ORDER_EFFECT_BRIMSTON_CORNER);
	m_renderer->setFixedSize(false);
	m_renderer->setOriginSizeWhenDefixedSize(false);
	m_elasped = 0;

	SetRadius(10);
}

void BrimstonCorner::Start()
{
}

void BrimstonCorner::Update()
{
	float delay = 0.05f;
	float step = 4;
	float y = fmodf(m_elasped / delay, 2) * 0.5f;
	size_t pulse = (size_t)(y * step);
	m_renderer->setSprite(m_sprites[pulse]);
	m_elasped += Global::deltaTime;
}

void BrimstonCorner::LateUpdate()
{
}

void BrimstonCorner::OnEnable()
{
}

void BrimstonCorner::OnDisable()
{
}

void BrimstonCorner::OnDestroy()
{
}

void BrimstonCorner::SetRadius(const float& radius)
{
	gameObject()->transform()->setSize({ radius * 2,radius * 2 });
}

void BrimstonCorner::SetOrder(const int& order)
{
	m_renderer->setRenderOrder(RD_ORDER_EFFECT_BRIMSTON_CORNER + order);
}