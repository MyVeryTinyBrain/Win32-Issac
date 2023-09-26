#pragma once
#ifndef __ItemRedHeart_h__
#define __ItemRedHeart_h__

#include "Item.h"

class ItemRedHeart : public Item
{
	virtual void SetSprite(Sprite** pSprite) override;
	virtual bool OnPlayerCollision(Player* player) override;
	virtual void OnUpdate() override;
};

#endif
