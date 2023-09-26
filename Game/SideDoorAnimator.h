#pragma once
#ifndef __DoorSideAnimator_h__
#define __DoorSideAnimator_h__

class DoorSideAnimator : public Animator
{
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_openAnimation;
	Animation* m_closeAnimation;

public:
	void InitSetDoorSprite(Sprite* door1, Sprite* door2, Sprite* door3, Sprite* door4);
	void PlayOpen();
	void PlayClose();

	Delegate<void> OnOpened;
	Delegate<void> OnClosed;
};

#endif