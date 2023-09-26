#pragma once
#ifndef __EquipItemHeart_h__
#define __EquipItemHeart_h__

#include "EquipItem.h"

class EquipItemHeart : public EquipItem
{
	virtual void GiveAbilityToPlayer(Player* player) override;

public:
	EquipItemHeart();
};

#endif
