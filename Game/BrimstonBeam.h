#pragma once
#ifndef __BrimstonBeam_h__
#define __BrimstonBeam_h__

class BrimstonBeam : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Sprite* m_sprites[4];
	SpriteRenderer* m_renderer;
	float m_elasped;
	float m_width;

	Body2D* m_body;
	RectCollider2D* m_hitTrigger;
	unsigned char m_targetLayer;
	float m_damage;

	float m_triggerToggleCounter;

public:
	void SetTwoPoints(const Vector2& a, const Vector2& b);
	void SetWidth(const float& Width);
	void SetOrder(const int& order);
	void setTargetLayer(const unsigned char& TargetLayer);
	void setDamage(const float& damage);

private:
	void OnTrigger(Collider2D* collider);
};

#endif
