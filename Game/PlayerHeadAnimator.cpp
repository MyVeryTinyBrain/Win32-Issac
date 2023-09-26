#include "stdafx.h"
#include "PlayerHeadAnimator.h"

void PlayerHeadAnimator::OnAwake()
{
	const float closeDelay = 0.1f;
	const float changeDirectionDelay = 0.5f;

	m_forward_default = new Animation(true);
	m_forward_default->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/head_forward")));
	m_forward_default->EndEdit();

	m_forward_close = new Animation(false);
	m_forward_close->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/head_forward_close")));
	m_forward_close->AddSprite(closeDelay, SpriteManager::Find(TEXT("character_001_isaac/head_forward")));
	m_forward_close->AddSprite(changeDirectionDelay, SpriteManager::Find(TEXT("character_001_isaac/head_forward")));
	m_forward_close->EndEdit();

	m_backward_default = new Animation(true);
	m_backward_default->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/head_back")));
	m_backward_default->EndEdit();

	m_backward_close = new Animation(false);
	m_backward_close->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/head_back_close")));
	m_backward_close->AddSprite(closeDelay, SpriteManager::Find(TEXT("character_001_isaac/head_back")));
	m_backward_close->AddSprite(changeDirectionDelay, SpriteManager::Find(TEXT("character_001_isaac/head_back")));
	m_backward_close->EndEdit();

	m_right_default = new Animation(true);
	m_right_default->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/head_right")));
	m_right_default->EndEdit();

	m_right_close = new Animation(false);
	m_right_close->AddSprite(0, SpriteManager::Find(TEXT("character_001_isaac/head_right_close")));
	m_right_close->AddSprite(closeDelay, SpriteManager::Find(TEXT("character_001_isaac/head_right")));
	m_right_close->AddSprite(changeDirectionDelay, SpriteManager::Find(TEXT("character_001_isaac/head_right")));
	m_right_close->EndEdit();

	m_gotItem = new Animation(false);
	m_gotItem->AddSprite(0, nullptr);
	m_gotItem->AddSprite(1.0f, nullptr);
	m_gotItem->EndEdit();

	m_brimston_forward_default = new Animation(true);
	m_brimston_forward_default->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward1")));
	m_brimston_forward_default->EndEdit();

	m_brimston_backward_default = new Animation(true);
	m_brimston_backward_default->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back1")));
	m_brimston_backward_default->EndEdit();

	m_brimston_right_default = new Animation(true);
	m_brimston_right_default->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right1")));
	m_brimston_right_default->EndEdit();

	m_brimston_forward_fire = new Animation(false);
	m_brimston_forward_fire->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward_fire")));
	m_brimston_forward_fire->AddSprite(1, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward_fire")));
	m_brimston_forward_fire->EndEdit();

	m_brimston_backward_fire = new Animation(false);
	m_brimston_backward_fire->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back_fire")));
	m_brimston_backward_fire->AddSprite(1, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back_fire")));
	m_brimston_backward_fire->EndEdit();

	m_brimston_right_fire = new Animation(false);
	m_brimston_right_fire->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right_fire")));
	m_brimston_right_fire->AddSprite(1, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right_fire")));
	m_brimston_right_fire->EndEdit();

	m_brimston_forward_charging = new Animation(false);
	m_brimston_forward_charging->AddSprite(0.17f * 0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward2")));
	m_brimston_forward_charging->AddSprite(0.17f * 1, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward3")));
	m_brimston_forward_charging->AddSprite(0.17f * 2, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward4")));
	m_brimston_forward_charging->AddSprite(0.17f * 3, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward5")));
	m_brimston_forward_charging->AddSprite(0.17f * 4, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward6")));
	m_brimston_forward_charging->AddSprite(0.17f * 5, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward7")));
	m_brimston_forward_charging->AddSprite(0.17f * 6, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward7")));
	m_brimston_forward_charging->EndEdit();

	m_brimston_backward_charging = new Animation(false);
	m_brimston_backward_charging->AddSprite(0.17f * 0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back2")));
	m_brimston_backward_charging->AddSprite(0.17f * 1, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back3")));
	m_brimston_backward_charging->AddSprite(0.17f * 2, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back4")));
	m_brimston_backward_charging->AddSprite(0.17f * 3, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back5")));
	m_brimston_backward_charging->AddSprite(0.17f * 4, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back6")));
	m_brimston_backward_charging->AddSprite(0.17f * 5, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back7")));
	m_brimston_backward_charging->AddSprite(0.17f * 6, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back7")));
	m_brimston_backward_charging->EndEdit();

	m_brimston_right_charging = new Animation(false);
	m_brimston_right_charging->AddSprite(0.17f * 0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right2")));
	m_brimston_right_charging->AddSprite(0.17f * 1, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right3")));
	m_brimston_right_charging->AddSprite(0.17f * 2, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right4")));
	m_brimston_right_charging->AddSprite(0.17f * 3, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right5")));
	m_brimston_right_charging->AddSprite(0.17f * 4, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right6")));
	m_brimston_right_charging->AddSprite(0.17f * 5, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right7")));
	m_brimston_right_charging->AddSprite(0.17f * 6, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right7")));
	m_brimston_right_charging->EndEdit();

	m_brimston_forward_charged = new Animation(true);
	m_brimston_forward_charged->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_forward7")));
	m_brimston_forward_charged->EndEdit();

	m_brimston_backward_charged = new Animation(true);
	m_brimston_backward_charged->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_back7")));
	m_brimston_backward_charged->EndEdit();

	m_brimston_right_charged = new Animation(true);
	m_brimston_right_charged->AddSprite(0, SpriteManager::Find(TEXT("costume_019_brimstone2/head_right7")));
	m_brimston_right_charged->EndEdit();

	m_direction = HeadDirection::FORWARD;
	m_state = HeadState::IDLE;
	m_isBrimston = false;
}

void PlayerHeadAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
	*defaultAnimtiaon = m_forward_default;
}

void PlayerHeadAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
	if (currentAnimation == m_gotItem)
		return;

	Vector2 localSize = transform()->localSize();
	localSize = { fabsf(localSize.x),fabsf(localSize.y) };
	if (m_direction == HeadDirection::LEFT)
		localSize.x *= -1;
	transform()->setLocalSize(localSize);

	if (!m_isBrimston)
	{
		switch (m_state)
		{
			case HeadState::IDLE:
				if (isPlayingClose()) break;
				switch (m_direction)
				{
					case HeadDirection::LEFT:
					case HeadDirection::RIGHT:
						if (m_curAnimation == m_right_default) break;
						PlayAnimation(m_right_default);
						break;
					case HeadDirection::FORWARD:
						if (m_curAnimation == m_forward_default) break;
						PlayAnimation(m_forward_default);
						break;
					case HeadDirection::BACKWARD:
						if (m_curAnimation == m_backward_default) break;
						PlayAnimation(m_backward_default);
						break;
				}
				break;
			case HeadState::CLOSE:
				m_state = HeadState::IDLE;
				switch (m_direction)
				{
					case HeadDirection::LEFT:
					case HeadDirection::RIGHT:
						PlayAnimation(m_right_close);
						break;
					case HeadDirection::FORWARD:
						PlayAnimation(m_forward_close);
						break;
					case HeadDirection::BACKWARD:
						PlayAnimation(m_backward_close);
						break;
				}
				break;
		}
	}
	else
	{
		bool wasCharging =
			m_curAnimation == m_brimston_right_charging ||
			m_curAnimation == m_brimston_forward_charging ||
			m_curAnimation == m_brimston_backward_charging;
		bool wasCharged =
			m_curAnimation == m_brimston_right_charged ||
			m_curAnimation == m_brimston_forward_charged ||
			m_curAnimation == m_brimston_backward_charged;
		switch (m_state)
		{
			case HeadState::IDLE:
				switch (m_direction)
				{
					case HeadDirection::LEFT:
					case HeadDirection::RIGHT:
						if (m_curAnimation == m_brimston_right_default) break;
						PlayAnimation(m_brimston_right_default);
						break;
					case HeadDirection::FORWARD:
						if (m_curAnimation == m_brimston_forward_default) break;
						PlayAnimation(m_brimston_forward_default);
						break;
					case HeadDirection::BACKWARD:
						if (m_curAnimation == m_brimston_backward_default) break;
						PlayAnimation(m_brimston_backward_default);
						break;
				}
				break;
			case HeadState::CHARGING:
				switch (m_direction)
				{
					case HeadDirection::LEFT:
					case HeadDirection::RIGHT:
						if (m_curAnimation == m_brimston_right_charging) break;
						PlayAnimation(m_brimston_right_charging, wasCharging);
						break;
					case HeadDirection::FORWARD:
						if (m_curAnimation == m_brimston_forward_charging) break;
						PlayAnimation(m_brimston_forward_charging, wasCharging);
						break;
					case HeadDirection::BACKWARD:
						if (m_curAnimation == m_brimston_backward_charging) break;
						PlayAnimation(m_brimston_backward_charging, wasCharging);
						break;
				}
				break;
			case HeadState::CHARGED:
				switch (m_direction)
				{
					case HeadDirection::LEFT:
					case HeadDirection::RIGHT:
						if (m_curAnimation == m_brimston_right_charged) break;
						PlayAnimation(m_brimston_right_charged);
						break;
					case HeadDirection::FORWARD:
						if (m_curAnimation == m_brimston_forward_charged) break;
						PlayAnimation(m_brimston_forward_charged);
						break;
					case HeadDirection::BACKWARD:
						if (m_curAnimation == m_brimston_backward_charged) break;
						PlayAnimation(m_brimston_backward_charged);
						break;
				}
				break;
			case HeadState::FIRE:
				switch (m_direction)
				{
					case HeadDirection::LEFT:
					case HeadDirection::RIGHT:
						if (m_curAnimation == m_brimston_right_fire) break;
						PlayAnimation(m_brimston_right_fire);
						break;
					case HeadDirection::FORWARD:
						if (m_curAnimation == m_brimston_forward_fire) break;
						PlayAnimation(m_brimston_forward_fire);
						break;
					case HeadDirection::BACKWARD:
						if (m_curAnimation == m_brimston_backward_fire) break;
						PlayAnimation(m_brimston_backward_fire);
						break;
				}
				break;
		}
	}
}

void PlayerHeadAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	bool wasCharging =
		prev == m_brimston_right_charging ||
		prev == m_brimston_forward_charging ||
		prev == m_brimston_backward_charging;
	bool wasFire = 
		prev == m_brimston_right_fire ||
		prev == m_brimston_forward_fire ||
		prev == m_brimston_backward_fire;
	if (wasCharging && next == m_defaultAnimation)
	{
		if (prev == m_brimston_right_charging)
			PlayAnimation(m_brimston_right_charged);
		else if (prev == m_brimston_forward_charging)
			PlayAnimation(m_brimston_forward_charged);
		else if (prev == m_brimston_backward_charging)
			PlayAnimation(m_brimston_backward_charged);
		m_state = HeadState::CHARGED;
	}
	if (wasFire)
	{
		m_state = HeadState::IDLE;
	}
}

void PlayerHeadAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_forward_default);
	SAFE_DELETE(m_forward_close);
	SAFE_DELETE(m_backward_default);
	SAFE_DELETE(m_backward_close);
	SAFE_DELETE(m_right_default);
	SAFE_DELETE(m_right_close);
	SAFE_DELETE(m_gotItem);
	SAFE_DELETE(m_brimston_forward_default);
	SAFE_DELETE(m_brimston_forward_fire);
	SAFE_DELETE(m_brimston_backward_default);
	SAFE_DELETE(m_brimston_backward_fire);
	SAFE_DELETE(m_brimston_right_default);
	SAFE_DELETE(m_brimston_right_fire);
	SAFE_DELETE(m_brimston_forward_charging);
	SAFE_DELETE(m_brimston_backward_charging);
	SAFE_DELETE(m_brimston_right_charging);
	SAFE_DELETE(m_brimston_forward_charged);
	SAFE_DELETE(m_brimston_backward_charged);
	SAFE_DELETE(m_brimston_right_charged);
}

void PlayerHeadAnimator::SetIdle(const HeadDirection& direction)
{
	if (!m_isBrimston && isPlayingClose())
		return;
	if (m_isBrimston && isPlayingCharge())
		return;
	m_direction = direction;
	m_state = HeadState::IDLE;
}

void PlayerHeadAnimator::SetClose(const HeadDirection& direction)
{
	m_direction = direction;
	m_state = HeadState::CLOSE;
}

void PlayerHeadAnimator::PlayGotItem()
{
	PlayAnimation(m_gotItem);
}

void PlayerHeadAnimator::SetChargeSpeed(const float& speed)
{
	m_brimston_forward_charging->setSpeed(speed);
	m_brimston_backward_charging->setSpeed(speed);
	m_brimston_right_charging->setSpeed(speed);
}

void PlayerHeadAnimator::SetFireSpeed(const float& speed)
{
	m_brimston_forward_fire->setSpeed(speed);
	m_brimston_backward_fire->setSpeed(speed);
	m_brimston_right_fire->setSpeed(speed);
}

void PlayerHeadAnimator::Charge()
{
	bool wasCharging =
		m_curAnimation == m_brimston_right_charging ||
		m_curAnimation == m_brimston_forward_charging ||
		m_curAnimation == m_brimston_backward_charging;
	bool wasCharged =
		m_curAnimation == m_brimston_right_charged ||
		m_curAnimation == m_brimston_forward_charged ||
		m_curAnimation == m_brimston_backward_charged;
	bool wasFired = 
		m_curAnimation == m_brimston_right_fire ||
		m_curAnimation == m_brimston_forward_fire ||
		m_curAnimation == m_brimston_backward_fire;
	if (wasCharging == false && wasCharged == false && wasFired == false)
	{
		m_state = HeadState::CHARGING;
	}
}

bool PlayerHeadAnimator::isCharged() const
{
	bool wasCharged =
		m_curAnimation == m_brimston_right_charged ||
		m_curAnimation == m_brimston_forward_charged ||
		m_curAnimation == m_brimston_backward_charged;
	return wasCharged;
}

bool PlayerHeadAnimator::StopChargeOrFire()
{
	bool wasCharging =
		m_curAnimation == m_brimston_right_charging ||
		m_curAnimation == m_brimston_forward_charging ||
		m_curAnimation == m_brimston_backward_charging;
	bool wasCharged =
		m_curAnimation == m_brimston_right_charged ||
		m_curAnimation == m_brimston_forward_charged ||
		m_curAnimation == m_brimston_backward_charged;
	if (m_state == HeadState::FIRE)
	{
		return false;
	}
	else if (wasCharging)
	{
		PlayAnimation(m_brimston_forward_default);
		m_state = HeadState::IDLE;
		return false;
	}
	else if (wasCharged)
	{
		m_state = HeadState::FIRE;
		return true;
	}
}

void PlayerHeadAnimator::setIsBrimston(const bool& value)
{
	if (m_isBrimston == value)
		return;
	m_isBrimston = value;
	if (!value)
	{
		SetDefaultAnimation(m_forward_default);
	}
	else
	{
		SetDefaultAnimation(m_brimston_forward_default);
	}
}

void PlayerHeadAnimator::setDirection(const HeadDirection& direction)
{
	bool wasFire =
		m_curAnimation == m_brimston_right_fire ||
		m_curAnimation == m_brimston_forward_fire ||
		m_curAnimation == m_brimston_backward_fire;
	if (wasFire)
		return;
	m_direction = direction;
}

const PlayerHeadAnimator::HeadDirection& PlayerHeadAnimator::direction() const
{
	return m_direction;
}

bool PlayerHeadAnimator::isPlayingClose()
{
	return
		m_curAnimation == m_forward_close ||
		m_curAnimation == m_backward_close ||
		m_curAnimation == m_right_close;
}

bool PlayerHeadAnimator::isPlayingCharge()
{
	bool wasCharging =
		m_curAnimation == m_brimston_right_charging ||
		m_curAnimation == m_brimston_forward_charging ||
		m_curAnimation == m_brimston_backward_charging;
	bool wasCharged =
		m_curAnimation == m_brimston_right_charged ||
		m_curAnimation == m_brimston_forward_charged ||
		m_curAnimation == m_brimston_backward_charged;
	bool wasFire = 
		m_curAnimation == m_brimston_right_fire ||
		m_curAnimation == m_brimston_forward_fire ||
		m_curAnimation == m_brimston_backward_fire;
	return wasCharging || wasCharged || wasFire;
}
