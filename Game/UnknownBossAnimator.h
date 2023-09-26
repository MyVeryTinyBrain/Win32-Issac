#pragma once
#ifndef __UnknownBossAnimator_h__
#define __UnknownBossAnimator_h__

class UnknownBossAnimator : public Animator
{
public:
	enum class State
	{
		LIE = 0, STAND, WING
	};
private:
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_lie_idle;
	Animation* m_lie_pop;

	Animation* m_stand_idle;
	Animation* m_stand_crouch_pop;

	Animation* m_wing_idle;
	Animation* m_wing_pop;
	Animation* m_wing_up;
	Animation* m_wing_down;

	State m_state;

public:
	void SetState(const State& state);
	void SetPop();
	void SetUpOnWing();
	bool isPopping();

	Delegate<void> OnUpAnimated;
	Delegate<void> OnPopAnimated;
};

#endif
