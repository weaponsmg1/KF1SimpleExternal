#include "Features.h"
#include <Windows.h>
#include <vector>

Features g_Features;

int ammo = 9999;
int health = 100;

bool infhealth = false;
bool infammo = false;

void Features::InfinityHealth(Memory& mem)
{
	if (!mem.IsValid()) return;

	uintptr_t gameModuleBase = mem.GetGameModuleBase();
	std::vector<uintptr_t> offsets = { 0x44, 0x480 };

	uintptr_t targetAddress = mem.GetPointerAddress(gameModuleBase + 0x001682F4, offsets);
	if (targetAddress != 0) {
		mem.WriteInt(targetAddress, health);
		Sleep(100);
	}
}

void Features::InfinityAmmo(Memory& mem)
{
	if (!mem.IsValid()) return;

	uintptr_t gameModuleBase = mem.GetGameModuleBase();

	//Offsets 

	// Pistol
	std::vector<uintptr_t> offsets = { 0x3C4, 0x1C, 0x5A0 };

	// Address

	// Pistol
	uintptr_t targetAddress = mem.GetPointerAddress(gameModuleBase + 0x00168B58, offsets);

	if (targetAddress != 0) 
	{
		// Pistol
		mem.WriteInt(targetAddress, ammo);

		Sleep(500);
	}
}

void Features::Main()
{
	Memory mem("KillingFloor.exe", "Core.dll");

	if (mem.IsValid())
	{
		if (infammo)
		{
			g_Features.InfinityAmmo(mem);
		}

		if (infhealth)
		{
			g_Features.InfinityHealth(mem);
		}
	}

}