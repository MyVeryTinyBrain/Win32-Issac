#include "stdafx.h"
#include "BrownRock01.h"

void BrownRock01::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void BrownRock01::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/brown01"));
	*pDestroyed = SpriteManager::Find(TEXT("rocks_basement/brown_destroyed"));
}

void BrownRock01::OnDestroyObstacle()
{
}
