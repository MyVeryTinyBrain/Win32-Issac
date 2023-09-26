#pragma once
#ifndef __EquipItemBrimston_h__
#define __EquipItemBrimston_h__

#include "EquipItem.h"

class EquipItemBrimston : public EquipItem
{
	virtual void GiveAbilityToPlayer(Player* player) override;

public:
	EquipItemBrimston();
};

#endif
