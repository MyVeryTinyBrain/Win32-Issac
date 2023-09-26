#pragma once
#ifndef __Coin_h__
#define __Coin_h__

#include "Item.h"

class ItemCoin : public Item
{
	virtual void SetSprite(Sprite** pSprite) override;
	virtual bool OnPlayerCollision(Player* player) override;
	virtual void OnUpdate() override;
};

#endif
