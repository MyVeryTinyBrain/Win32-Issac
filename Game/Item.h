#pragma once
#ifndef __Item_h__
#define __Item_h__

class Player;

class Item : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Body2D* m_body;
	CircleCollider2D* m_collider;
	SpriteRenderer* m_renderer;

	float m_elapsed;
	bool m_animated;

public:
	Body2D* body() const;

private:
	void OnCollision(Collider2D* collider);

protected:
	virtual void SetSprite(Sprite** pSprite) = 0;
	virtual bool OnPlayerCollision(Player* player) = 0;
	virtual void OnUpdate() = 0;
};

#endif
