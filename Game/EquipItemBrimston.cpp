#include "stdafx.h"
#include "EquipItemBrimston.h"
#include "Player.h"

void EquipItemBrimston::GiveAbilityToPlayer(Player* player)
{
	player->setToBrimston(true);
}

EquipItemBrimston::EquipItemBrimston() : EquipItem(SpriteManager::Find(TEXT("collectibles_118_brimstone")))
{
}
