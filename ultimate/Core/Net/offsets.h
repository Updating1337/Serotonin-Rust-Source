#pragma once
#include "config.h"
#include "../CRT/mutex/smutex.hpp"

#include <vector>
#include "data.h"
#include "singleton.h"

class OffsetManager : public Singleton<OffsetManager> {
public:
	OffsetManager();

	void add_offset(connector::offsets offset);

	/**
	 * @brief requests offset from server
	 * @param hash - hashed name of the offset
	 * @param value - output value - the requested offset, NULL if the request wasn't sucessfull
	 * @param base_index - index of base address on server which should be added to the actual offset value
	 * @param non_blocking - if true the function won't block the thread and will return false or true depending if we have read some offset
	 *					   - if false the function waits till the offset is avaliable in cache vector of this class, 
	 *						 !be aware if you remove the offset and try to request it again with non_blocking=false you can get into infinite loop
	 *						 since the offset won't be requested again coz it's already in request_list 
	 * @param remove_after_use - removes offset from cache vector
	 * @return 
	*/
	bool request(uint32_t hash, uint64_t& value, uint32_t base_index, bool non_blocking = true, bool remove_after_use = false);
private:
	/**
	 * @brief checks if the has is already on the request list
	 * @param hash - hash of the offset we want
	 * @return true if the hash is present
	*/
	bool check_request_list(uint32_t hash);
	/**
	 * @brief requestts offset from the server and adds the hash to the request_list
	 * @param hash - hash of the offset we want
	 * @param base_index - index of base address on server which should be added to the actual offset value
	 * @return true on success!
	*/
	bool request_from_server(uint32_t hash, uint32_t base_index);
	/**
	 * @brief removes offset from cache, before calling this func, make sure to lock the mutex!
	 * @param hash - hash of the offset to remove
	 * @returns true on success!
	*/
	bool remove_by_hash(uint32_t hash);

	rb::smutex mutex;

	/**
	 * @brief contains all recieved offsets
	*/
	std::vector<connector::offsets> cache;

	/**
	 * @brief array already requested hashes
	 *		  so we won't request same offset more than once
	*/
	std::vector<uint32_t> request_list;
};