#pragma once
#ifndef __EquipItemMomLipstick_h__
#define __EquipItemMomLipstick_h__

#include "EquipItem.h"

class EquipItemMomLipstick : public EquipItem
{
	virtual void GiveAbilityToPlayer(Player* player) override;

public:
	EquipItemMomLipstick();
};

#endif