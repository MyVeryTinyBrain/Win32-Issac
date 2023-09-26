#include "stdafx.h"
#include "BabyPlumAnimator.h"
#include "Define.h"

void BabyPlumAnimator::OnAwake()
{
	Sprite* idle01 = SpriteManager::Find(TEXT("boss_baby_plum/idle01"));
	Sprite* idle02 = SpriteManager::Find(TEXT("boss_baby_plum/idle02"));
	
	m_idle = new Animation(true);
	const float delay1 = 0.05f;
	const float end1 = 1.0f;
	m_idle->AddLocalSize(0, { 1,1 });
	m_idle->AddSprite(delay1 * 0, idle01);
	m_idle->AddSprite(delay1 * 1, idle02);
	m_idle->AddSprite(delay1 * 2, idle01);
	m_idle->AddSprite(delay1 * 3, idle02);
	m_idle->AddSprite(delay1 * 4, idle01);
	m_idle->AddSprite(delay1 * 5, idle02);
	m_idle->AddSprite(delay1 * 6, idle01);
	m_idle->AddSprite(delay1 * 7, idle02);
	m_idle->AddSprite(delay1 * 8, idle01);
	m_idle->AddSprite(delay1 * 9, idle02);
	m_idle->AddSprite(delay1 * 10, idle01);
	m_idle->AddSprite(delay1 * 10, idle01);
	m_idle->AddSprite(delay1 * 11, idle02);
	m_idle->AddSprite(delay1 * 12, idle01);
	m_idle->AddSprite(delay1 * 13, idle02);
	m_idle->AddSprite(delay1 * 14, idle01);
	m_idle->AddSprite(delay1 * 15, idle02);
	m_idle->AddSprite(delay1 * 16, idle01);
	m_idle->AddSprite(delay1 * 17, idle02);
	m_idle->AddSprite(delay1 * 18, idle01);
	m_idle->AddSprite(delay1 * 19, idle02);
	m_idle->AddSprite(delay1 * 20, idle01);
	m_idle->AddLocalSize(0, { 1,1 });
	m_idle->AddLocalSize(end1 * 0.5f, { 1.15f,1.25f });
	m_idle->AddLocalSize(end1, { 1,1 });
	m_idle->EndEdit();

	Sprite* awake_sit = SpriteManager::Find(TEXT("boss_baby_plum/awake_sit"));

	m_awake = new Animation(false);
	m_awake->AddLocalPosition(0, {0, -FLYING_HEIGHT + 5 });
	m_awake->AddSprite(0, awake_sit);
	m_awake->AddLocalSize(0, { 1,1 });
	m_awake->AddLocalSize(0.1f, { 0.7f,0.7f });
	m_awake->AddLocalSize(0.2f, { 1.3f,1.3f });
	m_awake->AddLocalSize(0.3f, { 1,1 });
	m_awake->AddLocalSize(1.2f, { 1,1 });
	m_awake->AddLocalSize(1.3f, { 0.7f,0.7f });
	m_awake->AddLocalPosition(1.3f, { 0, -FLYING_HEIGHT + 5 });
	m_awake->AddSprite(1.3f, SpriteManager::Find(TEXT("boss_baby_plum/awake01")));
	m_awake->AddLocalPosition(1.31f, {0, -FLYING_HEIGHT + 5 });
	m_awake->AddLocalSize(1.4f, { 1.2f,1.2f });
	m_awake->AddLocalSize(1.5f, { 1, 1 });
	const float end2 = 1.5f;
	const float delay2 = 0.05f;
	m_awake->AddLocalPosition(end2 + delay2 * 0, { 0,-FLYING_HEIGHT + 5 });
	m_awake->AddSprite(end2 + delay2 * 0, SpriteManager::Find(TEXT("boss_baby_plum/awake01")));
	m_awake->AddSprite(end2 + delay2 * 1, SpriteManager::Find(TEXT("boss_baby_plum/awake02")));
	m_awake->AddSprite(end2 + delay2 * 2, SpriteManager::Find(TEXT("boss_baby_plum/awake03")));
	m_awake->AddSprite(end2 + delay2 * 3, SpriteManager::Find(TEXT("boss_baby_plum/awake04")));
	m_awake->AddSprite(end2 + delay2 * 4, SpriteManager::Find(TEXT("boss_baby_plum/awake05")));
	m_awake->AddSprite(end2 + delay2 * 5, SpriteManager::Find(TEXT("boss_baby_plum/awake06")));
	m_awake->AddSprite(end2 + delay2 * 6, SpriteManager::Find(TEXT("boss_baby_plum/awake07")));
	m_awake->AddSprite(end2 + delay2 * 7, SpriteManager::Find(TEXT("boss_baby_plum/awake08")));
	m_awake->AddSprite(end2 + delay2 * 8, SpriteManager::Find(TEXT("boss_baby_plum/awake09")));
	m_awake->AddSprite(end2 + delay2 * 9, SpriteManager::Find(TEXT("boss_baby_plum/awake10")));
	m_awake->AddSprite(end2 + delay2 * 10, SpriteManager::Find(TEXT("boss_baby_plum/awake11")));
	m_awake->AddSprite(end2 + delay2 * 11, SpriteManager::Find(TEXT("boss_baby_plum/awake12")));
	m_awake->AddSprite(end2 + delay2 * 12, SpriteManager::Find(TEXT("boss_baby_plum/awake13")));
	m_awake->AddLocalPosition(end2 + delay2 * 12, { 0,0 });
	m_awake->EndEdit();

	// Play first animation
	PlayAwake();

	Sprite* spin09 = SpriteManager::Find(TEXT("boss_baby_plum/spin09"));
	Sprite* spin10 = SpriteManager::Find(TEXT("boss_baby_plum/spin10"));
	const float delay3 = 0.05f;
	m_spin = new Animation(false);
	m_spin->AddLocalSize(delay3 * 0, { 1,1 });
	m_spin->AddSprite(delay3 * 0, SpriteManager::Find(TEXT("boss_baby_plum/spin01")));
	m_spin->AddSprite(delay3 * 1, SpriteManager::Find(TEXT("boss_baby_plum/spin02")));
	m_spin->AddLocalSize(delay3 * 2, { 1,0.7f });
	m_spin->AddSprite(delay3 * 2, SpriteManager::Find(TEXT("boss_baby_plum/spin03")));
	m_spin->AddSprite(delay3 * 3, SpriteManager::Find(TEXT("boss_baby_plum/spin04")));
	m_spin->AddLocalSize(delay3 * 4, { 1,1.4f });
	m_spin->AddSprite(delay3 * 4, SpriteManager::Find(TEXT("boss_baby_plum/spin05")));
	m_spin->AddSprite(delay3 * 5, SpriteManager::Find(TEXT("boss_baby_plum/spin06")));
	m_spin->AddSprite(delay3 * 6, SpriteManager::Find(TEXT("boss_baby_plum/spin07")));
	m_spin->AddSprite(delay3 * 7, SpriteManager::Find(TEXT("boss_baby_plum/spin08")));
	m_spin->AddLocalSize(delay3 * 8, { 1,1 });
	m_spin->AddSprite(delay3 * 8, spin09);
	m_spin->AddSprite(delay3 * 9, spin10);
	m_spin->AddSprite(delay3 * 10, spin09);
	m_spin->AddLocalSize(delay3 * 11, { 1.15f,1.25f });
	m_spin->AddSprite(delay3 * 11, spin10);
	m_spin->AddSprite(delay3 * 12, spin09);
	m_spin->AddSprite(delay3 * 13, spin10);
	m_spin->AddSprite(delay3 * 14, spin09);
	m_spin->AddLocalSize(delay3 * 15, { 1, 1 });
	m_spin->AddSprite(delay3 * 15, spin10);
	m_spin->EndEdit();

	m_readyToStamp = false;
	Sprite* stamp_wait01 = SpriteManager::Find(TEXT("boss_baby_plum/stamp_wait01"));
	Sprite* stamp_wait02 = SpriteManager::Find(TEXT("boss_baby_plum/stamp_wait02"));
	m_stamp = new Animation(false);
	m_stamp->AddSprite(0, stamp_wait01);
	m_stamp->AddSprite(0, stamp_wait02);
	m_stamp->AddSprite(0, stamp_wait01);
	m_stamp->AddSprite(0.05f, stamp_wait02);
	m_stamp->AddSprite(0.1f, stamp_wait01);
	m_stamp->AddSprite(0.15f, stamp_wait02);
	m_stamp->AddSprite(0.2f, stamp_wait01);
	m_stamp->AddLocalPosition(0, {});
	m_stamp->AddLocalSize(0, { 1,1 });
	m_stamp->AddLocalSize(0.05f, { 0.8f,0.85f });
	m_stamp->AddLocalSize(0.1f, { 1.2f,1.25f });
	m_stamp->AddLocalPosition(0.2f, {0, 28});
	m_stamp->AddLocalSize(0.2f, { 1, 1 });
	m_stamp->AddLocalPosition(0.3f, {0, 30});
	m_stamp->AddSprite(0.3f, SpriteManager::Find(TEXT("boss_baby_plum/stamp_stamp")));
	m_stamp->AddLocalSize(0.3f, { 0.6f, 1.35f });
	m_stamp->AddLocalPosition(0.35f, {0, -FLYING_HEIGHT});
	m_stamp->AddLocalSize(0.35f, { 1.35f, 0.6f });
	m_stamp->AddLocalSize(0.5f, { 1.4f, 0.55f });
	m_stamp->AddLocalPosition(0.5f, { 0, -FLYING_HEIGHT });
	m_stamp->AddSprite(0.5f, stamp_wait01);
	m_stamp->AddSprite(0.55f, stamp_wait02);
	m_stamp->AddSprite(0.6f, stamp_wait01);
	m_stamp->AddLocalPosition(0.6f, { 0, 0 });
	m_stamp->AddLocalSize(0.6f, { 1, 1 });
	m_stamp->EndEdit();

	m_reflecting = false;
	m_direction = Direction::NODIRECTION;
	const float delay5 = 0.05f;
	Sprite* reflect_wait01 = SpriteManager::Find(TEXT("boss_baby_plum/reflect_wait01"));
	Sprite* reflect_wait02 = SpriteManager::Find(TEXT("boss_baby_plum/reflect_wait02"));
	m_reflectReady = new Animation(false);
	m_reflectReady->AddLocalSize(delay5 * 0, { 1.3f,0.8f });
	m_reflectReady->AddSprite(delay5 * 0, reflect_wait01);
	m_reflectReady->AddSprite(delay5 * 1, reflect_wait02);
	m_reflectReady->AddLocalSize(delay5 * 2, { 0.8f,1.3f });
	m_reflectReady->AddSprite(delay5 * 2, reflect_wait01);
	m_reflectReady->AddSprite(delay5 * 3, reflect_wait02);
	m_reflectReady->AddLocalSize(delay5 * 4, { 1, 1 });
	m_reflectReady->AddSprite(delay5 * 4, reflect_wait01);
	m_reflectReady->AddSprite(delay5 * 5, reflect_wait02);
	m_reflectReady->AddSprite(delay5 * 6, reflect_wait01);
	m_reflectReady->AddSprite(delay5 * 7, reflect_wait02);
	m_reflectReady->AddSprite(delay5 * 8, reflect_wait01);
	m_reflectReady->AddSprite(delay5 * 9, reflect_wait02);
	m_reflectReady->AddSprite(delay5 * 10, reflect_wait01);
	m_reflectReady->AddSprite(delay5 * 11, reflect_wait02);
	m_reflectReady->AddSprite(delay5 * 12, reflect_wait01);
	m_reflectReady->AddLocalSize(delay5 * 13, { 0.6f,1.35f });
	m_reflectReady->AddSprite(delay5 * 13, reflect_wait02);
	m_reflectReady->AddLocalSize(delay5 * 14, { 1.2f,0.8f });
	m_reflectReady->AddSprite(delay5 * 14, reflect_wait01);
	m_reflectReady->AddSprite(delay5 * 15, reflect_wait02);
	m_reflectReady->AddLocalSize(delay5 * 15, { 1,1 });
	m_reflectReady->EndEdit();

	Sprite* reflect_up01 = SpriteManager::Find(TEXT("boss_baby_plum/reflect_up01"));
	Sprite* reflect_up02 = SpriteManager::Find(TEXT("boss_baby_plum/reflect_up02"));
	m_reflectRightUp = new Animation(true);
	m_reflectRightUp->AddSprite(0, reflect_up01);
	m_reflectRightUp->AddSprite(0.05f, reflect_up02);
	m_reflectRightUp->AddSprite(0.1f, reflect_up01);
	m_reflectRightUp->EndEdit();

	Sprite* reflect_down01 = SpriteManager::Find(TEXT("boss_baby_plum/reflect_down01"));
	Sprite* reflect_down02 = SpriteManager::Find(TEXT("boss_baby_plum/reflect_down02"));
	m_reflectRightDown = new Animation(true);
	m_reflectRightDown->AddSprite(0, reflect_down01);
	m_reflectRightDown->AddSprite(0.05f, reflect_down02);
	m_reflectRightDown->AddSprite(0.1f, reflect_down01);
	m_reflectRightDown->EndEdit();

	m_readyToStamp2 = false;
	m_stamp2 = new Animation(false);
	m_stamp2->AddSprite(0, stamp_wait01);
	m_stamp2->AddSprite(0, stamp_wait02);
	m_stamp2->AddSprite(0, stamp_wait01);
	m_stamp2->AddSprite(0.05f, stamp_wait02);
	m_stamp2->AddSprite(0.1f, stamp_wait01);
	m_stamp2->AddSprite(0.15f, stamp_wait02);
	m_stamp2->AddSprite(0.2f, stamp_wait01);
	m_stamp2->AddLocalPosition(0, {});
	m_stamp2->AddLocalSize(0, { 1,1 });
	m_stamp2->AddLocalSize(0.05f, { 0.8f,0.85f });
	m_stamp2->AddLocalSize(0.1f, { 1.2f,1.25f });
	m_stamp2->AddLocalPosition(0.6f, { 0, 28 });
	m_stamp2->AddLocalSize(0.6f, { 1, 1 });
	m_stamp2->AddLocalPosition(0.7f, { 0, 30 });
	m_stamp2->AddSprite(0.7f, SpriteManager::Find(TEXT("boss_baby_plum/stamp_stamp")));
	m_stamp2->AddLocalSize(0.7f, { 0.6f, 1.35f });
	m_stamp2->AddLocalPosition(0.75f, { 0, -FLYING_HEIGHT });
	m_stamp2->AddLocalSize(0.75f, { 1.35f, 0.6f });
	m_stamp2->AddLocalSize(0.9f, { 1.4f, 0.55f });
	m_stamp2->AddLocalPosition(0.9f, { 0, -FLYING_HEIGHT });
	m_stamp2->AddSprite(0.9f, stamp_wait01);
	m_stamp2->AddSprite(0.95f, stamp_wait02);
	m_stamp2->AddSprite(1.0f, stamp_wait01);
	m_stamp2->AddLocalPosition(1.0f, { 0, 0 });
	m_stamp2->AddLocalSize(1.0f, { 1, 1 });
	m_stamp2->EndEdit();

	Sprite* flyaway01 = SpriteManager::Find(TEXT("boss_baby_plum/flyaway01"));
	Sprite* flyaway02 = SpriteManager::Find(TEXT("boss_baby_plum/flyaway02"));
	m_defeat = new Animation(false);
	m_defeat->AddSprite(0, SpriteManager::Find(TEXT("boss_baby_plum/crying")));
	m_defeat->AddLocalPosition(0, {});
	m_defeat->AddLocalSize(0, { 1,1 });
	m_defeat->AddLocalSize(0.05f, { 0.65f,1.35f });
	m_defeat->AddLocalSize(0.15f, { 1.2f,1.0f });
	const float cryEnd = 0.8f;
	const float flyAwayTime = 2.0f;
	m_defeat->AddLocalSize(cryEnd, { 1, 1 });
	m_defeat->AddLocalPosition(cryEnd, {});
	m_defeat->AddSprite(cryEnd, flyaway01);
	for (float t = 0; t < flyAwayTime; t += 0.1f)
	{
		m_defeat->AddSprite(cryEnd + t, flyaway01);
		m_defeat->AddSprite(cryEnd + t + 0.05f, flyaway02);
	}
	m_defeat->AddLocalPosition(cryEnd + flyAwayTime, { 250,400 });
	m_defeat->EndEdit();
}

