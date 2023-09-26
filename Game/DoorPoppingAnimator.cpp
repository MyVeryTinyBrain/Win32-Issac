#include "stdafx.h"
#include "DoorPoppingAnimator.h"

void DoorPoppingAnimator::OnAwake()
{
	m_animation = new Animation(false);
	m_animation->AddLocalSize(0, { 1,1 });
	m_animation->AddLocalSize(0.1f, { 0.75f,0.75f });
	m_animation->AddLocalSize(0.2f, { 1.25f,1.25f });
	m_animation->AddLocalSize(0.3f, { 1,1 });
	m_animation->AddLocalSize(0.4f, { 1,1 });
	m_animation->EndEdit();
}

void DoorPoppingAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void DoorPoppingAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void DoorPoppingAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_animation && next == nullptr)
		OnAnimated();
}

void DoorPoppingAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_animation);
}

void DoorPoppingAnimator::Play()
{
	PlayAnimation(m_animation);
}
