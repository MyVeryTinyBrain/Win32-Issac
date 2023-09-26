#include "stdafx.h"
#include "BrownRock02.h"

void BrownRock02::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void BrownRock02::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/brown03"));
	*pDestroyed = SpriteManager::Find(TEXT("rocks_basement/brown_destroyed"));
}

void BrownRock02::OnDestroyObstacle()
{
}
