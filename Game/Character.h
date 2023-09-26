#pragma once
#ifndef __Character_h__
#define __Character_h__

class Character : public Behavior
{
public:
	enum class Size
	{
		Small, Regular, Large
	};

private:
	virtual void Awake() override;

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

protected:
	virtual void setSize(Size* pSize) = 0;
	virtual void setInitHP(float* pHP) = 0;
	virtual void setCollider(Collider2D** pCollider, Collider2D** pHitTrigger) = 0;
	virtual void setRenderers(std::vector<SpriteRenderer*>* pRenderers) = 0;
	virtual void LateAwake() = 0;
	virtual void OnCollision(Collider2D* collider) = 0;
	virtual void OnTrigger(Collider2D* collider) = 0;
	virtual void OnDamaged() = 0;
	virtual void OnDead() = 0;
	virtual bool ApplyDamage(float* pDamage);

public:
	virtual Vector2 center() const = 0;

private:
	float m_hp{};
	float m_maxHP{};
	bool m_isDead{};

	float m_damagedEffectTime{};

	Size m_size{};

protected:
	Body2D* m_body{};
	Collider2D* m_collider{};
	Collider2D* m_hitTrigger{};
	std::vector<SpriteRenderer*> m_renderers{};
	float m_speed{};

public:
	Body2D* body() const;

	const float& HP() const;
	const float& maxHP() const;
	void setMaxHP(const float& MaxHP);
	void TakeDamage(float Damage);
	void setHP(const float& HP);
	const bool& isDead() const;
	const float& speed() const;
	void setSpeed(const float& value);

	const Size& size() const;

protected:
	void SetDamagedEffectTime(const float& time);

public:
	Delegate<void, Character*> OnDeadCallback;
};

#endif
