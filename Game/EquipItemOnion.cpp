#include "stdafx.h"
#include "EquipItemOnion.h"
#include "Player.h"

void EquipItemOnion::GiveAbilityToPlayer(Player* player)
{
	player->setShootDelay(player->shootDelay() - 0.05f);
}

EquipItemOnion::EquipItemOnion() : EquipItem(SpriteManager::Find(TEXT("collectibles_001_thesadonion")))
{
}
