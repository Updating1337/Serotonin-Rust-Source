#include "config.h"
#include "../CRT/mutex/smutex.hpp"
#include "offsets.h"
#include "net.h"

OffsetManager::OffsetManager()
{
	cache.clear();
}

void OffsetManager::add_offset(connector::offsets offset)
{
#ifdef HAS_CRT
	std::lock_guard<std::mutex>lock(mutex);
	cache.push_back(offset);
#else
	mutex.lock();
	cache.push_back(offset);
	mutex.unlock();
#endif
}

bool OffsetManager::request(uint32_t hash, uint64_t& value, uint32_t base_index, bool non_blocking, bool remove_after_use)
{
	while (true) {
		bool found = false;
		{
#ifdef HAS_CRT
			std::lock_guard<std::mutex>lock(mutex);
#else
			mutex.lock();
#endif		
			for (auto& iter : cache) {
				if (iter.hash != hash)
					continue;

				value = iter.value;
				found = true;
				break;
			}
#ifndef HAS_CRT
			mutex.unlock();
#endif
		}

		if (found) {
			if (remove_after_use) {
				remove_by_hash(hash);
			}
			return true;
		}

		request_from_server(hash, base_index);

		if (non_blocking) {
			return false;
		}

		//wait a bit so we don't spike our CPU ussage coz of this infnite loop
#ifdef HAS_CRT
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
#else
		LI_FN(Sleep).cached()(30);
#endif
	}
}

bool OffsetManager::check_request_list(uint32_t hash)
{
	bool found = false;
	for (auto& iter : request_list)
	{
		if (iter == hash) {
			found = true;
			break;
		}
	}
	return found;
}

bool OffsetManager::request_from_server(uint32_t hash, uint32_t base_index)
{
	if (check_request_list(hash))
		return false;

	net->request_offset(hash, base_index);
	request_list.push_back(hash);
	return true;
}

bool OffsetManager::remove_by_hash(uint32_t hash)
{
#ifdef HAS_CRT
	std::lock_guard<std::mutex>lock(mutex);
#else
	mutex.lock();
#endif
	size_t index = 0;
	bool found = false;
	for (size_t i = 0; i < cache.size(); i++) {
		if (cache[i].hash != hash)
			continue;

		found = true;
		index = i;
		break;
	}

	if (!found) {
#ifndef HAS_CRT
		mutex.unlock();
#endif
		return false;
	}

	cache.erase(cache.begin() + index);

	found = false;
	for (size_t i = 0; i < request_list.size(); i++) {
		if (request_list[i] != hash)
			continue;

		found = true;
		index = i;
		break;
	}

	if (!found) {
#ifndef HAS_CRT
		mutex.unlock();
#endif
		return false;
	}

	request_list.erase(request_list.begin() + index);

#ifndef HAS_CRT
	mutex.unlock();
#endif
	return true;
}