#include "stdafx.h"
#include "KeyAnimator.h"

void KeyAnimator::OnAwake()
{
	m_keyAnimation = new Animation(false);

	m_keyAnimation->AddSprite(0, SpriteManager::Find(TEXT("door_01_normaldoor/key")));
	m_keyAnimation->AddLocalPosition(0, { 1,-15 });
	m_keyAnimation->AddLocalPosition(0.2f, { 1,-5 });
	m_keyAnimation->AddSprite(0.2f, SpriteManager::Find(TEXT("door_01_normaldoor/keyanim_01")));
	m_keyAnimation->AddSprite(0.3f, SpriteManager::Find(TEXT("door_01_normaldoor/keyanim_02")));
	m_keyAnimation->AddSprite(0.4f, SpriteManager::Find(TEXT("door_01_normaldoor/keyanim_03")));
	m_keyAnimation->AddSprite(0.5f, SpriteManager::Find(TEXT("door_01_normaldoor/keyanim_04")));
	m_keyAnimation->AddSprite(0.6f, SpriteManager::Find(TEXT("door_01_normaldoor/keyanim_03")));
	m_keyAnimation->AddSprite(0.7f, SpriteManager::Find(TEXT("door_01_normaldoor/keyanim_02")));
	m_keyAnimation->AddSprite(0.8f, SpriteManager::Find(TEXT("door_01_normaldoor/keyanim_01")));
	m_keyAnimation->AddSprite(0.9f, nullptr);
	m_keyAnimation->AddSprite(1.0f, nullptr);
	m_keyAnimation->EndEdit();
}

void KeyAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void KeyAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void KeyAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == next) return;
	if (prev == m_keyAnimation && next == nullptr)
	{
		OnAnimated();
	}
}

void KeyAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_keyAnimation);
}

void KeyAnimator::Play()
{
	PlayAnimation(m_keyAnimation);
}

bool KeyAnimator::isPlayingUnlockAnimation() const
{
	return (m_curAnimation == m_keyAnimation);
}
