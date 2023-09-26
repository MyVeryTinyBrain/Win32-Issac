#include "stdafx.h"
#include "TestRemover.h"

void TestRemover::Awake()
{
}

void TestRemover::Start()
{
}

void TestRemover::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		gameObject()->Destroy();
	}
}

void TestRemover::LateUpdate()
{
}

void TestRemover::OnEnable()
{
}

void TestRemover::OnDisable()
{
}

void TestRemover::OnDestroy()
{
}
