#include "stdafx.h"
#include "EquipItemHeart.h"
#include "Player.h"

void EquipItemHeart::GiveAbilityToPlayer(Player* player)
{
	player->setMaxHP(player->maxHP() + 1);
}

EquipItemHeart::EquipItemHeart() : EquipItem(SpriteManager::Find(TEXT("collectibles_015_heart")))
{
}
