#include "stdafx.h"
#include "TestAnimator.h"

void TestAnimator::Awake()
{
	m_interval = 0.05f;
	m_accumulated = 0;
}

void TestAnimator::Start()
{
	m_renderer = gameObject()->GetComponent<SpriteRenderer>();
}

void TestAnimator::Update()
{
	m_accumulated += Global::deltaTime;
	if (m_accumulated > m_interval)
	{
		m_accumulated = 0;
		++m_idx;
		if (m_idx == m_sprites.size())
			m_idx = 0;
	}
	m_renderer->setSprite(m_sprites[m_idx]);
}

void TestAnimator::LateUpdate()
{
}

void TestAnimator::OnEnable()
{
}

void TestAnimator::OnDisable()
{
}

void TestAnimator::OnDestroy()
{
}

void TestAnimator::AddSprite(Sprite* sprite)
{
	m_sprites.push_back(sprite);
}
