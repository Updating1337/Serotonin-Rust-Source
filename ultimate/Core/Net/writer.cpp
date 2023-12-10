#include <cstring>

#include "writer.h"

namespace connector {

	void write_traits<const char*>::write(writer& writer, const item& data) {
		auto length = strlen(data);

		writer.write((uint64_t)length);
		writer.write_bytes((const unsigned char*)data, length);
	}

}