#include "stdafx.h"
#include "LargeBloodPoofAnimator.h"

void LargeBloodPoofAnimator::OnAwake()
{
	const float delay = 0.05f;

	m_anim = new Animation(false);
	m_anim->AddSprite(delay * 0, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/01")));
	m_anim->AddSprite(delay * 1, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/02")));
	m_anim->AddSprite(delay * 2, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/03")));
	m_anim->AddSprite(delay * 3, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/04")));
	m_anim->AddSprite(delay * 4, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/05")));
	m_anim->AddSprite(delay * 5, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/06")));
	m_anim->AddSprite(delay * 6, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/07")));
	m_anim->AddSprite(delay * 7, SpriteManager::Find(TEXT("effect_002_bloodpoof_large/08")));
	m_anim->AddSprite(delay * 8, nullptr);
	m_anim->AddSprite(delay * 9, nullptr);
	m_anim->EndEdit();

	PlayAnimation(m_anim);
}

void LargeBloodPoofAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void LargeBloodPoofAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void LargeBloodPoofAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_anim && next == nullptr)
	{
		gameObject()->Destroy();
		return;
	}
}

void LargeBloodPoofAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_anim);
}