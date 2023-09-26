#pragma once
#ifndef __SmallBloodPoofAnimator_h__
#define __SmallBloodPoofAnimator_h__

class SmallBloodPoofAnimator : public Animator
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
