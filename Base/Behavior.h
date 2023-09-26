#pragma once
#ifndef __Behavior_h__
#define __Behavior_h__

#include "Component.h"

// �� Ŭ������ ��ӹ޾� ������Ʈ�� �����մϴ�.
class Behavior : public Component
{
protected:
	// �ش� �����ڸ� �����ε� ���� �ʾƵ� �˴ϴ�.
	// ������ Awake, Start���� �ʱ�ȭ�� �����Ͻʽÿ�.
	Behavior();

protected:
	// �ش� �Ҹ��ڸ� �����ε� ���� �ʾƵ� �˴ϴ�.
	// ������ OnDestroy���� �Ҹ��� �����Ͻʽÿ�.
	virtual ~Behavior();

public:
	virtual void Awake() override = 0;			// �� ������Ʈ�� ������ ���� ȣ��˴ϴ�. ���⿡�� �ʱ�ȭ�� �����մϴ�.
	virtual void Start() override = 0;			// �� ������Ʈ�� ������Ʈ �Ǳ� ������ �� �� ȣ��˴ϴ�. ���⿡�� �ٸ� ������Ʈ ������ �ϴ� ���� �����ϴ�.
	virtual void Update() override = 0;			// �� �����Ӹ��� ȣ��˴ϴ�.
	virtual void LateUpdate() override = 0;		// �� �������� ������Ʈ ���ĸ��� ȣ��˴ϴ�.

	virtual void OnEnable() override = 0;		// ������Ʈ�� ��Ȱ��ȭ ���¿��� Ȱ��ȭ �� ��� ȣ��˴ϴ�.
	virtual void OnDisable() override = 0;		// ������Ʈ�� Ȱ��ȭ ���¿��� ��Ȱ��ȭ ���°� �� ��� ȣ��˴ϴ�.
	virtual void OnDestroy() override = 0;		// ������Ʈ�� �ı��Ǳ� ������ ȣ��˴ϴ�.

	Transform* transform() const;				// �� ������Ʈ�� �����Ǿ� �ִ� ���� ������Ʈ�� Ʈ�������� ��ȯ�մϴ�.
	GameObject* gameObject() const;				// �� ������Ʈ�� �����Ǿ� �ִ� ���� ������Ʈ�� ��ȯ�մϴ�.
};

#endif
