#include "stdafx.h"
#include "ProjectileAnimator.h"

void ProjectileAnimator::OnAwake()
{
	m_destroyAnimated = false;
}

void ProjectileAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void ProjectileAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void ProjectileAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_destroyAnimation && next == nullptr)
		OnDestroyAnimated();
}

void ProjectileAnimator::OnPrevDestroy()
{
}

void ProjectileAnimator::InitSetSprites(Sprite* s1, Sprite* s2, Sprite* s3, Sprite* s4, Sprite* s5, Sprite* s6, Sprite* s7, Sprite* s8, Sprite* s9, Sprite* s10, Sprite* s11, Sprite* s12)
{
	m_idleAnimation = new Animation(true);
	m_idleAnimation->AddSprite(0, s1);
	m_idleAnimation->EndEdit();

	float delay = 0.05f;
	m_destroyAnimation = new Animation(false);
	m_destroyAnimation->AddSprite(delay * 0, s2);
	m_destroyAnimation->AddSprite(delay * 1, s3);
	m_destroyAnimation->AddSprite(delay * 2, s4);
	m_destroyAnimation->AddSprite(delay * 3, s5);
	m_destroyAnimation->AddSprite(delay * 4, s6);
	m_destroyAnimation->AddSprite(delay * 5, s7);
	m_destroyAnimation->AddSprite(delay * 6, s8);
	m_destroyAnimation->AddSprite(delay * 7, s9);
	m_destroyAnimation->AddSprite(delay * 8, s10);
	m_destroyAnimation->AddSprite(delay * 9, s11);
	m_destroyAnimation->AddSprite(delay * 10, s12);
	m_destroyAnimation->AddSprite(delay * 11, nullptr);
	m_destroyAnimation->EndEdit();
}

void ProjectileAnimator::PlayIdleAnimation()
{
	PlayAnimation(m_idleAnimation);
}

void ProjectileAnimator::PlayOnceDestroyAnimation()
{
	if (m_destroyAnimated)
		return;
	m_destroyAnimated = true;
	PlayAnimation(m_destroyAnimation);
}
