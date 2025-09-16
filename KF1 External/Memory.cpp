#include "Memory.h"
#include <TlHelp32.h>
#include <iostream>

Memory::Memory(const char* processName, const char* moduleName) {
	processHandle = nullptr;
	processId = 0;
	gameModuleBase = 0;

	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		return;
	}

	if (Process32First(snapshot, &processEntry)) {
		do {
			if (strcmp(processEntry.szExeFile, processName) == 0) {
				processId = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshot, &processEntry));
	}
	CloseHandle(snapshot);

	if (processId == 0) {
		return;
	}

	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (processHandle == nullptr) {
		return;
	}

	MODULEENTRY32 moduleEntry;
	moduleEntry.dwSize = sizeof(MODULEENTRY32);

	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
	if (snapshot == INVALID_HANDLE_VALUE) {
		return;
	}

	if (Module32First(snapshot, &moduleEntry)) {
		do {
			if (strcmp(moduleEntry.szModule, moduleName) == 0) {
				gameModuleBase = (uintptr_t)moduleEntry.modBaseAddr;
				break;
			}
		} while (Module32Next(snapshot, &moduleEntry));
	}
	CloseHandle(snapshot);
}

Memory::~Memory() {
	if (processHandle != nullptr) {
		CloseHandle(processHandle);
	}
}

uintptr_t Memory::ReadInt(uintptr_t address) {
	uintptr_t value = 0;
	SIZE_T bytesRead;

	if (ReadProcessMemory(processHandle, (LPCVOID)address, &value, sizeof(value), &bytesRead)) {
		return value;
	}

	return 0;
}

bool Memory::WriteInt(uintptr_t address, int value) {
	SIZE_T bytesWritten;

	if (WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(value), &bytesWritten)) {
		return true;
	}

	return false;
}

uintptr_t Memory::GetPointerAddress(uintptr_t baseAddress, const std::vector<uintptr_t>& offsets) {
	uintptr_t addr = ReadInt(baseAddress);

	for (size_t i = 0; i < offsets.size() - 1; i++) {
		addr = ReadInt(addr + offsets[i]);
		if (addr == 0) {
			return 0;
		}
	}

	return addr + offsets.back();
}

uintptr_t Memory::GetGameModuleBase() const {
	return gameModuleBase;
}

bool Memory::IsValid() const {
	return processHandle != nullptr && gameModuleBase != 0;
}