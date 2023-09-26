#include "stdafx.h"
#include "EquipItemMartyr.h"
#include "Player.h"

void EquipItemMartyr::GiveAbilityToPlayer(Player* player)
{
	player->setDamage(player->damage() + 1);
}

EquipItemMartyr::EquipItemMartyr() : EquipItem(SpriteManager::Find(TEXT("collectibles_007_bloodofthemartyr")))
{
}
