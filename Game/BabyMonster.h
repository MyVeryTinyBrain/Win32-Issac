#pragma once
#ifndef __BabyMonster_h__
#define __BabyMonster_h__

#include "Monster.h"

class BabyMonsterAnimator;

class BabyMonster : public Monster
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
	GameObject* m_spriteObj{};
	GameObject* m_shadowObj{};
	BabyMonsterAnimator* m_animator{};

	Vector2 m_teleportTarget{};
	size_t m_teleportCounterInit{};
	float m_attackDelay{};
	size_t m_teleportCounter{};
	float m_attackCounter{};

private:
	void OnTeleportAnimated();
	void OnAttackAnimated();
};

#endif
