#pragma once
#ifndef __ProjectileAnimator_h__
#define __ProjectileAnimator_h__

class ProjectileAnimator : public Animator
{
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_idleAnimation;
	Animation* m_destroyAnimation;
	bool m_destroyAnimated;

public:
	void InitSetSprites
	(Sprite* s1, Sprite* s2, Sprite* s3, Sprite* s4, Sprite* s5, Sprite* s6, Sprite* s7, Sprite* s8, Sprite* s9, Sprite* s10, Sprite* s11, Sprite* s12);
	void PlayIdleAnimation();
	void PlayOnceDestroyAnimation();

	Delegate<void> OnDestroyAnimated;
};

#endif
