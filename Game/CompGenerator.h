#pragma once
#ifndef __CompGenerator_h__
#define __CompGenerator_h__

template <typename T>
T* CompGenerate()
{
	GameObject* obj = new GameObject();
	return obj->AddComponent<T>();
}

template <typename T>
T* CompGenerate(Transform* parent)
{
	GameObject* obj = new GameObject(parent);
	return obj->AddComponent<T>();
}

template <typename T>
T* CompGenerate(const Vector2& position)
{
	GameObject* obj = new GameObject(position);
	return obj->AddComponent<T>();
}

template <typename T>
T* CompGenerate(const Vector2& position, Transform* parent)
{
	GameObject* obj = new GameObject(position, parent);
	return obj->AddComponent<T>();
}

#endif
