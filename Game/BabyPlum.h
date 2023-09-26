#pragma once
#ifndef __BabyPlum_h__
#define __BabyPlum_h__

#include "Monster.h"

class BabyPlumAnimator;
class Projectile;
class Brimston;

class BabyPlum : public Monster
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
	GameObject* m_objParent;
	BabyPlumAnimator* m_animator;
	GameObject* m_hitObj;
	CircleCollider2D* m_hit;
	GameObject* m_rendererObj;
	SpriteRenderer* m_renderer;

	GameObject* m_shadowObj;

	Vector2 m_targetPos;
	float m_targetCaptureCounter;
	float m_targetCaptureDelay;

	float m_attackDelay;
	float m_attackCounter;
	size_t m_spinCount;
	size_t m_stampCount;
	size_t m_reflectCount;
	size_t m_stamp2Count;

	float m_lastStampShootAngle;

	Vector2 m_spinDir;
	float m_spinShootCounter;
	float m_lastSpinShootAngle;

	float m_reflectShootCounter;
	float m_reflectCounter;

private:
	void OnAwakeAnimated();
	void OnRelfectReadyAnimated();
	void OnStamped();
	void OnStampAnimated();
	void OnSpinAnimated();
	void OnStamped2();
	void OnDefeatAnimated();

	Projectile* CreateBullet(const float& speed, const float& range, const int& damage, const float& radian, const Vector2& position);
	Brimston* CreateBrimston();
};

#endif