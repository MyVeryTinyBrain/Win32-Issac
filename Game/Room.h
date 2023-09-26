#pragma once
#ifndef __Room_h__
#define __Room_h__

class RoomObstacle;
class Monster;
class Character;
class Item;
class EquipItemPlacer;

class Room : public Behavior
{
protected:
	virtual void Awake() override;
	virtual void Start() override = 0;
	virtual void Update() override;
	virtual void LateUpdate() override = 0;
	virtual void OnEnable() override = 0;
	virtual void OnDisable() override = 0;
	virtual void OnDestroy() override;

public:
	const static float FloorWidth;
	const static float FloorHeight;
	const static float CornerLength;
	const static float FloorGridLength;

private:
	float m_disableEndTime = 0;
	float m_disableCountTime = 0;
	bool m_disableCounting = false;

	size_t m_cx = 0;
	size_t m_cy = 0;
	RoomObstacle** m_arrRoomObstacles = nullptr;
	std::list<Monster*> m_monsters;

	GameObject* m_enterTriggerObj = nullptr;
	Body2D* m_body = nullptr;
	RectCollider2D* m_EnterTrigger = nullptr;

	std::list<Item*> m_items;

	std::list<EquipItemPlacer*> m_equipItems;

public:
	void RoomObjEnable();
	void RoomObjDisableWithTime(const float& time);

	virtual void SetCxCy(size_t* pCX, size_t* pCY) = 0;
	virtual void SetDoorsUseState(const bool& canUse) = 0;
	virtual void SetDoorsOpen(const bool& open) = 0;

	float floorHorizontalLength() const;
	float floorVerticalLength() const;
	float roomHorizontalLength() const;
	float roomVerticalLength() const;

	float floorLeft() const;
	float floorTop() const;
	float floorRight() const;
	float floorBottom() const;
	float roomLeft() const;
	float roomTop() const;
	float roomRight() const;
	float roomBottom() const;

	size_t floorGridCountX() const;
	size_t floorGridCountY() const;

	Vector2 floorLeftTop() const;
	Vector2 floorRightTop() const;
	Vector2 floorRightBottom() const;
	Vector2 floorLeftBottom() const;
	Vector2 roomLeftTop() const;
	Vector2 roomRightTop() const;
	Vector2 roomRightBottom() const;
	Vector2 roomLeftBottom() const;
	const Vector2& center() const;

	// Returns world position by index of room
	Vector2 IndexToCoordOnFloor(const size_t& x, const size_t& y) const;
	// Returns index of room by world position
	Vector2 CoordToIndexOnFloor(const Vector2& coord) const;
	static Vector2 IndexToRoomLeftTopCoord(const int& x, const int& y);
	static Vector2 RoomLeftTopCoordToIndex(const Vector2& roomCoord);
	void SetRoomLeftTop(const Vector2& roomLeftTop);

	void AddObstacle(const size_t& x, const size_t& y, RoomObstacle* obstacle);
	void AddMonster(const size_t& x, const size_t& y, Monster* monster);
	void AddMonsterAtCenter(Monster* monster);
	void AddItem(const size_t& x, const size_t& y, Item* item);
	void AddItemAtCenter(Item* item);
	void AddEquipItemPlacer(const size_t& x, const size_t& y, EquipItemPlacer* placer);
	void AddEquipItemPlacerAtCenter(EquipItemPlacer* placer);

	Vector2 GetEmptyGridPosition() const;

private:
	void OnPlayerEnter(Collider2D* collider);
	void OnMonsterDead(Character* monster);
	void OnObstacleDestroyed(RoomObstacle* obstacle);
};

#endif
