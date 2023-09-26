#include "stdafx.h"
#include "BrownBombRock.h"
#include "Explosion.h"

void BrownBombRock::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void BrownBombRock::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/brown_bomb"));
	*pDestroyed = SpriteManager::Find(TEXT("rocks_basement/brown_destroyed"));
}

void BrownBombRock::OnDestroyObstacle()
{
	GameObject* obj = new GameObject(this->transform()->position(), this->transform());
	obj->AddComponent<Explosion>();
}
