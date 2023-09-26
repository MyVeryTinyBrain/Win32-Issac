#pragma once

class Explosion : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	void OnHit(Collider2D* collider);

private:
	float m_destroyDelay;
	Sprite* m_bombRadSprite;
	Sprite* m_anim[12];
	SpriteRenderer* m_animRenderer;
	SpriteRenderer* m_bombRadRenderer;
	Body2D* m_body;
	Collider2D* m_hit;
	float m_endTime;
	float m_accumulated;
	bool m_exploded;
	float m_destroyCount;
};

