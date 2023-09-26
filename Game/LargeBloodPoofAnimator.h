#pragma once
#ifndef __LargeBloodPoofAnimator_h__
#define __LargeBloodPoofAnimator_h__

class LargeBloodPoofAnimator : public Animator
{
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_anim;
};

#endif
