#pragma once
#ifndef __Camerawork_h__
#define __Camerawork_h__

class Camerawork : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	Transform* m_target = nullptr;
	
	bool m_useBorder = false;
	float m_borderLeft = 0;
	float m_borderTop = 0;
	float m_borderRight = 0;
	float m_borderBottom = 0;

	bool m_borderLerp = false;
	float m_borderLerpPrevLeft = 0;
	float m_borderLerpPrevTop = 0;
	float m_borderLerpPrevRight = 0;
	float m_borderLerpPrevBottom = 0;
	float m_borderLerpLeft = 0;
	float m_borderLerpTop = 0;
	float m_borderLerpRight = 0;
	float m_borderLerpBottom = 0;
	float m_borderLerpAccumulated = 0;
	float m_borderLerpEndTime = 0;

public:
	void SetTarget(Transform* target);
	void SetUseBorder(const bool& enable);
	void SetBorder(const float& left, const float& top, const float& right, const float& bottom);
	void LerpBorder(const float& left, const float& top, const float& right, const float& bottom, const float& t);

private:
	float Lerp(const float& start, const float& end, const float& t);
};

#endif
