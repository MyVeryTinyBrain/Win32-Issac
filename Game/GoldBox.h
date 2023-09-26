#pragma once
#ifndef __GoldBox_h__
#define __GoldBox_h__

#include "EquipItemPlacer.h"

class GoldBox : public EquipItemPlacer
{
	virtual void SetCanGetItem(bool* pCanGetItem) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pChanged) override;
	virtual void SetCollider(Collider2D** pCollider) override;
	virtual void SetBody2DProperty(Body2D* body) override;
	virtual void LateAwake() override;
	virtual void Update() override;
	virtual void OnPlayerCollision(Player* player) override;
	virtual void GiveAbilityToPlayer(Player* player) override;

private:
	float m_elapsed;
};

#endif
