#include "stdafx.h"
#include "TargetEffect.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"

void TargetEffect::Awake()
{
	m_remainingTime = 1.0f;

	m_renderer = gameObject()->AddComponent<SpriteRenderer>();
	m_renderer->setRenderTag(RD_TAG_FLOOR_OVERLAY);
	m_renderer->setRenderOrder(RD_TAG_FLOOR_OVERLAY_TARGET);
	m_renderer->setSprite(SpriteManager::Find(TEXT("target")));
	m_renderer->setFixedSize(true);
	m_renderer->setOriginSizeWhenDefixedSize(true);
	m_renderer->setFillMode(true);
}

void TargetEffect::Start()
{
}

void TargetEffect::Update()
{
	m_remainingTime -= Global::deltaTime;

	if (m_remainingTime <= 0)
	{
		gameObject()->Destroy();
		return;
	}

	const float delay = 0.05f;
	size_t pulse = (size_t)(fmodf(m_remainingTime / delay, 2) * 0.5f * 2);
	switch (pulse)
	{
		case 0:
			m_renderer->setFillColor(RGB(200, 0, 0));
			break;
		case 1:
			m_renderer->setFillColor(RGB(200, 200, 0));
			break;
	}
}

void TargetEffect::LateUpdate()
{
}

void TargetEffect::OnEnable()
{
}

void TargetEffect::OnDisable()
{
}

void TargetEffect::OnDestroy()
{
}

void TargetEffect::InitSetRemainingTime(const float& time)
{
	m_remainingTime = time;
}
