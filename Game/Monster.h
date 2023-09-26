#pragma once
#ifndef __Monster_h__
#define __Monster_h__

#include "Character.h"

class Room;

class Monster : public Character
{
protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

protected:
	virtual void setSize(Size* pSize) override = 0;
	virtual void setInitHP(float* pHP) override = 0;
	virtual void setCollider(Collider2D** pCollider, Collider2D** pHitTrigger) override = 0;
	virtual void setRenderers(std::vector<SpriteRenderer*>* pRenderers) override = 0;
	virtual void LateAwake() override = 0;
	virtual void OnCollision(Collider2D* collider) override = 0;
	virtual void OnTrigger(Collider2D* collider) override = 0;
	virtual void OnDamaged() override = 0;
	virtual void OnDead() override = 0;

public:
	virtual Vector2 center() const = 0;

protected:
	Room* m_room{};

public:
	void SetRoom(Room* room);
	Room* GetRoom() const;
};

#endif
