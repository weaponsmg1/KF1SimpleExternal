#pragma once

#include <Windows.h>
#include <vector>

class Memory {
private:
	HANDLE processHandle;
	DWORD processId;
	uintptr_t gameModuleBase;

public:
	Memory(const char* processName, const char* moduleName);
	~Memory();

	uintptr_t ReadInt(uintptr_t address);
	bool WriteInt(uintptr_t address, int value);
	uintptr_t GetPointerAddress(uintptr_t baseAddress, const std::vector<uintptr_t>& offsets);
	uintptr_t GetGameModuleBase() const;
	bool IsValid() const;
};