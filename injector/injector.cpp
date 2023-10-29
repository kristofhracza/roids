#include "injector.hpp"

bool DLLInjector::loadDLL(int procId){

	if (procId == 0) {
		return false;
	}

	wchar_t customDLL[MAX_PATH];
	GetFullPathName(fileName, MAX_PATH, customDLL, 0);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	LPVOID allocatedMemory = VirtualAllocEx(hProcess, NULL, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!WriteProcessMemory(hProcess, allocatedMemory, customDLL,MAX_PATH, NULL)) {
		CloseHandle(hProcess);
		return false;
	}

	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMemory, 0, 0);

	if (hProcess) {
		CloseHandle(hProcess);
	}

	return true;
}
