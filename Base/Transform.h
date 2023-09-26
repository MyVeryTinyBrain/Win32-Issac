#pragma once
#ifndef __Transform_h__
#define __Transform_h__

#include "Behavior.h"

class GameObject;

class Transform : public Behavior
{
	friend class GameObject;

	GameObject* m_gameObject;
	bool m_parentEnable;

	Vector2 m_position;
	float m_angle; // radian
	Vector2 m_size;
	Vector2 m_localPosition;
	float m_localAngle;
	Vector2 m_localSize;
	Transform* m_parent;
	std::vector<Transform*> m_childs;

public:
	Transform(GameObject* gameObject);
	virtual ~Transform();

	GameObject* gameObject();

	// Linear algebra
	Matrix3x3 localToWorldMatrix() const;
	Matrix3x3 worldToLocalMatrix() const;
	Vector2 up() const;
	Vector2 right() const;

	// Tree
	void ForceUpdate(Transform* _root = nullptr);
	Transform* root() const;
	size_t childCount() const;
	Transform* getChild(size_t index) const;
	void addChild(Transform* transform);
	void detachChild(Transform* transform);
	void detachAllChilds();
	Transform* parent() const;
	void setParent(Transform* transform);
	const bool& parentEnable() const;

	// Transform
	const Vector2& position() const;
	const float& angle() const; // radian
	const Vector2& size() const;
	const Vector2& localPosition() const;
	const float& localAngle() const; // radian
	const Vector2& localSize() const;
	void setPosition(const Vector2& position);
	void setAngle(const float& radian);
	void setSize(const Vector2& size);
	void setLocalPosition(const Vector2& localPosition);
	void setLocalAngle(const float& localRadian);
	void setLocalSize(const Vector2& localSize);

private:
	void UpdateGlobalPosition();
	void UpdateGlobalAngle();
	void UpdateGlobalSize();
	void UpdateLocalPosition();
	void UpdateLocalAngle();
	void UpdateLocalSize();
	void UpdateSubEnable();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;
};

#endif
