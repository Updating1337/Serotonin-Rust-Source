#pragma once
#include <atomic>
#include <mutex>
#include <vector>

struct FileHandle {
	std::string name;
	std::vector<unsigned char> data;
	size_t size;
};