#include "stdafx.h"
#include "Resizer.h"

void Resizer::Awake()
{
}

void Resizer::Start()
{
}

void Resizer::Update()
{
	float x = transform()->localSize().x;
	float y = transform()->localSize().y;
	x += speed_x * Global::deltaTime;
	y += speed_y * Global::deltaTime;
	transform()->setLocalSize({ x,y });
	if (x > 1.5f || x < 0.5f) speed_x *= -1;
	if (y > 1.5f || y < 0.5f) speed_y *= -1;
}

void Resizer::LateUpdate()
{
}

void Resizer::OnEnable()
{
}

void Resizer::OnDisable()
{
}

void Resizer::OnDestroy()
{
}
