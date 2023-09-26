#pragma once
#ifndef __KeyAnimator_h__
#define __KeyAnimator_h__

class KeyAnimator : public Animator
{
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_keyAnimation;

public:
	void Play();
	bool isPlayingUnlockAnimation() const;

	Delegate<void> OnAnimated;
};

#endif
