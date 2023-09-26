#include "stdafx.h"
#include "BlueRock.h"
#include "ItemBlueHeart.h"

void BlueRock::SetDestructible(bool* pDestructible)
{
	*pDestructible = true;
}

void BlueRock::SetSprites(Sprite** pDefault, Sprite** pDestroyed)
{
	*pDefault = SpriteManager::Find(TEXT("rocks_basement/blue"));
	*pDestroyed = SpriteManager::Find(TEXT("rocks_basement/blue_destroyed"));
}

void BlueRock::OnDestroyObstacle()
{
	GameObject* obj = new GameObject(this->transform()->position(), this->transform());
	obj->AddComponent<ItemBlueHeart>();
}
