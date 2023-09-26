#pragma once
#ifndef __Behavior_h__
#define __Behavior_h__

#include "Component.h"

// 이 클래스를 상속받아 컴포넌트를 구현합니다.
class Behavior : public Component
{
protected:
	// 해당 생성자를 오버로딩 하지 않아도 됩니다.
	// 가능한 Awake, Start에서 초기화를 진행하십시오.
	Behavior();

protected:
	// 해당 소멸자를 오버로딩 하지 않아도 됩니다.
	// 가능한 OnDestroy에서 소멸을 진행하십시오.
	virtual ~Behavior();

public:
	virtual void Awake() override = 0;			// 이 컴포넌트가 생성된 직후 호출됩니다. 여기에서 초기화를 진행합니다.
	virtual void Start() override = 0;			// 이 컴포넌트가 업데이트 되기 직전에 한 번 호출됩니다. 여기에서 다른 컴포넌트 참조를 하는 것이 좋습니다.
	virtual void Update() override = 0;			// 매 프레임마다 호출됩니다.
	virtual void LateUpdate() override = 0;		// 매 프레임의 업데이트 이후마다 호출됩니다.

	virtual void OnEnable() override = 0;		// 컴포넌트가 비활성화 상태에서 활성화 된 경우 호출됩니다.
	virtual void OnDisable() override = 0;		// 컴포넌트가 활성화 상태에서 비활성화 상태가 된 경우 호출됩니다.
	virtual void OnDestroy() override = 0;		// 컴포넌트가 파괴되기 직전에 호출됩니다.

	Transform* transform() const;				// 이 컴포넌트가 부착되어 있는 게임 오브젝트의 트랜스폼을 반환합니다.
	GameObject* gameObject() const;				// 이 컴포넌트가 부착되어 있는 게임 오브젝트를 반환합니다.
};

#endif
