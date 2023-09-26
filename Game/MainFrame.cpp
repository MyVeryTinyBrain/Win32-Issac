#include "stdafx.h"
#include "MainFrame.h"
#include "Placer.h"
#include "SoundMgr.h"

MainFrame::MainFrame()
{
	Initalize();
}

MainFrame::~MainFrame()
{
	Release();
}

void MainFrame::WinLoop()
{
    static int fpsCount = 0;
    static ULONGLONG prevFPSCheck = GetTickCount64();

    ULONGLONG interval = (ULONGLONG)(1000.0f / Global::fps);
    ULONGLONG cur = GetTickCount64();
    ULONGLONG elapsed = over + cur - prev;

    if (elapsed >= interval)
    {
        if (elapsed > interval) over = elapsed - interval;
        else over = 0;
        
        Global::unscaledDeltaTime = (float)(elapsed - over) / 1000.0f;
        Global::deltaTime = Global::unscaledDeltaTime * Global::timeScale;

        PatBlt(*memDC, 0, 0, Global::cx, Global::cy, BLACKNESS);
        MainLoop();
        BitBlt(Global::hdc, 0, 0, Global::cx, Global::cy, *memDC, 0, 0, SRCCOPY);

        prev = GetTickCount64();

        ++fpsCount;
        if (cur >= prevFPSCheck + 1000)
        {
            TCHAR fpsText[32];
            _stprintf_s(fpsText, TEXT("fps: %d"), fpsCount);
            SetWindowText(Global::hWnd, fpsText);

            fpsCount = 0;
            prevFPSCheck = cur;
        }
    }
}

void MainFrame::Initalize()
{
    prev = GetTickCount64();
    over = 0;

    Global::hdc = GetDC(Global::hWnd);
    memDC = new HDCEx(Global::hdc);
    BaseGlobal::Init(&Global::hWnd, memDC, &Global::cx, &Global::cy, &Global::deltaTime, &Global::unscaledDeltaTime);
    machine = new Machine();

    CSoundMgr::Get_Instance()->Initialize();
    Placer::SetMachine(machine);
    Placer::Place();
}

void MainFrame::Release()
{
    Placer::Release();

    CSoundMgr::Get_Instance()->Destroy_Instance();

    SAFE_DELETE(memDC);
    ReleaseDC(Global::hWnd, Global::hdc);
}

void MainFrame::MainLoop()
{
    if (Placer::g_shouldReset)
    {
        Placer::g_shouldReset = false;
        Placer::Release();
        Placer::Place();
        return;
    }
    machine->UpdateAll();
    machine->Render(*memDC);
    Input::instance()->SetUsed();
}