void BabyPlumAnimator::OnSetDefaultAnimation(Animation** defaultAnimtiaon)
{
	*defaultAnimtiaon = m_idle;
}

void BabyPlumAnimator::OnUpdate(Animation* currentAnimation, const float& Elapsed)
{
	if (m_readyToStamp)
	{
		if (currentAnimation != m_stamp)
		{
			m_readyToStamp = false;
		}
		else
		{
			if (m_elapsed >= 0.3f)
			{
				OnStamped();
				m_readyToStamp = false;
			}
		}
	}
	if (m_readyToStamp2)
	{
		if (currentAnimation != m_stamp2)
		{
			m_readyToStamp2 = false;
		}
		else
		{
			if (m_elapsed >= 0.7f)
			{
				OnStamped2();
				m_readyToStamp2 = false;
			}
		}
	}

	if (m_reflecting)
	{
		Vector2 localSize = transform()->localSize();
		localSize.x = fabsf(localSize.x);
		localSize.y = fabsf(localSize.y);
		switch (m_direction)
		{
			case Direction::LEFTUP:
				PlayReflectToRightUp();
				localSize.x *= -1;
				break;
			case Direction::RIGHTUP:
				PlayReflectToRightUp();
				break;
			case Direction::LEFTDOWN:
				PlayReflectToRightDown();
				localSize.x *= -1;
				break;
			case Direction::RIGHTDOWN:
				PlayReflectToRightDown();
				break;
			case Direction::NODIRECTION:
				m_reflecting = false;
				break;
		}
		transform()->setLocalSize(localSize);
	}
}

