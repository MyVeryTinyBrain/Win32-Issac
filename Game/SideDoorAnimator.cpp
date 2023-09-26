#include "stdafx.h"
#include "SideDoorAnimator.h"

void DoorSideAnimator::OnAwake()
{
}

void DoorSideAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void DoorSideAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void DoorSideAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_openAnimation && next == nullptr)
		OnOpened();
	if (prev == m_closeAnimation && next == nullptr)
		OnClosed();
}

void DoorSideAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_openAnimation);
	SAFE_DELETE(m_closeAnimation);
}

void DoorSideAnimator::InitSetDoorSprite(Sprite* door1, Sprite* door2, Sprite* door3, Sprite* door4)
{
	SAFE_DELETE(m_openAnimation);
	SAFE_DELETE(m_closeAnimation);

	const float delay = 0.05f;

	m_openAnimation = new Animation(false);
	m_openAnimation->AddSprite(delay * 1, door1);
	m_openAnimation->AddSprite(delay * 2, door2);
	m_openAnimation->AddSprite(delay * 3, door3);
	m_openAnimation->AddSprite(delay * 4, door4);
	m_openAnimation->AddSprite(delay * 5, nullptr);
	m_openAnimation->AddSprite(delay * 6, nullptr);
	m_openAnimation->EndEdit();

	m_closeAnimation = new Animation(false);
	m_closeAnimation->AddSprite(delay * 0, nullptr);
	m_closeAnimation->AddSprite(delay * 1, door4);
	m_closeAnimation->AddSprite(delay * 2, door3);
	m_closeAnimation->AddSprite(delay * 3, door2);
	m_closeAnimation->AddSprite(delay * 4, door1);
	m_closeAnimation->AddSprite(delay * 5, nullptr);
	m_closeAnimation->EndEdit();
}

void DoorSideAnimator::PlayOpen()
{
	PlayAnimation(m_openAnimation);
}

void DoorSideAnimator::PlayClose()
{
	PlayAnimation(m_closeAnimation);
}
