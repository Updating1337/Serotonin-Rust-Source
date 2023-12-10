#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include "../CRT/ntwinddk.hpp"

#include <string>

constexpr std::uint64_t HashPrime = 1099511628211;
constexpr std::uint64_t HashBasis = 14695981039346656037;

template< typename Type >
constexpr bool IsUpper(const Type character)
{
	return (character >= static_cast<const Type>(65) &&
		character <= static_cast<const Type>(90));
}

template< typename Type >
constexpr Type ToLower(const Type character)
{
	if (IsUpper(character))
	{
		return (character + static_cast<const Type>(32));
	}

	return character;
}

template< typename Type >
constexpr bool IsTerminator(const Type character)
{
	return (character == static_cast<const Type>(0));
}

template< typename Type >
constexpr std::size_t GetLength(const Type* const data)
{
	std::size_t length = 0;

	while (true)
	{
		if (IsTerminator(data[length]))
		{
			break;
		}

		length++;
	}

	return length;
}


//template <typename Type>
//constexpr std::uint64_t HashCompute(std::uint64_t hash, const Type* const data, std::size_t size, bool ignore_case)
//{
//	std::uint64_t finalHash = hash;
//	for (std::size_t i = 0; i < size; ++i) {
//		const auto element = static_cast<std::uint64_t>(ignore_case ? ToLower(data[i]) : data[i]);
//		finalHash = (finalHash * HashPrime) ^ element;
//	}
//	return finalHash;
//}

template <typename Type>
constexpr std::uint64_t HashCompute(std::uint64_t hash, const Type* const data, std::size_t size, bool ignore_case)
{
	std::uint64_t finalHash = hash;
	if (ignore_case) {
		// Preprocess data to lowercase
		for (std::size_t i = 0; i < size; ++i) {
			finalHash = (finalHash * HashPrime) ^ ToLower(data[i]);
		}
	}
	else {
		for (std::size_t i = 0; i < size; ++i) {
			finalHash = (finalHash * HashPrime) ^ data[i];
		}
	}
	return finalHash;
}

template< typename Type >
constexpr std::uint64_t Hash(const Type* const data, std::size_t size, bool ignore_case)
{
	return HashCompute(HashBasis, data, size, ignore_case);
}
constexpr std::uint64_t Hash_C(const char* const data, bool ignore_case)
{
	const auto length = GetLength(data);
	return Hash(data, length, ignore_case);
}
constexpr std::uint64_t Hash(const char* const data, bool ignore_case)
{
	const auto length = GetLength(data);
	return Hash(data, length, ignore_case);
}

constexpr std::uint64_t Hash(const wchar_t* const data, bool ignore_case)
{
	const auto length = GetLength(data);
	return Hash(data, length, ignore_case);
}

constexpr std::uint64_t Hash(const ANSI_STRING& data, bool ignore_case)
{
	const auto length = data.Length / sizeof(char);
	return Hash(data.Buffer, length, ignore_case);
}

constexpr std::uint64_t Hash(const UNICODE_STRING& data, bool ignore_case)
{
	const auto length = data.Length / sizeof(wchar_t);
	return Hash(data.Buffer, length, ignore_case);
}

template< typename Type >
constexpr std::uint64_t Hash(const std::basic_string< Type >& data, bool ignore_case)
{
	return Hash(data.c_str(), data.size(), ignore_case);
}


#define HASH( Data )																							\
	[ & ]()																													\
	{																																\
		constexpr auto hash = Hash( Data, true );	\
		return hash;																									\
	}()