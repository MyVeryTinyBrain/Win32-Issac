#include "stdafx.h"
#include "Pool.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"

void Pool::Awake()
{
	m_do = false;
	m_destroyDelay = 10.0f;
	m_destroyCounter = 0;

	m_renderer = gameObject()->AddComponent<SpriteRenderer>();
	m_renderer->setRenderTag(RD_TAG_FLOOR_OVERLAY);
	m_renderer->setRenderOrder(RD_TAG_FLOOR_OVERLAY_POOL);
	m_renderer->setAlphaMode(true);
	m_renderer->setSprite(nullptr);
}

void Pool::Start()
{
}

void Pool::Update()
{
	if (m_do)
	{
		m_destroyCounter -= Global::deltaTime;
		if (m_destroyCounter <= 0)
		{
			m_do = false;
			this->gameObject()->Destroy();
			return;
		}
		float per = m_destroyCounter / m_destroyDelay;
		m_renderer->setAlpha(per * 0.4f);
	}
}

void Pool::LateUpdate()
{
}

void Pool::OnEnable()
{
}

void Pool::OnDisable()
{
}

void Pool::OnDestroy()
{
}

Sprite* Pool::FindSprite(const Type& type, const Size& size)
{
	Sprite* sprite = nullptr;
	TCHAR spriteKey[512]{};

	switch (type)
	{
		case Type::Water:
			_tcscpy_s(spriteKey, 512, TEXT("effect_016_pool_"));
			break;
		case Type::Blood:
			_tcscpy_s(spriteKey, 512, TEXT("effect_016_bloodpool_"));
			break;
	}

	size_t idx;
	TCHAR lastKey[64]{};
	switch (size)
	{
		case Size::Small:
			idx = rand() % 12;
			_stprintf_s(lastKey, 64, TEXT("small/%u"), idx);
			break;
		case Size::Regular:
			idx = rand() % 6;
			_stprintf_s(lastKey, 64, TEXT("regular/%u"), idx);
			break;
		case Size::Large:
			idx = rand() % 6;
			_stprintf_s(lastKey, 64, TEXT("large/%u"), idx);
			break;
	}
	_tcscat_s(spriteKey, 512, lastKey);

	return SpriteManager::Find(spriteKey);
}

void Pool::InitGenerate(const Type& type, const Size& size)
{
	m_renderer->setSprite(FindSprite(type, size));
	m_do = true;
	m_destroyCounter = m_destroyDelay;
	transform()->setLocalAngle((rand() % 360) * DEG2RAD);
}
