#include "stdafx.h"
#include "Controller.h"

void Controller::Awake()
{
	cam = gameObject()->GetComponent<Camera2D>();
}

void Controller::Start()
{
}

void Controller::Update()
{
	float speed = 200;
	float x = transform()->position().x;
	float y = transform()->position().y;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		x -= speed * Global::deltaTime;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		x += speed * Global::deltaTime;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		y += speed * Global::deltaTime;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		y -= speed * Global::deltaTime;
	transform()->setPosition({ x,y });

	float aspeed = 10;
	float a = transform()->angle();
	if (Input::GetKey(Key::Q))
		a += speed * DEG2RAD * Global::deltaTime;
	if (Input::GetKey(Key::E))
		a -= speed * DEG2RAD * Global::deltaTime;
	transform()->setAngle(a);

	float sspeed = 1;
	Vector2 s = transform()->size();
	if (GetAsyncKeyState('W') & 0x8000)
		s.y += sspeed * Global::deltaTime;
	if (GetAsyncKeyState('S') & 0x8000)
		s.y -= sspeed * Global::deltaTime;
	if (GetAsyncKeyState('A') & 0x8000)
		s.x += sspeed * Global::deltaTime;
	if (GetAsyncKeyState('D') & 0x8000)
		s.x -= sspeed * Global::deltaTime;
	transform()->setSize(s);

	if (GetAsyncKeyState('1') & 0x8000)
		transform()->setPosition({ -100,100 });
	if (GetAsyncKeyState('2') & 0x8000)
		transform()->setPosition({ 0,0 });
	if (GetAsyncKeyState('3') & 0x8000)
		transform()->setPosition({ 100,-100 });

	if (Input::GetKey(Key::F5))
		cam->setHorizontal(cam->horizontal() + 100 * Global::deltaTime);
	if (Input::GetKey(Key::F6))
		cam->setHorizontal(cam->horizontal() - 100 * Global::deltaTime);
	if (Input::GetKey(Key::F7))
		cam->setVertical(cam->vertical() + 100 * Global::deltaTime);
	if (Input::GetKey(Key::F8))
		cam->setVertical(cam->vertical() - 100 * Global::deltaTime);
}

void Controller::LateUpdate()
{
}

void Controller::OnEnable()
{
}

void Controller::OnDisable()
{
}

void Controller::OnDestroy()
{
}
