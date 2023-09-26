#pragma once
#ifndef __BlackFly_h__
#define __BlackFly_h__

#include "Monster.h"

class BlackFlyAnimator;

class BlackFly : public Monster
{
	virtual void setSize(Size* pSize) override;
	virtual void setInitHP(float* pHP) override;
	virtual void setCollider(Collider2D** pCollider, Collider2D** pHitTrigger) override;
	virtual void setRenderers(std::vector<SpriteRenderer*>* pRenderers) override;
	virtual void LateAwake() override;
	virtual void OnCollision(Collider2D* collider) override;
	virtual void OnTrigger(Collider2D* collider) override;
	virtual void OnDamaged() override;
	virtual void OnDead() override;

public:
	virtual Vector2 center() const override;

	virtual void Update() override;

private:
	void OnDeadAnimated();

private:
	GameObject* m_spriteObj{};
	GameObject* m_shadowObj{};
	BlackFlyAnimator* m_animator{};
};

#endif
