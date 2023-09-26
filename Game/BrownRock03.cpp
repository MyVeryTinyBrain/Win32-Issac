#include "stdafx.h"
#include "BrownRock03.h"

void BrownRock03::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void BrownRock03::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/brown02"));
	*pDestroyed = SpriteManager::Find(TEXT("rocks_basement/brown_destroyed"));
}

void BrownRock03::OnDestroyObstacle()
{
}
