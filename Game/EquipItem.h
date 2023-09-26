#pragma once
#ifndef __EquipItem_h__
#define __EquipItem_h__

class Player;

class EquipItem
{
	Sprite* m_sprite;

public:
	EquipItem(Sprite* Sprite);

public:
	virtual void GiveAbilityToPlayer(Player* player) = 0;
	Sprite* sprite() const;
};

#endif
