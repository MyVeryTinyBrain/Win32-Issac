#include "BaseStdafx.h"
#include "Animator.h"
#include "ExecutionOrder.h"
#include "Animation.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

void Animator::Awake()
{
	SetExecutionOrder(EX_ORDER_ANIMATOR);

	m_elapsed = 0;
	m_useUnscaledDeltaTime = false;

	OnAwake();
	OnSetDefaultAnimation(&m_defaultAnimation);

	SpriteRenderer* sr = nullptr;
	sr = gameObject()->GetComponent<SpriteRenderer>();
	SetSpriteRenderer(sr);
}

void Animator::Start()
{
}

void Animator::Update()
{
	OnUpdate(m_curAnimation, m_elapsed);

	if (!m_curAnimation)
		PlayAnimation(m_defaultAnimation);
	if (!m_curAnimation)
		return;

	if (m_useUnscaledDeltaTime)
		m_elapsed += *BaseGlobal::pUnscaledDeltaTime;
	else
		m_elapsed += *BaseGlobal::pDeltaTime;

	Vector2 localPosition = {};
	float localAngle = 0;
	Vector2 localSize = {};
	Sprite* sprite = nullptr;

	if (m_curAnimation->GetLocalPosition(m_elapsed, &localPosition))
	{
		transform()->setLocalPosition(localPosition);
	}
	if (m_curAnimation->GetLocalAngle(m_elapsed, &localAngle))
	{
		transform()->setLocalAngle(localAngle);
	}
	if (m_curAnimation->GetLocalSize(m_elapsed, &localSize))
	{
		transform()->setLocalSize(localSize);
	}
	if (m_spriteRenderer && m_curAnimation->GetSprite(m_elapsed, &sprite))
	{
		m_spriteRenderer->setSprite(sprite);
	}

	if (m_elapsed * m_curAnimation->speed() > m_curAnimation->totalTime())
	{
		if (m_curAnimation->isLoop() == false)
			PlayAnimation(m_defaultAnimation);
		else
			OnAnimationChanged(m_curAnimation, m_curAnimation);
	}
}

void Animator::LateUpdate()
{
}

void Animator::OnEnable()
{
}

void Animator::OnDisable()
{
}

void Animator::OnDestroy()
{
}

void Animator::SetDefaultAnimation(Animation* animation)
{
	m_defaultAnimation = animation;
}

void Animator::PlayAnimation(Animation* animation, bool keepElapsedTime)
{
	if (keepElapsedTime == false)
		m_elapsed = 0;
	Animation* prev = m_curAnimation;
	m_curAnimation = animation;
	OnAnimationChanged(prev, m_curAnimation);
}

void Animator::SetSpriteRenderer(SpriteRenderer* spriteRenderer)
{
	if (m_spriteRenderer)
	{
		m_spriteRenderer = nullptr;
	}
	m_spriteRenderer = spriteRenderer;
	if (spriteRenderer)
	{
	}
}

void Animator::OnSpriteRendererDestroy(Object* obj)
{
	if (m_spriteRenderer == obj)
	{
		m_spriteRenderer = nullptr;
	}
}

void Animator::setDefaultAnimation(Animation* animation)
{
	m_defaultAnimation = animation;
}