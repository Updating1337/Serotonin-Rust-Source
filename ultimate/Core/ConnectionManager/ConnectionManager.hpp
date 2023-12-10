#pragma once

#include "../Includes/includes.hpp"


class ConnectionManager {
public:
	static auto Instance() -> ConnectionManager*
	{
		ConnectionManager obj;
		return &obj;
	}
public:
	bool IsConnected();
	void ResetPlayerCache();
};