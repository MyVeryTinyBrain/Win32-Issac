#pragma once
#ifndef __BlackBowl1_h__
#define __BlackBowl1_h__

#include "RoomObstacle.h"

class BlackBowl1 : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
