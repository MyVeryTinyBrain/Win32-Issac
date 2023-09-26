#pragma once
#ifndef __ItemKey_h__
#define __ItemKey_h__

#include "Item.h"

class ItemKey : public Item
{
	virtual void SetSprite(Sprite** pSprite) override;
	virtual bool OnPlayerCollision(Player* player) override;
	virtual void OnUpdate() override;
};

#endif
