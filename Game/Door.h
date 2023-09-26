#pragma once
#ifndef __Door_h__
#define __Door_h__

class Room;

class KeyAnimator;
class DoorSideAnimator;
class DoorPoppingAnimator;

class Door : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Room* m_room;

	float m_height;
	float m_width;
	Body2D* m_body;
	RectCollider2D* m_trigger;
	LineCollider2D* m_entranceCollider;
	bool m_locked;
	bool m_opened;
	
	KeyAnimator* m_unlockAnimator;
	DoorSideAnimator* m_leftDoorAnimator;
	DoorSideAnimator* m_rightDoorAnimator;
	DoorSideAnimator* m_rightLockedDoorAnimator;
	DoorPoppingAnimator* m_poppingAnimator;

	Vector2 m_exitDirection;
	Door* m_exit;
	bool m_canUse;

public:
	const float& height() const;
	const float& width() const;

	void Lock();
	void Unlock();
	const bool& isLocked() const;
	void Open();
	void Close();
	const bool& isOpened() const;

	Door* exitDoor() const;
	void Connect(Door* exitDoor);
	void SetCanUse(const bool& canUse);

	void InitGenerate(const TCHAR* bmpKey);
	void InitSetRoom(Room* room);
	Room* GetRoom() const;

private:
	void OnPoppingAnimated();
	void OnUnlockAnimated();
	void OnTrigged(Collider2D* collider);
	void OnCollision(Collider2D* collider);
};

#endif
