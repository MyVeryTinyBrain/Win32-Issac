#pragma once
#ifndef __ItemBlueHeart_h__
#define __ItemBlueHeart_h__

#include "Item.h"

class ItemBlueHeart : public Item
{
	virtual void SetSprite(Sprite** pSprite) override;
	virtual bool OnPlayerCollision(Player* player) override;
	virtual void OnUpdate() override;
};

#endif