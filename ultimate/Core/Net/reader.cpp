#include "reader.h"

namespace connector {

	void reader::read_bytes(unsigned char* buffer, size_t size) {
		if (position_ + size > size_) {
			return; //"Out of bounds read"
		}

		memcpy(buffer, data_ + position_, size);
		position_ += size;
	}

	std::string read_traits<std::string>::read(reader& reader) {
		auto length = reader.read<uint64_t>();

		std::string result;
		for (uint64_t i = 0; i < length; i++)
			result += (char)reader.read<unsigned char>();

		return result;
	}

}
