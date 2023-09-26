#pragma once
#ifndef __EquipItemMomSheels_h__
#define __EquipItemMomSheels_h__

#include "EquipItem.h"

class EquipItemMomSheels : public EquipItem
{
	virtual void GiveAbilityToPlayer(Player* player) override;

public:
	EquipItemMomSheels();
};

#endif
