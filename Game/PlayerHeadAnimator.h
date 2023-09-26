#pragma once
#ifndef __PlayerHeadAnimator_h__
#define __PlayerHeadAnimator_h__

class PlayerHeadAnimator : public Animator
{
public:
	enum class HeadState
	{
		IDLE, 
		CLOSE,
		CHARGING, CHARGED, FIRE
	};
	enum class HeadDirection
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
	Animation* m_forward_default;
	Animation* m_forward_close;
	Animation* m_backward_default;
	Animation* m_backward_close;
	Animation* m_right_default;
	Animation* m_right_close;
	Animation* m_gotItem;

	Animation* m_brimston_forward_default;
	Animation* m_brimston_forward_fire;
	Animation* m_brimston_backward_default;
	Animation* m_brimston_backward_fire;
	Animation* m_brimston_right_default;
	Animation* m_brimston_right_fire;
	Animation* m_brimston_forward_charging;
	Animation* m_brimston_backward_charging;
	Animation* m_brimston_right_charging;
	Animation* m_brimston_forward_charged;
	Animation* m_brimston_backward_charged;
	Animation* m_brimston_right_charged;

	HeadDirection m_direction;
	HeadState m_state;
	bool m_isBrimston;

public:
	void SetIdle(const HeadDirection& direction);
	void SetClose(const HeadDirection& direction);
	void PlayGotItem();
	void SetChargeSpeed(const float& speed);
	void SetFireSpeed(const float& speed);
	void Charge();
	bool isCharged() const;
	bool StopChargeOrFire();
	void setIsBrimston(const bool& value);
	void setDirection(const HeadDirection& direction);
	const HeadDirection& direction() const;

private:
	bool isPlayingClose();
	bool isPlayingCharge();
};

#endif
