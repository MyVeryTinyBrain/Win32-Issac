#pragma once
#ifndef __DoorPoppingAnimator_h__
#define __DoorPoppingAnimator_h__

class DoorPoppingAnimator : public Animator
{
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_animation;

public:
	void Play();
	
	Delegate<void> OnAnimated;
};

#endif
