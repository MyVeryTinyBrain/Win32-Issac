#pragma once
#ifndef __Projectile_h__
#define __Projectile_h__

class ProjectileAnimator;
class Pool;

class Projectile : public Behavior
{
public:
	enum class Type
	{
		Normal, Blood,
	};

private:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Type m_type;
	int m_damage{};
	Vector2 m_dir{};
	float m_speed{};
	float m_range{};
	unsigned char m_targetLayer{};

	float m_accumulatedDistance{};
	bool m_doStop{};

	GameObject* m_projectileObj{};
	GameObject* m_shadowObj{};
	CircleCollider2D* m_hitTrigger{};
	ProjectileAnimator* m_animator{};

public:
	void InitSetType(const Type& type);
	void InitSetDamage(const int& damage);
	void InitSetSpeed(const float& speed);
	void InitSetDirection(const Vector2& direction);
	void InitSetRange(const float& range);
	void InitSetTargetLayer(const unsigned char& targetLayer);

private:
	void OnDestroyAnimated();
	void OnTrigger(Collider2D* collider);
	Pool* CreatePool();
};

#endif
