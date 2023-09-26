#pragma once
#ifndef __EquipItemMartyr_h__
#define __EquipItemMartyr_h__

#include "EquipItem.h"

class EquipItemMartyr : public EquipItem
{
	virtual void GiveAbilityToPlayer(Player* player) override;

public:
	EquipItemMartyr();
};

#endif
