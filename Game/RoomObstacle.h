#pragma once
#ifndef __RoomObstacle_h__
#define __RoomObstacle_h__

class RoomObstacle : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

protected:
	virtual void SetDestructible(bool* pDestructible) = 0;
	virtual void SetSprites(Sprite** pDefault, Sprite** pDestroyed) = 0;
	virtual void OnDestroyObstacle() = 0;

private:
	size_t m_ix = 0;
	size_t m_iy = 0;

	Body2D* m_body = nullptr;
	RectCollider2D* m_collider = nullptr;
	SpriteRenderer* m_renderer = nullptr;

	Sprite* m_defaultSprite = nullptr;
	Sprite* m_destroyedSprite = nullptr;
	bool m_isDestructible = false;
	bool m_destroyed = false;

public:
	void DestroyObstacle();

	Vector2 GetIndex() const;
	void InitSetIndex(const size_t& ix, const size_t& iy);

	Delegate<void, RoomObstacle*> OnObstacleDestroyedCallback;
};

#endif
