#pragma once
#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>
#include <psapi.h>

inline namespace DLLInjectorParams {
	inline uintptr_t procID;
	inline const wchar_t* fileName;
};

class DLLInjector {
public:
	static bool loadDLL(int procId);
};