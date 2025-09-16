#pragma once
#include "Memory.h"
#include <vector>

extern int ammo;
extern int health;

extern bool infhealth;
extern bool infammo;

class Features
{
public:
	void InfinityAmmo(Memory& mem);
	void InfinityHealth(Memory& mem);
	void Main();
};

extern Features g_Features;
