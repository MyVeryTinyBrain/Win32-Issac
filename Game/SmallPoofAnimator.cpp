#include "stdafx.h"
#include "SmallPoofAnimator.h"
#include "MyRenderTag.h"

void SmallPoofAnimator::OnAwake()
{
	const float delay = 0.05f;

	m_anim = new Animation(false);
	m_anim->AddSprite(delay * 0, SpriteManager::Find(TEXT("effect_009_poof01_small/03")));
	m_anim->AddSprite(delay * 1, SpriteManager::Find(TEXT("effect_009_poof01_small/04")));
	m_anim->AddSprite(delay * 2, SpriteManager::Find(TEXT("effect_009_poof01_small/05")));
	m_anim->AddSprite(delay * 3, SpriteManager::Find(TEXT("effect_009_poof01_small/06")));
	m_anim->AddSprite(delay * 4, SpriteManager::Find(TEXT("effect_009_poof01_small/07")));
	m_anim->AddSprite(delay * 5, SpriteManager::Find(TEXT("effect_009_poof01_small/08")));
	m_anim->AddSprite(delay * 6, SpriteManager::Find(TEXT("effect_009_poof01_small/09")));
	m_anim->AddSprite(delay * 7, SpriteManager::Find(TEXT("effect_009_poof01_small/10")));
	m_anim->AddSprite(delay * 8, SpriteManager::Find(TEXT("effect_009_poof01_small/11")));
	m_anim->AddSprite(delay * 9, SpriteManager::Find(TEXT("effect_009_poof01_small/12")));
	m_anim->AddSprite(delay * 10, SpriteManager::Find(TEXT("effect_009_poof01_small/13")));
	m_anim->AddSprite(delay * 11, SpriteManager::Find(TEXT("effect_009_poof01_small/14")));
	m_anim->AddSprite(delay * 12, SpriteManager::Find(TEXT("effect_009_poof01_small/15")));
	m_anim->AddSprite(delay * 13, nullptr);
	m_anim->AddSprite(delay * 14, nullptr);
	m_anim->EndEdit();

	PlayAnimation(m_anim);
}

void SmallPoofAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void SmallPoofAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void SmallPoofAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_anim && next == nullptr)
	{
		gameObject()->Destroy();
		return;
	}
}

void SmallPoofAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_anim);
}
