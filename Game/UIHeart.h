#pragma once
#ifndef __UIHeart_h__
#define __UIHeart_h__

class UIHeart : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Sprite* m_redFull;
	Sprite* m_redHalf;
	Sprite* m_redEmpty;
	Sprite* m_blueFull;
	Sprite* m_blueHalf;

	float m_lastRedMax;
	float m_lastRed;
	float m_lastBlue;

	std::vector<SpriteRenderer*> m_icons;

private:
	void PlaceHearts();
};

#endif
