#pragma once
#ifndef __Brimston_h__
#define __Brimston_h__

class BrimstonCorner;
class BrimstonBeam;
class BrimstonHit;

class Brimston : public Behavior
{
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

private:
	size_t m_vertexCount;
	float m_width;

	Vector2 m_dir;
	float m_dirAngle;
	float m_targetDirAngle;

	Vector2 m_beg;
	Vector2 m_mid;
	Vector2 m_end;

	Vector2 m_targetEnd;
	Vector2 m_targetMid;
	Collider2D* m_lastHitCollider;
	Vector2 m_lastHitPoint;

	GameObject* m_lineRendererObj;
	LineRenderer* m_lineRenderer;

	std::vector<BrimstonCorner*> m_corners;
	std::vector<BrimstonBeam*> m_beams;
	BrimstonHit* m_hitEffect;

	unsigned char m_targetLayer;
	float m_damage;

	bool m_stopCounter;
	float m_counterMax;
	float m_counter;
	bool m_disableWhenCounterOver;

	float m_lerpPower;

private:
	Vector2 BezierCurve(const float& t);
	float BezierCurveLength();
	float BezierCurveLength(const float& t);
	Vector2 BezierCurveDirection(const float& t);
	void SetTargetMidAndTargetEnd();
	float Lerp(const float& a, const float& b, const float& t);
	float LerpAngle(float a, float b, const float& t);
	BrimstonCorner* CreateCorner();
	BrimstonBeam* CreateBeam();
	void ShowBezierCurve(const size_t& vertexCount);
	void PlaceCorner(const int& index, const float& t);
	void PlaceBeam(const int& indexA, const int& indexB);
	void PlaceHit();

public:
	void SetDirection(const float& Angle);
	void SetDirection(const Vector2& Direction);
	void SetTargetDirection(const float& TargetAngle);
	void SetTargetDirection(const Vector2& TargetDirection);
	const unsigned char& targetLayer() const;
	void setTargetLayer(const unsigned char& TargetLayer);
	void setDamage(const float& damage);
	void setCounter(const float& time);
	void setUseCounter(const bool& enable);
	void setDisableWhenCounterOver(const bool& enable);
	void setWidth(const float& width);
	void setLerpPower(const float& power);
	void setVertexCount(const size_t& count);
};

#endif