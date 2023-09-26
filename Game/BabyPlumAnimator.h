#pragma once
#ifndef __BabyPlumAnimator_h__
#define __BabyPlumAnimator_h__

class BabyPlumAnimator : public Animator
{
public:
	enum class Direction
	{
		LEFTUP, RIGHTUP, LEFTDOWN, RIGHTDOWN, NODIRECTION
	};

private:
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_idle;
	Animation* m_awake;
	Animation* m_spin;

	bool m_readyToStamp;
	Animation* m_stamp;

	Animation* m_reflectReady;
	// Direction for reflect animation
	Direction m_direction;
	bool m_reflecting;
	Animation* m_reflectRightUp;
	Animation* m_reflectRightDown;

	bool m_readyToStamp2;
	Animation* m_stamp2;

	Animation* m_defeat;

public:
	void PlayAwake();
	void PlayIdle();
	void PlaySpin();
	void PlayStamp();
	void PlayStamp2();
	void PlayDefeat();

	void SetReflectState(const bool& enable);
	void SetDirection(const Direction& direction);
	Direction VectorToDirection(const Vector2& v) const;
	void PlayReflectReady();

	bool isPlayingAwake() const;
	bool isPlayingSpin() const;
	bool isReflecting() const;
	bool isPlayingAttack() const;

	Delegate<void> OnAwakeAnimated;
	Delegate<void> OnReflectReadyAnimated;
	// Timing to make projectiles
	Delegate<void> OnStamped;
	Delegate<void> OnStampAnimated;
	Delegate<void> OnSpinAnimated;
	Delegate<void> OnStamped2;
	Delegate<void> OnDefeatAnimated;

private:
	void PlayReflectToRightUp();
	void PlayReflectToRightDown();
};

#endif
