#pragma once
#ifndef __UICollectibles_h__
#define __UICollectibles_h__

class UICollectibles : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Sprite* m_coin;
	Sprite* m_bomb;
	Sprite* m_key;

	size_t m_prevCoin;
	size_t m_prevBomb;
	size_t m_prevKey;

	SpriteRenderer* m_coinSpriteRenderer;
	SpriteRenderer* m_bombSpriteRenderer;
	SpriteRenderer* m_keySpriteRenderer;

	TextRenderer* m_coinCountRenderer;
	TextRenderer* m_bombCountRenderer;
	TextRenderer* m_keyCountRenderer;
};

#endif
