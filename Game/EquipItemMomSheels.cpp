#include "stdafx.h"
#include "EquipItemMomSheels.h"
#include "Player.h"

void EquipItemMomSheels::GiveAbilityToPlayer(Player* player)
{
	player->setSpeed(player->speed() + 50);
}

EquipItemMomSheels::EquipItemMomSheels() : EquipItem(SpriteManager::Find(TEXT("collectibles_030_momsheels")))
{
}
