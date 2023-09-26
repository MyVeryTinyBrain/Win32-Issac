#include "stdafx.h"
#include "SmallBloodPoofAnimator.h"

void SmallBloodPoofAnimator::OnAwake()
{
	const float delay = 0.05f;

	m_anim = new Animation(false);
	m_anim->AddSprite(delay * 0, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/01")));
	m_anim->AddSprite(delay * 1, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/02")));
	m_anim->AddSprite(delay * 2, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/03")));
	m_anim->AddSprite(delay * 3, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/04")));
	m_anim->AddSprite(delay * 4, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/05")));
	m_anim->AddSprite(delay * 5, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/06")));
	m_anim->AddSprite(delay * 6, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/07")));
	m_anim->AddSprite(delay * 7, SpriteManager::Find(TEXT("effect_002_bloodpoof_small/08")));
	m_anim->AddSprite(delay * 8, nullptr);
	m_anim->AddSprite(delay * 9, nullptr);
	m_anim->EndEdit();

	PlayAnimation(m_anim);
}

void SmallBloodPoofAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void SmallBloodPoofAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void SmallBloodPoofAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_anim && next == nullptr)
	{
		gameObject()->Destroy();
		return;
	}
}

void SmallBloodPoofAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_anim);
}
