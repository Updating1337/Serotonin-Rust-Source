#pragma once

#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

namespace connector {

	class read_error : public std::runtime_error {
	public:
		inline read_error(const char* what) : std::runtime_error(what) {}
	};

	template<typename T>
	class read_traits;

	class reader {
	public:
		inline reader(const unsigned char* data, size_t size) : data_(data), size_(size), position_(0) {}

		void read_bytes(unsigned char* buffer, size_t size);

		template<typename T>
		T read() {
			return read_traits<T>::read(*this);
		}

	private:
		const unsigned char* data_;
		size_t size_;
		size_t position_;
	};

	template<typename T>
	T read_integer(reader& reader) {
		unsigned char buffer[sizeof(T)];
		reader.read_bytes(buffer, sizeof(buffer));

		T n = 0;
		for (size_t i = 0; i < sizeof(T); i++)
			n |= (T)buffer[i] << ((sizeof(T) - i - 1) * 8);

		return n;
	}

	template<typename T>
	class read_traits {};

	template<>
	class read_traits<std::string> {
	public:
		static std::string read(reader& reader);
	};

	template<typename T>
	class read_traits<std::vector<T>> {
	public:
		static std::vector<T> read(reader& reader) {
			auto length = reader.read<uint64_t>();

			std::vector<T> data;
			for (uint64_t i = 0; i < length; i++)
				data.push_back(reader.read<T>());

			return data;
		}
	};

	template<>
	class read_traits<float> {
	public:
		static inline float read(reader& reader) {
			static_assert(sizeof(float) == sizeof(uint32_t));

			auto ival = reader.read<uint32_t>();

			float fval;
			memcpy(&fval, &ival, sizeof(ival));

			return fval;
		}
	};

#define READ_INTEGER(ty) template<> \
class read_traits<ty> { \
public: \
	static inline ty read(reader& reader) { \
		return read_integer<ty>(reader); \
	} \
};

	READ_INTEGER(unsigned char)
		READ_INTEGER(uint16_t)
		READ_INTEGER(uint32_t)
		READ_INTEGER(uint64_t)

#undef READ_INTEGER

}