void BabyPlumAnimator::OnAnimationChanged(Animation* prev, Animation* next)
{
	if (prev == m_awake && next != m_awake)
		OnAwakeAnimated();
	if (prev == m_reflectReady && next != m_reflectReady)
		OnReflectReadyAnimated();
	if (prev == m_stamp && next != m_stamp)
		OnStampAnimated();
	if (prev == m_spin && next != m_spin)
		OnSpinAnimated();
	if (prev == m_defeat && next != m_defeat)
		OnDefeatAnimated();
}

void BabyPlumAnimator::OnPrevDestroy()
{
	SAFE_DELETE(m_idle);
	SAFE_DELETE(m_awake);
	SAFE_DELETE(m_spin);
	SAFE_DELETE(m_stamp);
	SAFE_DELETE(m_reflectReady);
	SAFE_DELETE(m_reflectRightUp);
	SAFE_DELETE(m_reflectRightDown);
	SAFE_DELETE(m_stamp2);
	SAFE_DELETE(m_defeat);
}

void BabyPlumAnimator::PlayAwake()
{
	if (m_curAnimation == m_awake)
		return;
	PlayAnimation(m_awake);
}

void BabyPlumAnimator::PlayIdle()
{
	if (m_curAnimation == m_idle)
		return;
	PlayAnimation(m_idle);
}

