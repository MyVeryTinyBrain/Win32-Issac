#pragma once
#ifndef __UnknownBoss_h__
#define __UnknownBoss_h__

#include "Monster.h"

class UnknownBossAnimator;

class UnknownBoss : public Monster
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
	virtual void Start() override;

public:
	virtual Vector2 center() const override;
	virtual void Update() override;

private:
	UnknownBossAnimator* m_animator;

	GameObject* m_hitObj;
	RectCollider2D* m_hit;
	
	GameObject* m_rendererObj;
	SpriteRenderer* m_renderer;

	int m_state;

	float m_skillDelay;
	float m_skillCounter;

private:
	void SetState(const int& state);
	void OnUpAnimated();
	void OnPopAnimated();
	void OnStateChange();

	float m_shootToPlayerCounter;
	float m_shootToPlayerNextCounter;
	void ShootToPlayer();

	void MakeProjectilToPlayer();
};

#endif
