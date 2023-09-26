#pragma once
#ifndef __Room1x1_h__
#define __Room1x1_h__

#include "Room.h"

class Door;

class Room1x1 : public Room
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;

private:
	Door* m_leftDoor = nullptr;
	Door* m_topDoor = nullptr;
	Door* m_rightDoor = nullptr;
	Door* m_bottomDoor = nullptr;

private:
	virtual void SetCxCy(size_t* pCX, size_t* pCY) override;

public:
	void InitGenerateRoom(const TCHAR* bmpKey);
	void InitGenerateBloodRoom();
	void InitGenerateDoor(const TCHAR* leftBmpKey, const TCHAR* topBmpKey, const TCHAR* rightBmpKey, const TCHAR* bottomBmpKey);

	Door* leftDoor() const;
	Door* topDoor() const;
	Door* rightDoor() const;
	Door* bottomDoor() const;

	virtual void SetDoorsUseState(const bool& canUse) override;
	virtual void SetDoorsOpen(const bool& open) override;
};

#endif
