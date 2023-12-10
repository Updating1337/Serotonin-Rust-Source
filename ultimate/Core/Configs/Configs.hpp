#pragma once

#include "../Includes/includes.hpp"
#include "../Utils/json.hpp"

class Configs {
public:
	static void SaveConfig();
	static void LoadConfig();
};

class Buttons {
public:
	static void ClearRaidCache();
	static void ClearLOSPoints();
	static void LoadLegitCheat();
	static void LoadRageCheat();
};