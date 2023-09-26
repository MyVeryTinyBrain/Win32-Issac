#pragma once
#ifndef __BabyMonsterAnimator_h__
#define __BabyMonsterAnimator_h__

class BabyMonsterAnimator : public Animator
{
	virtual void OnAwake() override;
	virtual void OnSetDefaultAnimation(Animation** defaultAnimtiaon) override;
	virtual void OnUpdate(Animation* currentAnimation, const float& Elapsed) override;
	virtual void OnAnimationChanged(Animation* prev, Animation* next) override;
	virtual void OnPrevDestroy() override;

private:
	Animation* m_default;
	Animation* m_attack;
	Animation* m_teleport;

public:
	void PlayAttack();
	void PlayTeleport();

	Delegate<void> OnAttackAnimated;
	Delegate<void> OnTeleportAnimated;

	bool isPlayingAttack();
	bool isPlayingTeleport();
};

#endif
