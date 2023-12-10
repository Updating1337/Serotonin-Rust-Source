#pragma once
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace connector {

	template<typename T>
	class write_traits;

	class writer {
	public:
		inline const unsigned char* data() const {
			return data_.data();
		}

		inline size_t size() const {
			return data_.size();
		}

		inline void write_bytes(const unsigned char* data, size_t size) {
			for (size_t i = 0; i < size; i++)
				data_.push_back(data[i]);
		}

		template<typename T>
		void write(const T& data) {
			write_traits<T>::write(*this, data);
		}

	private:
		std::vector<unsigned char> data_;
	};

	template<typename T>
	static void write_integer(writer& writer, T data) {
		unsigned char buffer[sizeof(data)];
		for (size_t i = 0; i < sizeof(data); i++)
			buffer[i] = (data >> ((sizeof(data) - i - 1) * 8)) & (T)0xFF;

		writer.write_bytes(buffer, sizeof(buffer));
	}

	template<typename T>
	class write_traits {};

	template<>
	class write_traits<const char*> {
	public:
		using item = const char*;

		static void write(writer& writer, const item& data);
	};

	template<typename T>
	class write_traits<std::pair<const T*, size_t>> {
	public:
		static void write(writer& writer, const std::pair<const T*, size_t>& data) {
			auto [ptr, length] = data;

			writer.write((uint64_t)length);
			for (size_t i = 0; i < length; i++)
				writer.write(ptr[i]);
		}
	};

	template<>
	class write_traits<float> {
	public:
		static inline void write(writer& writer, const float& data) {
			static_assert(sizeof(float) == sizeof(uint32_t));

			uint32_t ival;
			memcpy(&ival, &data, sizeof(ival));

			writer.write(ival);
		}
	};

#define WRITE_INTEGER(ty) template<> \
class write_traits<ty> { \
public: \
	static inline void write(writer& writer, const ty& data) { \
		write_integer(writer, data); \
	} \
}; 

	WRITE_INTEGER(unsigned char)
		WRITE_INTEGER(uint16_t)
		WRITE_INTEGER(uint32_t)
		WRITE_INTEGER(uint64_t)

#undef WRITE_INTEGER

}