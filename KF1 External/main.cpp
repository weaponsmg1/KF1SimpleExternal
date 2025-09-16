#include "Memory.h"
#include "Features.h"
#include "iostream" 

bool speedhack = false;

int main()
{
	system("color 4");
	system("title KF1 External");

	std::cout << "F1.Infinity Health\nF2.Infinity Ammo (Pistol Only)\nF3.Speehack(Need enabled Infinity Health)\nby weapon_smg1\n!!!USE OWN YOUR RISK!!!\n";

	while (true)
	{
		if (speedhack)
		{
			health = 9999;
		}
		else
		{
			health = 100;
		}

		if (GetAsyncKeyState(VK_F1) & 1)
		{
			infhealth = !infhealth;
			std::cout << "Toggle Infinity Health\n";
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			infammo = !infammo;
			std::cout << "Toggle Infinity Ammo\n";
		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			speedhack = !speedhack;
			std::cout << "Toggle speedhack\n";
		}

		g_Features.Main();

		Sleep(50);
	}

	return 0;
}