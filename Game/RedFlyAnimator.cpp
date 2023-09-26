#include "stdafx.h"
#include "RedFlyAnimator.h"

void RedFlyAnimator::OnAwake()
{
	m_default = new Animation(true);
	m_default->AddSprite(0, SpriteManager::Find(TEXT("monster_010_eternalfly/red01")));
	m_default->AddSprite(0.05f, SpriteManager::Find(TEXT("monster_010_eternalfly/red02")));
	m_default->AddSprite(0.1f, SpriteManager::Find(TEXT("monster_010_eternalfly/black01")));
	m_default->AddSprite(0.15f, SpriteManager::Find(TEXT("monster_010_eternalfly/black02")));
	m_default->AddSprite(0.2f, SpriteManager::Find(TEXT("monster_010_eternalfly/red01")));
	m_default->EndEdit();

	const float delay = 0.05f;
	m_dead = new Animation(false);
	m_dead->AddSprite(delay * 0, SpriteManager::Find(TEXT("monster_010_eternalfly/dead01")));
	m_dead->AddSprite(delay * 1, SpriteManager::Find(TEXT("monster_010_eternalfly/dead02")));
	m_dead->AddSprite(delay * 2, SpriteManager::Find(TEXT("monster_010_eternalfly/dead03")));
	m_dead->AddSprite(delay * 3, SpriteManager::Find(TEXT("monster_010_eternalfly/dead04")));
	m_dead->AddSprite(delay * 4, SpriteManager::Find(TEXT("monster_010_eternalfly/dead05")));
	m_dead->AddSprite(delay * 5, SpriteManager::Find(TEXT("monster_010_eternalfly/dead06")));
	m_dead->AddSprite(delay * 6, SpriteManager::Find(TEXT("monster_010_eternalfly/dead07")));
	m_dead->AddSprite(delay * 7, SpriteManager::Find(TEXT("monster_010_eternalfly/dead08")));
	m_dead->AddSprite(delay * 8, SpriteManager::Find(TEXT("monster_010_eternalfly/dead09")));
	m_dead->AddSprite(delay * 9, SpriteManager::Find(TEXT("monster_010_eternalfly/dead10")));
	m_dead->AddSprite(delay * 10, SpriteManager::Find(TEXT("monster_010_eternalfly/dead11")));
	m_dead->AddSprite(delay * 11, SpriteManager::Find(TEXT("monster_010_eternalfly/dead12")));
	m_dead->AddSprite(delay * 12, nullptr);
	m_dead->EndEdit();

	m_deadAnimated = false;

	PlayAnimation(m_default);
}

void RedFlyAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void RedFlyAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void RedFlyAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_dead && next == nullptr)
		OnDeadAnimated();
}

void RedFlyAnimator::OnPrevDestroy()
{
}

void RedFlyAnimator::PlayDefault()
{
	if (m_curAnimation == m_dead)
		return;
	PlayAnimation(m_default);
}

void RedFlyAnimator::PlayDead()
{
	if (m_deadAnimated == true)
		return;
	m_deadAnimated = true;
	PlayAnimation(m_dead);
}
