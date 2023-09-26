#pragma once
#ifndef __PlayerBodyAnimator_h__
#define __PlayerBodyAnimator_h__

class PlayerBodyAnimator : public Animator
{
public:
	enum class BodyState
	{
		IDLE, WALK, RAISEUP
	};
	enum class BodyDirection
	{
		LEFT,
		BACKWARD,
		RIGHT,
		FORWARD,
	};

private:
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_forward_idle;
	Animation* m_forward_walk;
	Animation* m_right_walk;
	Animation* m_gotItem;

	Animation* m_brimston_forward_idle;
	Animation* m_brimston_forward_walk;
	Animation* m_brimston_right_walk;

	BodyDirection m_direction;
	BodyState m_state;
	bool m_isBrimston;

public:
	void SetDirection(const BodyDirection& direction);
	void SetState(const BodyState& state);
	void PlayGotItem();
	bool isPlayingGotItem();
	void setIsBrimston(const bool& value);
};

#endif