void BabyPlumAnimator::PlaySpin()
{
	PlayAnimation(m_spin);
}

void BabyPlumAnimator::PlayStamp()
{
	m_readyToStamp = true;
	PlayAnimation(m_stamp);
}

void BabyPlumAnimator::PlayStamp2()
{
	m_readyToStamp2 = true;
	PlayAnimation(m_stamp2);
}

void BabyPlumAnimator::PlayDefeat()
{
	if (m_curAnimation == m_defeat)
		return;
	PlayAnimation(m_defeat);
}

void BabyPlumAnimator::SetReflectState(const bool& enable)
{
	m_reflecting = enable;
}

void BabyPlumAnimator::SetDirection(const Direction& direction)
{
	m_direction = direction;
}

BabyPlumAnimator::Direction BabyPlumAnimator::VectorToDirection(const Vector2& v) const
{
	static Vector2 leftUpVec = Vector2(-1, 1).normalized();
	static Vector2 rightUpVec = Vector2(1, 1).normalized();
	static Vector2 leftDownVec = Vector2(-1, -1).normalized();
	static Vector2 rightDownVec = Vector2(1, -1).normalized();

	float leftUpDot = Vector2::Dot(v, { leftUpVec });
	float rightUpDot = Vector2::Dot(v, { rightUpVec });
	float leftDownDot = Vector2::Dot(v, { leftDownVec });
	float rightDownDot = Vector2::Dot(v, { rightDownVec });

	Direction dir = Direction::NODIRECTION;
	float max = 0;
	if (leftUpDot > max)
	{
		max = leftUpDot;
		dir = Direction::LEFTUP;
	}
	if (rightUpDot > max)
	{
		max = rightUpDot;
		dir = Direction::RIGHTUP;
	}
	if (leftDownDot > max)
	{
		max = leftDownDot;
		dir = Direction::LEFTDOWN;
	}
	if (rightDownDot > max)
	{
		max = rightDownDot;
		dir = Direction::RIGHTDOWN;
	}

	return dir;
}

void BabyPlumAnimator::PlayReflectReady()
{
	if (m_curAnimation == m_reflectReady)
		return;
	PlayAnimation(m_reflectReady);
}

bool BabyPlumAnimator::isPlayingAwake() const
{
	return (m_curAnimation == m_awake);
}

bool BabyPlumAnimator::isPlayingSpin() const
{
	return (m_curAnimation == m_spin);
}

bool BabyPlumAnimator::isReflecting() const
{
	return m_reflecting;
}

bool BabyPlumAnimator::isPlayingAttack() const
{
	return
		(m_curAnimation == m_spin) ||
		(m_curAnimation == m_stamp) ||
		(m_curAnimation == m_reflectReady)||
		(m_curAnimation == m_reflectRightUp)||
		(m_curAnimation == m_reflectRightDown)||
		(m_curAnimation == m_stamp2)
		;
}

void BabyPlumAnimator::PlayReflectToRightUp()
{
	if (m_curAnimation == m_reflectRightUp)
		return;
	PlayAnimation(m_reflectRightUp);
}

void BabyPlumAnimator::PlayReflectToRightDown()
{
	if (m_curAnimation == m_reflectRightDown)
		return;
	PlayAnimation(m_reflectRightDown);
}
