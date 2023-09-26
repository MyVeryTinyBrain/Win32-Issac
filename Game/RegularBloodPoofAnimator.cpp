#include "stdafx.h"
#include "RegularBloodPoofAnimator.h"

void RegularBloodPoofAnimator::OnAwake()
{
	const float delay = 0.05f;

	m_anim = new Animation(false);
	m_anim->AddSprite(delay * 0, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/01")));
	m_anim->AddSprite(delay * 1, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/02")));
	m_anim->AddSprite(delay * 2, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/03")));
	m_anim->AddSprite(delay * 3, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/04")));
	m_anim->AddSprite(delay * 4, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/05")));
	m_anim->AddSprite(delay * 5, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/06")));
	m_anim->AddSprite(delay * 6, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/07")));
	m_anim->AddSprite(delay * 7, SpriteManager::Find(TEXT("effect_002_bloodpoof_regular/08")));
	m_anim->AddSprite(delay * 8, nullptr);
	m_anim->AddSprite(delay * 9, nullptr);
	m_anim->EndEdit();

	PlayAnimation(m_anim);
}

void RegularBloodPoofAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void RegularBloodPoofAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void RegularBloodPoofAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_anim && next == nullptr)
	{
		gameObject()->Destroy();
		return;
	}
}

void RegularBloodPoofAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_anim);
}