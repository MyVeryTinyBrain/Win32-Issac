#pragma once
#ifndef __Player_h__
#define __Player_h__

#include "Character.h"

class PlayerHeadAnimator;
class PlayerBodyAnimator;
class Brimston;

class Player : public Character
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
	virtual bool ApplyDamage(float* pDamage) override;

public:
	virtual Vector2 center() const override;

	virtual void Update() override;
	virtual void LateUpdate() override;

private:
	float m_subHP;

	GameObject* m_spriteParent;
	GameObject* m_playerHeadObj;
	GameObject* m_playerBodyObj;
	PlayerHeadAnimator* m_headAnimator;
	PlayerBodyAnimator* m_bodyAnimator;
	float m_invisibleTime;

	float m_projShootCounter;
	float m_projDelay;
	float m_damage;
	float m_range;
	float m_projSpeed;

	size_t m_bomb;
	size_t m_coin;
	size_t m_key;

	GameObject* m_gotItemObj;
	SpriteRenderer* m_gotItemRenderer;

	bool m_isBrimston;

public:
	const Vector2& headPosition() const;
	const float& subHP() const;
	void SetSubHP(const float& SubHP);
	const size_t& bomb() const;
	void setBomb(const size_t& Bomb);
	const size_t& coin() const;
	void setCoin(const size_t& Coin);
	const size_t& key() const;
	void setKey(const size_t& Key);

	const float& shootDelay() const;
	void setShootDelay(const float& value);
	const float& damage() const;
	void setDamage(const float& value);
	const float& range() const;
	void setRange(const float& value);
	const float& projectileSpeed() const;
	void setProjectileSpeed(const float& value);

	void GotItem(Sprite* itemSprite);
	void setToBrimston(const bool& value);

private:
	static Player* g_instnace;

public:
	static Player* instance();
};

#endif
