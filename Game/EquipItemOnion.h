#pragma once
#ifndef __EquipItemOnion_h__
#define __EquipItemOnion_h__

#include "EquipItem.h"

class EquipItemOnion : public EquipItem
{
	virtual void GiveAbilityToPlayer(Player* player) override;

public:
	EquipItemOnion();
};

#endif
