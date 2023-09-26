#pragma once
#ifndef __BlackBowl2_h__
#define __BlackBowl2_h__

#include "RoomObstacle.h"

class BlackBowl2 : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
