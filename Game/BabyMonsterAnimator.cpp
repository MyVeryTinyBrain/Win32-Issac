#include "stdafx.h"
#include "BabyMonsterAnimator.h"

void BabyMonsterAnimator::OnAwake()
{
	m_default = new Animation(true);
	m_default->AddSprite(0, SpriteManager::Find(TEXT("monster_155_baby_champion/default")));
	m_default->AddLocalSize(0, { 1,1 });
	m_default->EndEdit();

	m_attack = new Animation(false);
	m_attack->AddSprite(0, SpriteManager::Find(TEXT("monster_155_baby_champion/default")));
	m_attack->AddSprite(0.1f, SpriteManager::Find(TEXT("monster_155_baby_champion/scream")));
	m_attack->AddSprite(0.7f, SpriteManager::Find(TEXT("monster_155_baby_champion/default")));
	m_attack->AddLocalSize(0, { 1,1 });
	m_attack->AddLocalSize(0.05f, { 0.5f,1 });
	m_attack->AddLocalSize(0.15f, { 1.25f,1 });
	m_attack->AddLocalSize(0.2f, { 1,1 });
	m_attack->EndEdit();

	m_teleport = new Animation(false);
	m_teleport->AddLocalSize(0, { 1,1 });
	m_teleport->AddLocalSize(0.1f, { 1.5f,1.5f });
	m_teleport->AddLocalSize(0.25f, { 0,0 });
	m_teleport->AddLocalSize(0.5f, { 0,0 });
	m_teleport->EndEdit();

	PlayAnimation(m_default);
}

void BabyMonsterAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
	*defaultAnimtiaon = m_default;
}

void BabyMonsterAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void BabyMonsterAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_teleport && next == m_default)
		OnTeleportAnimated();
	else if (prev == m_attack && next == m_default)
		OnAttackAnimated();
}

void BabyMonsterAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_default);
	SAFE_DELETE(m_attack);
	SAFE_DELETE(m_teleport);
}

void BabyMonsterAnimator::PlayAttack()
{
	if (m_curAnimation == m_attack)
		return;
	PlayAnimation(m_attack);
}

void BabyMonsterAnimator::PlayTeleport()
{
	if (m_curAnimation == m_teleport)
		return;
	PlayAnimation(m_teleport);
}

bool BabyMonsterAnimator::isPlayingAttack()
{
	return (m_curAnimation == m_teleport);
}

bool BabyMonsterAnimator::isPlayingTeleport()
{
	return (m_curAnimation == m_attack);
}
