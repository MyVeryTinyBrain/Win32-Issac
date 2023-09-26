#pragma once
#ifndef __Body2D_h__
#define __Body2D_h__

#include "Behavior.h"

class Collider2D;

class Body2D : public Behavior
{
	friend class Physics2D;

private:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Vector2 m_velcoity;
	float m_mass;
	float m_invMass;
	float m_elasticity;
	float m_friction;
	// �ش� �ٵ� ���� �ݶ��̴��� �浹�� �޴� ��츸 ����մϴ�.
	// ���� �浹�� �� �ٵ� ��� �� �÷��װ� ���� �ִٸ� �浹�� ������� �ʽ��ϴ�.
	bool m_justCollider;
	std::vector<Collider2D*> m_colliders;

public:
	void ApplyVelocity();
	void UpdateColliderVertices();

	const Vector2& velocity() const;
	void setVelocity(const Vector2& velocity);
	float mass() const;
	void setMass(const float& mass);
	float invMass() const;
	const float& elasticity() const;
	void setElasticity(const float& elasticity);
	const float& friction() const;
	void setFriction(const float& friction);

	const bool& justCollider() const;
	void setJustCollider(const bool& enable);

	size_t colliderCount() const;
	Collider2D* collider2D(const size_t& index) const;

	void RegisterCollider(Collider2D* collider);
	void DeregisterCollider(Collider2D* collider);
	bool HasCollider(Collider2D* collider) const;

	void AddImpulseToSpeed(const Vector2& direction, const float& speed);
	void AddImpulse(const Vector2& impulse);

private:
	void OnRegisteredColliderDestroy(Object* obj);

private:
	static std::vector<Body2D*> g_bodies;
};

#endif
