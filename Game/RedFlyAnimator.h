#pragma once
#ifndef __RedFlyAnimator_h__
#define __RedFlyAnimator_h__

class RedFlyAnimator : public Animator
{
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_default{};
	Animation* m_dead{};
	bool m_deadAnimated{};

public:
	Delegate<void> OnDeadAnimated;

	void PlayDefault();
	void PlayDead();
};

#endif
