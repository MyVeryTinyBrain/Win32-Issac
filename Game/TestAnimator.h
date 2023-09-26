#pragma once
#ifndef __TestAnimator_h__
#define __TestAnimator_h__

class Sprite;
class SpriteRenderer;

class TestAnimator : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	SpriteRenderer* m_renderer;
	std::vector<Sprite*> m_sprites;
	float m_interval;
	float m_accumulated;
	size_t m_idx;

public:
	void AddSprite(Sprite* sprite);
};

#endif
