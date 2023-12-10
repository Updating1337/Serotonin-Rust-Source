#pragma once

#include <windows.h>
#include <cstdint>
#include <cstddef>

static inline float Clamp01(float value)
{
	bool flag = value < 0.f;
	float result;
	if (flag)
	{
		result = 0.f;
	}
	else
	{
		bool flag2 = value > 1.f;
		if (flag2)
		{
			result = 1.f;
		}
		else
		{
			result = value;
		}
	}
	return result;
}


inline bool m_wcsicmp(const wchar_t a, const wchar_t* b) {
	if (!a)
		return false;
	int ret = 0;
	wchar_t* p1 = (wchar_t*)a;
	wchar_t* p2 = (wchar_t*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}

namespace Math {





	double pow(double x, double y);
	float powf(float x, float y);
	double fmod(double x, double y);
	float fmodf(float x, float y);
	double atof(const char* data);

	double floor(double x);
	float floorf(float x);
	double ceil(double x);
	float ceilf(float x);
	float my_asin(float x);
	float my_atan2(float y, float x);
	float my_sqrt(float number);

	float roundf(float x);

	float fabsf(float x);
	float sqrtf(float number);
	float my_abs(float x);
	float my_sqrt(float x);

	float sinf(float x);
	float cosf(float x);
	float tanf(float x);

	float asinf(float x);
	float acosf(float x);
	float atanf(float x);

	float atan2f(float y, float x);
	double atof(const char* str);

	inline float abs(float x)
	{
		return fabsf(x);
	}
}
