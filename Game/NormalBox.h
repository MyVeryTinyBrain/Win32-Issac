#pragma once
#ifndef __NormalBox_h__
#define __NormalBox_h__

#include "EquipItemPlacer.h"

class NormalBox : public EquipItemPlacer
{
	virtual void SetCanGetItem(bool* pCanChanged) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pChanged) override;
	virtual void SetCollider(Collider2D** pCollider) override;
	virtual void SetBody2DProperty(Body2D* body) override;
	virtual void LateAwake() override;
	virtual void Update() override;
	virtual void OnPlayerCollision(Player* player) override;
	virtual void GiveAbilityToPlayer(Player* player) override;
};

#endif
