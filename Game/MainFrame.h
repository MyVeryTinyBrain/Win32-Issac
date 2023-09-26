#pragma once
#ifndef __MainFrame_h__
#define __MainFrame_h__

class MainFrame
{
	ULONGLONG prev;
	ULONGLONG over;
	HDCEx* memDC;
	Machine* machine;

public:
	MainFrame();
	~MainFrame();

	void WinLoop();
private:
	void Initalize();
	void Release();
	void MainLoop();
};

#endif
