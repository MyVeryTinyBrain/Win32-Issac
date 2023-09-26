#pragma once
#ifndef __WhiteBowl_h__
#define __WhiteBowl_h__

#include "RoomObstacle.h"

class WhiteBowl : public RoomObstacle
{
	virtual void SetDestructible(bool* pDestructible) override;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) override;
	virtual void OnDestroyObstacle() override;
};

#endif
