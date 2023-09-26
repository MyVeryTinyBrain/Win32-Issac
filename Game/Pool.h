#pragma once
#ifndef __Pool_h__
#define __Pool_h__

class Pool : public Behavior
{
public:
	enum class Type
	{
		Blood, Water
	};
	enum class Size
	{
		Small, Regular, Large
	};

private:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	SpriteRenderer* m_renderer;
	bool m_do;
	float m_destroyDelay;
	float m_destroyCounter;

private:
	Sprite* FindSprite(const Type& type, const Size& size);

public:
	void InitGenerate(const Type& type, const Size& size);
};

#endif
