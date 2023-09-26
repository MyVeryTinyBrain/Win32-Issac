#pragma once
#ifndef __BlueRock_h__
#define __BlueRock_h__

#include "RoomObstacle.h"

class BlueRock : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
