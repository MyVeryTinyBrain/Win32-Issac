#include "stdafx.h"
#include "UnknownBossAnimator.h"

void UnknownBossAnimator::OnAwake()
{
	m_lie_idle = new Animation(true);
	m_lie_idle->AddLocalPosition(0, { -0.05, 0 });
	m_lie_idle->AddLocalSize(0, {1, 1});
	m_lie_idle->AddSprite(0, SpriteManager::Find(TEXT("boss_078_bluebaby_01/lie")));
	m_lie_idle->AddLocalPosition(0.1f, { 0.05, 0 });
	m_lie_idle->AddLocalPosition(0.2f, { -0.05, 0 });
	m_lie_idle->EndEdit();

	m_lie_pop = new Animation(false);
	m_lie_pop->AddLocalPosition(0, {});
	m_lie_pop->AddLocalSize(0, {1, 1});
	m_lie_pop->AddSprite(0, SpriteManager::Find(TEXT("boss_078_bluebaby_01/lie")));
	m_lie_pop->AddLocalSize(0.05f, { 1.2f,0.6f });
	m_lie_pop->AddLocalSize(0.15f, { 1,1 });
	m_lie_pop->EndEdit();

	m_stand_idle = new Animation(true);
	m_stand_idle->AddLocalPosition(0, {});
	m_stand_idle->AddLocalSize(0, { 1,1 });
	m_stand_idle->AddSprite(0, SpriteManager::Find(TEXT("boss_078_bluebaby_01/stand")));
	m_stand_idle->EndEdit();

	m_stand_crouch_pop = new Animation(false);
	m_stand_crouch_pop->AddLocalPosition(0, {});
	m_stand_crouch_pop->AddLocalSize(0, { 1,1 });
	m_stand_crouch_pop->AddSprite(0, SpriteManager::Find(TEXT("boss_078_bluebaby_01/crouch")));
	m_stand_crouch_pop->AddLocalSize(0.2f, { 1.3f,0.7f });
	m_stand_crouch_pop->AddSprite(0.2f, SpriteManager::Find(TEXT("boss_078_bluebaby_01/stand_white")));
	m_stand_crouch_pop->AddLocalSize(0.25f, { 0.7f,1.3f });
	m_stand_crouch_pop->AddSprite(0.25f, SpriteManager::Find(TEXT("boss_078_bluebaby_01/stand")));
	m_stand_crouch_pop->AddLocalSize(0.3f, { 1,1 });
	m_stand_crouch_pop->EndEdit();

	const float delay1 = 0.05f;
	m_wing_idle = new Animation(true);
	m_wing_idle->AddLocalPosition(0, {});
	m_wing_idle->AddLocalSize(0, {1, 1});
	m_wing_idle->AddSprite(delay1 * 0, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing1")));
	m_wing_idle->AddSprite(delay1 * 1, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing2")));
	m_wing_idle->AddSprite(delay1 * 2, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing3")));
	m_wing_idle->AddSprite(delay1 * 3, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing4")));
	m_wing_idle->AddSprite(delay1 * 4, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing5")));
	m_wing_idle->AddSprite(delay1 * 5, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing6")));
	m_wing_idle->AddSprite(delay1 * 6, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing7")));
	m_wing_idle->AddLocalPosition(delay1 * 7, { 0, 5 });
	m_wing_idle->AddSprite(delay1 * 7, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing1")));
	m_wing_idle->AddSprite(delay1 * 8, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing2")));
	m_wing_idle->AddSprite(delay1 * 9, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing3")));
	m_wing_idle->AddSprite(delay1 * 10, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing4")));
	m_wing_idle->AddSprite(delay1 * 11, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing5")));
	m_wing_idle->AddSprite(delay1 * 12, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing6")));
	m_wing_idle->AddSprite(delay1 * 13, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing7")));
	m_wing_idle->AddSprite(delay1 * 14, SpriteManager::Find(TEXT("boss_078_bluebaby_02/wing1")));
	m_wing_idle->AddLocalPosition(delay1 * 14, { 0, 0 });
	m_wing_idle->EndEdit();

	const float delay2 = 0.05f;
	m_wing_pop = new Animation(false);
	m_wing_pop->AddLocalPosition(0, {});
	m_wing_pop->AddLocalSize(0, { 1, 1 });
	m_wing_pop->AddSprite(0, SpriteManager::Find(TEXT("boss_078_bluebaby_01/wing_hide")));
	m_wing_pop->AddLocalSize(0.2f, { 1.3f, 0.7f });
	m_wing_pop->AddSprite(0.2f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold_white3")));
	m_wing_pop->AddLocalSize(0.25f, { 0.8f, 1.2f });
	m_wing_pop->AddSprite(0.3f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold_white2")));
	m_wing_pop->AddLocalSize(0.35f, { 1, 1 });
	m_wing_pop->AddSprite(0.4f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold_white1")));
	m_wing_pop->AddSprite(0.45, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold1")));
	m_wing_pop->AddSprite(0.5f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold2")));
	m_wing_pop->AddSprite(0.55f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold3")));
	m_wing_pop->AddLocalSize(0.55f, { 1, 1 });
	m_wing_pop->EndEdit();

	m_wing_up = new Animation(false);
	m_wing_up->AddLocalPosition(0, {});
	m_wing_up->AddLocalSize(0, { 1, 1 });
	m_wing_up->AddSprite(0, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold3")));
	m_wing_up->AddSprite(0.05f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold2")));
	m_wing_up->AddSprite(0.1f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold1")));
	m_wing_up->AddSprite(0.15f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold1")));
	m_wing_up->AddSprite(0.2f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold_white3")));
	m_wing_up->AddLocalPosition(0.2f, {});
	m_wing_up->AddLocalSize(0.2f, { 1, 1 });
	m_wing_up->AddLocalPosition(0.25f, {0, 50});
	m_wing_up->AddLocalSize(0.25f, { 0.2f, 2.0f });
	m_wing_up->AddSprite(0.25f, nullptr);
	m_wing_up->AddSprite(0.4f, nullptr);
	m_wing_up->EndEdit();

	m_wing_down = new Animation(false);
	m_wing_down->AddLocalPosition(0, { 0, 50 });
	m_wing_down->AddLocalSize(0, { 0.2f, 2.0f });
	m_wing_down->AddSprite(0, nullptr);
	m_wing_down->AddLocalSize(0.1f, { 0.2f, 2.0f });
	m_wing_down->AddSprite(0.1f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold_white3")));
	m_wing_down->AddLocalPosition(0.15f, {});
	m_wing_down->AddLocalSize(0.15f, { 1, 1 });
	m_wing_down->AddSprite(0.2f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold1")));
	m_wing_down->AddSprite(0.25f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold2")));
	m_wing_down->AddSprite(0.3f, SpriteManager::Find(TEXT("boss_078_bluebaby_03/unfold3")));
	m_wing_down->EndEdit();

	m_state = State::LIE;
	SetState(m_state);
}

void UnknownBossAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
}

void UnknownBossAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
}

void UnknownBossAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_wing_up && next == m_defaultAnimation)
	{
		PlayAnimation(m_wing_down);
		OnUpAnimated();
	}
	if (prev == m_lie_pop && next != m_lie_pop)
		OnPopAnimated();
	if (prev == m_stand_crouch_pop && next != m_stand_crouch_pop)
		OnPopAnimated();
	if (prev == m_wing_pop && next != m_wing_pop)
		OnPopAnimated();
}

void UnknownBossAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_lie_idle);
	SAFE_DELETE(m_lie_pop);

	SAFE_DELETE(m_stand_idle);
	SAFE_DELETE(m_stand_crouch_pop);

	SAFE_DELETE(m_wing_idle);
	SAFE_DELETE(m_wing_pop);
	SAFE_DELETE(m_wing_up);
	SAFE_DELETE(m_wing_down);
}

void UnknownBossAnimator::SetState(const State& state)
{
	m_state = state;
	switch (m_state)
	{
		case State::LIE:
			if (m_curAnimation != m_lie_idle)
				PlayAnimation(m_lie_idle);
			SetDefaultAnimation(m_lie_idle);
			break;
		case State::STAND:
			if (m_curAnimation != m_stand_idle)
				PlayAnimation(m_stand_idle);
			SetDefaultAnimation(m_stand_idle);
			break;
		case State::WING:
			if (m_curAnimation != m_wing_idle)
				PlayAnimation(m_wing_idle);
			SetDefaultAnimation(m_wing_idle);
			break;
	}
}

void UnknownBossAnimator::SetPop()
{
	switch (m_state)
	{
		case State::LIE:
			PlayAnimation(m_lie_pop);
			break;
		case State::STAND:
			PlayAnimation(m_stand_crouch_pop);
			break;
		case State::WING:
			PlayAnimation(m_wing_pop);
			break;
	}
}

void UnknownBossAnimator::SetUpOnWing()
{
	PlayAnimation(m_wing_up);
}

bool UnknownBossAnimator::isPopping()
{
	return
		m_curAnimation == m_lie_pop ||
		m_curAnimation == m_stand_crouch_pop ||
		m_curAnimation == m_wing_pop ||
		m_curAnimation == m_wing_up ||
		m_curAnimation == m_wing_down;
}
