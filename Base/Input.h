#pragma once
#ifndef __Input_h__
#define __Input_h__

enum class Key : unsigned char
{
	Tab = 0x09,
	Return = 0x0D,
	Escape = 0x1B,
	Space = 0x20,

	Left = 0x25,
	Up, Right,
	Down = 0x28,

	Zero = 0x30,
	One, Two, Three, Four, Five, Six, Seven, Eight,
	Nine = 0x39,

	A = 0x41,
	B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y,
	Z = 0x5A,
	LWin = 0x5B,
	RWin = 0x5C,

	Num0 = 0x60,
	Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8,
	Num9 = 0x69,

	NumMultiply = 0x6A,
	NumAdd, NumSeparator, NumSubtract, NumDecimal,
	NumDivide = 0x6F,

	F1 = 0x70,
	F2, F3, F4, F5, F6, F7, F8, F9, F10, F11,
	F12 = 0X7B,

	LShift = 0xA0,
	RShift, LControl,
	RControl = 0xA3,
	LAlt = 0xA4,
	RAlt = 0xA5,
};

class Input
{
	bool m_keyState[0xFF];
	bool m_hasDown;
	bool m_downState[0xFF];
	bool m_hasUp;
	bool m_upState[0xFF];

public:
	void SetKeyDown(unsigned char key);
	void SetKeyUp(unsigned char key);
	void SetUsed();

private:
	static Input g_instance;

public:
	static Input* instance();

	static const bool& GetKey(const Key& key);
	static const bool& GetKeyDown(const Key& key);
	static const bool& GetKeyUp(const Key& key);
	static Vector2 GetMousePointInScreen();
	static Vector2 GetMousePointInWorld();
};

#endif
