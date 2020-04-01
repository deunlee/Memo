#include <stdio.h>
#include <Windows.h>

void UseConsole()
{
	FILE* streamIn;
	FILE* streamOut;
	FILE* streamErr;

	AllocConsole();
	freopen_s(&streamIn,  "CONIN$",  "r", stdin);
	freopen_s(&streamOut, "CONOUT$", "w", stdout);
	freopen_s(&streamErr, "CONOUT$", "w", stderr);
}
