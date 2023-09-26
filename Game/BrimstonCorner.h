#pragma once
#ifndef __BrimstonCorner_h__
#define __BrimstonCorner_h__

class BrimstonCorner : public Behavior
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

public:
	void SetRadius(const float& radius);
	void SetOrder(const int& order);
};

#endif
