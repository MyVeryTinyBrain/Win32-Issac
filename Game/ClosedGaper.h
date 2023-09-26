#pragma once
#ifndef __ClosedGaper_h__
#define __ClosedGaper_h__

#include "Monster.h"

class PlayerBodyAnimator;

class ClosedGaper : public Monster
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
	virtual void LateUpdate() override;

private:
	GameObject* m_colObj = nullptr;
	GameObject* m_hitObj = nullptr;
	GameObject* m_spriteParent = nullptr;
	GameObject* m_headObj = nullptr;
	GameObject* m_bodyObj = nullptr;
	GameObject* m_shadowObj = nullptr;
	PlayerBodyAnimator* m_bodyAnimator = nullptr;
};

#endif
