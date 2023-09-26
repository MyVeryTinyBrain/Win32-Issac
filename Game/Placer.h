#pragma once
#ifndef __Placer_h__
#define __Placer_h__

class Machine;

class Placer
{
private:
	static Machine* g_machine;

public:
	static bool g_shouldReset;

	static void SetMachine(Machine* machine);
	static void Place();
	static void Release();

private:
	static void ResetPhysics();
	static void SetPhysics();
	static void ReleaseResources();
	static void LoadResources();
	static void ReleaseObjects();
	static void MakeObjects();
};

#endif
