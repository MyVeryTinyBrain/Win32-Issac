#pragma once
#ifndef __ItemBomb_h__
#define __ItemBomb_h__

#include "Item.h"

class ItemBomb : public Item
{
	virtual void SetSprite(Sprite** pSprite) override;
	virtual bool OnPlayerCollision(Player* player) override;
	virtual void OnUpdate() override;
};

#endif
