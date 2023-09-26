#include "stdafx.h"
#include "PlayerBodyAnimator.h"

void PlayerBodyAnimator::OnAwake()
{
	m_forward_idle = new Animation(true);
	m_forward_idle->AddLocalPosition(0, { 0, 0 });
	m_forward_idle->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/body_forward3")));
	m_forward_idle->EndEdit();

	const float walkInterval = 0.05f;

	m_forward_walk = new Animation(true);
	m_forward_walk->AddLocalPosition(0, { 0, 0 });
	m_forward_walk->AddSprite(walkInterval * 1, SpriteManager::Find(TEXT("character_001_isaac/body_forward1")));
	m_forward_walk->AddSprite(walkInterval * 2, SpriteManager::Find(TEXT("character_001_isaac/body_forward2")));
	m_forward_walk->AddSprite(walkInterval * 3, SpriteManager::Find(TEXT("character_001_isaac/body_forward3")));
	m_forward_walk->AddSprite(walkInterval * 4, SpriteManager::Find(TEXT("character_001_isaac/body_forward4")));
	m_forward_walk->AddSprite(walkInterval * 5, SpriteManager::Find(TEXT("character_001_isaac/body_forward5")));
	m_forward_walk->AddSprite(walkInterval * 6, SpriteManager::Find(TEXT("character_001_isaac/body_forward6")));
	m_forward_walk->AddSprite(walkInterval * 7, SpriteManager::Find(TEXT("character_001_isaac/body_forward7")));
	m_forward_walk->AddSprite(walkInterval * 8, SpriteManager::Find(TEXT("character_001_isaac/body_forward8")));
	m_forward_walk->AddSprite(walkInterval * 9, SpriteManager::Find(TEXT("character_001_isaac/body_forward9")));
	m_forward_walk->AddSprite(walkInterval * 10, SpriteManager::Find(TEXT("character_001_isaac/body_forward10")));
	m_forward_walk->AddSprite(walkInterval * 11, SpriteManager::Find(TEXT("character_001_isaac/body_forward1")));
	m_forward_walk->EndEdit();

	m_right_walk = new Animation(true);
	m_right_walk->AddLocalPosition(0, { 0, 0 });
	m_right_walk->AddSprite(walkInterval * 1, SpriteManager::Find(TEXT("character_001_isaac/body_right1")));
	m_right_walk->AddSprite(walkInterval * 2, SpriteManager::Find(TEXT("character_001_isaac/body_right2")));
	m_right_walk->AddSprite(walkInterval * 3, SpriteManager::Find(TEXT("character_001_isaac/body_right3")));
	m_right_walk->AddSprite(walkInterval * 4, SpriteManager::Find(TEXT("character_001_isaac/body_right4")));
	m_right_walk->AddSprite(walkInterval * 5, SpriteManager::Find(TEXT("character_001_isaac/body_right5")));
	m_right_walk->AddSprite(walkInterval * 6, SpriteManager::Find(TEXT("character_001_isaac/body_right6")));
	m_right_walk->AddSprite(walkInterval * 7, SpriteManager::Find(TEXT("character_001_isaac/body_right7")));
	m_right_walk->AddSprite(walkInterval * 8, SpriteManager::Find(TEXT("character_001_isaac/body_right8")));
	m_right_walk->AddSprite(walkInterval * 9, SpriteManager::Find(TEXT("character_001_isaac/body_right9")));
	m_right_walk->AddSprite(walkInterval * 10, SpriteManager::Find(TEXT("character_001_isaac/body_right10")));
	m_right_walk->AddSprite(walkInterval * 11, SpriteManager::Find(TEXT("character_001_isaac/body_right1")));
	m_right_walk->EndEdit();

	m_gotItem = new Animation(false);
	m_gotItem->AddLocalPosition(0, { 0, 11 });
	m_gotItem->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/got_item")));
	m_gotItem->AddSprite(1.0f, SpriteManager::Find(TEXT("character_001_isaac/got_item")));
	m_gotItem->EndEdit();

	m_brimston_forward_idle = new Animation(true);
	m_brimston_forward_idle->AddLocalPosition(0, { 0, 0 });
	m_brimston_forward_idle->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward1")));
	m_brimston_forward_idle->EndEdit();

	m_brimston_forward_walk = new Animation(true);
	m_brimston_forward_walk->AddLocalPosition(0, { 0, 0 });
	m_brimston_forward_walk->AddSprite(walkInterval * 1, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward1")));
	m_brimston_forward_walk->AddSprite(walkInterval * 2, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward2")));
	m_brimston_forward_walk->AddSprite(walkInterval * 3, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward3")));
	m_brimston_forward_walk->AddSprite(walkInterval * 4, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward4")));
	m_brimston_forward_walk->AddSprite(walkInterval * 5, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward5")));
	m_brimston_forward_walk->AddSprite(walkInterval * 6, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward6")));
	m_brimston_forward_walk->AddSprite(walkInterval * 7, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward7")));
	m_brimston_forward_walk->AddSprite(walkInterval * 8, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward8")));
	m_brimston_forward_walk->AddSprite(walkInterval * 9, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward9")));
	m_brimston_forward_walk->AddSprite(walkInterval * 10, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward10")));
	m_brimston_forward_walk->AddSprite(walkInterval * 11, SpriteManager::Find(TEXT("costume_019_brimstone2/body_forward1")));
	m_brimston_forward_walk->EndEdit();

	m_brimston_right_walk = new Animation(true);
	m_brimston_right_walk->AddLocalPosition(0, { 0, 0 });
	m_brimston_right_walk->AddSprite(walkInterval * 1, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right1")));
	m_brimston_right_walk->AddSprite(walkInterval * 2, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right2")));
	m_brimston_right_walk->AddSprite(walkInterval * 3, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right3")));
	m_brimston_right_walk->AddSprite(walkInterval * 4, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right4")));
	m_brimston_right_walk->AddSprite(walkInterval * 5, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right5")));
	m_brimston_right_walk->AddSprite(walkInterval * 6, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right6")));
	m_brimston_right_walk->AddSprite(walkInterval * 7, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right7")));
	m_brimston_right_walk->AddSprite(walkInterval * 8, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right8")));
	m_brimston_right_walk->AddSprite(walkInterval * 9, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right9")));
	m_brimston_right_walk->AddSprite(walkInterval * 10, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right10")));
	m_brimston_right_walk->AddSprite(walkInterval * 11, SpriteManager::Find(TEXT("costume_019_brimstone2/body_right1")));
	m_brimston_right_walk->EndEdit();

	m_direction = BodyDirection::FORWARD;
	m_state = BodyState::IDLE;
	//m_isBrimston = false;
	setIsBrimston(false);
}

void PlayerBodyAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
	*defaultAnimtiaon = m_forward_idle;
}

void PlayerBodyAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
	if (currentAnimation == m_gotItem)
		return;

	Vector2 localSize = transform()->localSize();
	localSize = { fabsf(localSize.x),fabsf(localSize.y) };
	if (m_state == BodyState::WALK && m_direction == BodyDirection::LEFT)
		localSize.x *= -1;
	transform()->setLocalSize(localSize);

	switch (m_state)
	{
		case BodyState::IDLE:
			switch (m_direction)
			{
				case BodyDirection::LEFT:
				case BodyDirection::RIGHT:
				case BodyDirection::FORWARD:
				case BodyDirection::BACKWARD:
					if (!m_isBrimston)
					{
						if (m_curAnimation == m_forward_idle) break;
						PlayAnimation(m_forward_idle);
					}
					else
					{
						if (m_curAnimation == m_brimston_forward_idle) break;
						PlayAnimation(m_brimston_forward_idle);
					}
					break;
			}
			break;
		case BodyState::WALK:
			switch (m_direction)
			{
				case BodyDirection::LEFT:
				case BodyDirection::RIGHT:
					if (!m_isBrimston)
					{
						if (m_curAnimation == m_right_walk) break;
						PlayAnimation(m_right_walk);
					}
					else
					{
						if (m_curAnimation == m_brimston_right_walk) break;
						PlayAnimation(m_brimston_right_walk);
					}
					break;
				case BodyDirection::FORWARD:
				case BodyDirection::BACKWARD:
					if (!m_isBrimston)
					{
						if (m_curAnimation == m_forward_walk) break;
						PlayAnimation(m_forward_walk);
					}
					else
					{
						if (m_curAnimation == m_brimston_forward_walk) break;
						PlayAnimation(m_brimston_forward_walk);
					}
					break;
			}
			break;
	}
}

void PlayerBodyAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
}

void PlayerBodyAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_forward_idle);
	SAFE_DELETE(m_forward_walk);
	SAFE_DELETE(m_right_walk);
	SAFE_DELETE(m_gotItem);
	SAFE_DELETE(m_brimston_forward_idle);
	SAFE_DELETE(m_brimston_forward_walk);
	SAFE_DELETE(m_brimston_right_walk);
}

void PlayerBodyAnimator::SetDirection(const BodyDirection& direction)
{
	m_direction = direction;
}

void PlayerBodyAnimator::SetState(const BodyState& state)
{
	m_state = state;
}

void PlayerBodyAnimator::PlayGotItem()
{
	PlayAnimation(m_gotItem);
}

bool PlayerBodyAnimator::isPlayingGotItem()
{
	return (m_curAnimation == m_gotItem);
}

void PlayerBodyAnimator::setIsBrimston(const bool& value)
{
	if (m_isBrimston == value)
		return;
	m_isBrimston = value;
	if (value)
	{
		SetDefaultAnimation(m_forward_idle);
	}
	else
	{
		SetDefaultAnimation(m_brimston_forward_idle);
	}
}
