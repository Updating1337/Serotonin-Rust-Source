#include "math.hpp"
#include <intrin.h>

namespace Math{

#define DBL_EPSILON      2.2204460492503131e-016 // smallest such that 1.0+DBL_EPSILON != 1.0
#define M_PI_2 1.57079632679489661923
#define M_PI 3.14159265358979323846f

	constexpr float XM_PI = 3.141592654f;
	constexpr float XM_2PI = 6.283185307f;
	constexpr float XM_1DIVPI = 0.318309886f;
	constexpr float XM_1DIV2PI = 0.159154943f;
	constexpr float XM_PIDIV2 = 1.570796327f;
	constexpr float XM_PIDIV4 = 0.785398163f;
	constexpr double PI = 3.14159265358979323846;
	constexpr double TWO_PI = 2.0 * PI;

#define GET_FLOAT_WORD( i, d )			\
	do																\
	{																	\
		ieee_float_shape_type gf_u;			\
		gf_u.value = ( d );							\
		( i ) = gf_u.word;							\
	}																	\
	while( 0 )

#define SET_FLOAT_WORD( d, i )			\
	do																\
	{																	\
		ieee_float_shape_type sf_u;			\
		sf_u.word = ( i );							\
		( d ) = sf_u.value;							\
	}																	\
	while( 0 )


	double pow(double x, double y)
	{
		if (y == 0) {
			return 1.0;
		}

		if (y < 0) {
			// For negative exponents, calculate the reciprocal of the result
			x = 1.0 / x;
			y = -y;
		}

		double result = 1.0;
		while (y > 0) {
			if ((int)y % 2 == 1) {
				// If the current exponent is odd, multiply by the base (x)
				result *= x;
			}
			// Square the base (x) and halve the exponent (y) for the next iteration
			x *= x;
			y /= 2;
		}

		return result;
	}

	float powf(float x, float y)
	{
		return static_cast<float>(pow(static_cast<double>(x), static_cast<double>(y)));
	}

	double fmod(double x, double y)
	{
		if (y == 0.0) {
			// Handle division by zero (or very close to zero)
			return 0.0; // You can choose an appropriate return value here
		}

		// Calculate the integer quotient
		double quotient = x / y;

		// Calculate the truncated quotient (integer part)
		double truncatedQuotient = static_cast<long long>(quotient); // Casting to long long for floor-like behavior

		// Calculate the floating-point remainder
		double remainder = x - truncatedQuotient * y;

		// Handle the case when the remainder might be negative
		if ((y < 0.0 && remainder > 0.0) || (y > 0.0 && remainder < 0.0))
			remainder += y;

		return remainder;
	}

	float fmodf(float x, float y)
	{
		return static_cast<float>(fmod(static_cast<double>(x), static_cast<double>(y)));
	}

	double atof(const char* data)
	{
		double result = 0.0;
		int sign = 1;
		int decimalPlace = 0;
		bool hasDecimal = false;

		// Handle leading whitespaces
		while (*data == ' ')
			data++;

		// Check for a sign character (+/-)
		if (*data == '-' || *data == '+') {
			sign = (*data == '-') ? -1 : 1;
			data++;
		}

		// Convert the integer part of the number
		while (*data != '\0' && (*data >= '0' && *data <= '9')) {
			result = result * 10.0 + (*data - '0');
			data++;
		}

		// Convert the decimal part of the number
		if (*data == '.') {
			hasDecimal = true;
			data++;

			while (*data != '\0' && (*data >= '0' && *data <= '9')) {
				result = result * 10.0 + (*data - '0');
				decimalPlace++;
				data++;
			}
		}

		// Handle any remaining characters
		while (*data != '\0' && (*data == ' ' || (*data >= '\t' && *data <= '\r')))
			data++;

		// Adjust the result based on the decimal place
		if (hasDecimal)
			result /= pow(10.0, decimalPlace);

		// Apply the sign
		return result * sign;
	}

	double floor(double x)
	{
		int integerPart = static_cast<int>(x); // Cast to int truncates the decimal part

		// If the number is already an integer or positive, return the integer part
		if (x >= 0 || x == static_cast<float>(integerPart)) {
			return integerPart;
		}

		// For negative numbers, subtract 1 from the integer part to get the floor value
		return integerPart - 1;
	}

	float floorf(float x)
	{
		return static_cast<float>(floor(static_cast<double>(x)));

	}
	double ceil(double x)
	{
		double integerPart = floor(x);
		if (x == integerPart) {
			return x;
		}
		return integerPart + 1.0;
	}

	float ceilf(float x)
	{
		return static_cast<float>(ceil(static_cast<double>(x)));
	}

	union ieee_float_shape_type
	{
		float value;
		std::uint32_t word;
	};

	float roundf(float x)
	{
		std::uint32_t w;
		GET_FLOAT_WORD(w, x);

		const auto exponent_less_127 = static_cast<std::int32_t>((w & 0x7f800000) >> 23) - 127;

		if (exponent_less_127 < 23)
		{
			if (exponent_less_127 < 0)
			{
				w &= 0x80000000;

				if (exponent_less_127 == -1)
				{
					w |= (static_cast<std::uint32_t>(127) << 23);
				}
			}
			else
			{
				const auto exponent_mask = 0x007fffffu >> exponent_less_127;

				if ((w & exponent_mask) == 0)
				{
					return x;
				}

				w += 0x00400000 >> exponent_less_127;
				w &= ~exponent_mask;
			}
		}
		else
		{
			if (exponent_less_127 == 128)
			{
				return x + x;
			}
			else
			{
				return x;
			}
		}

		SET_FLOAT_WORD(x, w);
		return x;
	}

	float fabsf(float x)
	{
		return (x < 0.f ? -x : x);
	}

	float my_abs(float x)
	{
		return fabsf(x);
	}

	//float sqrtf(float x)
	//{
	//	auto root = _mm_set_ss(x);
	//	root = _mm_sqrt_ss(root);
	//	return _mm_cvtss_f32(root);
	//}

	float sqrtf(float number) {
		auto root = _mm_set_ss(number);
		root = _mm_sqrt_ss(root);
		return _mm_cvtss_f32(root);
	}

	float my_sqrt(float x)
	{
		return sqrtf(x);
	}

	float sinf(float x)
	{
		auto quotient = XM_1DIV2PI * x;

		if (x >= 0.f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		auto y = x - XM_2PI * quotient;
		auto sign = 0.f;

		if (y > XM_PIDIV2)
		{
			y = XM_PI - y;
			sign = -1.f;
		}
		else if (y < -XM_PIDIV2)
		{
			y = -XM_PI - y;
			sign = -1.f;
		}
		else
		{
			sign = +1.f;
		}

		auto y2 = y * y;
		return ((((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.f) * y);
	}

	float cosf(float x)
	{
		auto quotient = XM_1DIV2PI * x;

		if (x >= 0.f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		auto y = x - XM_2PI * quotient;
		auto sign = 0.f;

		if (y > XM_PIDIV2)
		{
			y = XM_PI - y;
			sign = -1.f;
		}
		else if (y < -XM_PIDIV2)
		{
			y = -XM_PI - y;
			sign = -1.f;
		}
		else
		{
			sign = +1.f;
		}

		auto y2 = y * y;
		auto p = (((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.f);

		return (sign * p);
	}

	float tanf(float x)
	{
		auto s = sinf(x);
		auto c = cosf(x);

		return (s / c);
	}

	float asinf(float x)
	{
		auto non_negative = (x >= 0.f);

		auto pox = fabsf(x);
		auto omx = 1.f - pox;

		if (omx < 0.f)
		{
			omx = 0.f;
		}

		auto root = sqrtf(omx);
		auto result = (((((((-0.0012624911f * pox + 0.0066700901f) * pox - 0.0170881256f) * pox + 0.0308918810f) * pox - 0.0501743046f) * pox + 0.0889789874f) * pox - 0.2145988016f) * pox + 1.5707963050f);

		result *= root;
		return (non_negative ? (XM_PIDIV2 - result) : (result - XM_PIDIV2));
	}
	
	static double my_atan(double x)
	{
		// Return arctangent(x) given that 5/3 < x <= 2, with the same properties as atan.
		auto atani5 = [](double x) {
			constexpr double p00 = +0x1.124A85750FB5Cp+00;
			constexpr double p01 = +0x1.D59AE78C11C49p-03;
			constexpr double p02 = -0x1.8AD3C44F10DC3p-04;
			constexpr double p03 = +0x1.2B090AAD5F9DCp-05;
			constexpr double p04 = -0x1.881EC3D15241Fp-07;
			constexpr double p05 = +0x1.8CB82A74E0699p-09;
			constexpr double p06 = -0x1.3182219E21362p-12;
			constexpr double p07 = -0x1.2B9AD13DB35A8p-12;
			constexpr double p08 = +0x1.10F884EAC0E0Ap-12;
			constexpr double p09 = -0x1.3045B70E93129p-13;
			constexpr double p10 = +0x1.00B6A460AC05Dp-14;

			double y = x - 0x1.d555555461337p0;

			return ((((((((((+p10) * y + p09) * y + p08) * y + p07) * y + p06) * y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
			};
		// Return arctangent(x) given that 4/3 < x <= 5/3, with the same properties as
		// atan.
		auto atani4 = [](double x) {
			constexpr double p00 = +0x1730BD281F69Dp-01;
			constexpr double p01 = +0x1.3B13B13B13B0Cp-02;
			constexpr double p02 = -0x1.22D719C06115Ep-03;
			constexpr double p03 = +0x1.C963C83985742p-05;
			constexpr double p04 = -0x1.135A0938EC462p-06;
			constexpr double p05 = +0x1.13A254D6E5B7Cp-09;
			constexpr double p06 = +0x1.DFAA5E77B7375p-10;
			constexpr double p07 = -0x14AC1342182D2p-10;
			constexpr double p08 = +0x1.25BAD4D85CBE1p-10;
			constexpr double p09 = -0x1.E4EEF429EB680p-12;
			constexpr double p10 = +0x1.B4E30D1BA3819p-14;
			constexpr double p11 = +0x1.0280537F097F3p-15;

			double y = x - 0x1.8000000000003p0;

			return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
			};
		// Return arctangent(x) given that 1 < x <= 4 / 3, with the same properties as
		// atan.
		auto atani3 = [](double x) {
			constexpr double p00 = +0x1.B96E5A78C5C40p-01;
			constexpr double p01 = +0x1.B1B1B1B1B1B3Dp-02;
			constexpr double p02 = -0x1.AC97826D58470p-03;
			constexpr double p03 = +0x1.3FD2B9F586A67p-04;
			constexpr double p04 = -0x1.BC317394714B7p-07;
			constexpr double p05 = -0x1.2B01FC60CC37Ap-07;
			constexpr double p06 = +0x1.73A9328786665p-07;
			constexpr double p07 = -0x1.C0B993A09CE31p-08;
			constexpr double p08 = +0x1.2FCDACDD6E5B5p-09;
			constexpr double p09 = +0x1.CBD49DA316282p-13;
			constexpr double p10 = -0x1.0120E602F6336p-10;
			constexpr double p11 = +0x1.A89224FF69018p-11;
			constexpr double p12 = -0x1.883D8959134B3p-12;

			double y = x - 0x1.2aaaaaaaaaa96p0;

			return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
				p07) *
				y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
			};
		// Return arctangent(x) given that 3 / 4 < x <= 1, with the same properties as
		// atan.
		auto atani2 = [](double x) {
			constexpr double p00 = +0x1.700A7C580EA7Ep-01;
			constexpr double p01 = +0x1.21FB781196AC3p-01;
			constexpr double p02 = -0x1.1F6A8499714A2p-02;
			constexpr double p03 = +0x1.41B15E5E8DCD0p-04;
			constexpr double p04 = +0x1.59BC93F81895Ap-06;
			constexpr double p05 = -0x1.63B543EFFA4EFp-05;
			constexpr double p06 = +0x1.C90E92AC8D86Cp-06;
			constexpr double p07 = -0x1.91F7E2A7A338Fp-08;
			constexpr double p08 = -0x1.AC1645739E676p-08;
			constexpr double p09 = +0x1.152311B180E6Cp-07;
			constexpr double p10 = -0x1.265EF51B17DB7p-08;
			constexpr double p11 = +0x1.CA7CDE5DE9BD7p-14;

			double y = x - 0x1.c0000000f4213p-1;

			return (((((((((((+p11) * y + p10) * y + p09) * y + p08) * y + p07) * y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
			};
		// Return arctangent(x) given that 1/2 < x <= 3/4, with the same properties as
		// atan.
		auto atani1 = [](double x) {
			constexpr double p00 = +0x1.1E00BABDEFED0p-1;
			constexpr double p01 = +0x1.702E05C0B8155p-1;
			constexpr double p02 = -0x1.4AF2B78215A1Bp-2;
			constexpr double p03 = +0x1.5D0B7E9E69054p-6;
			constexpr double p04 = +0x1.A1247CA5D9475p-4;
			constexpr double p05 = -0x1.519E110F61B54p-4;
			constexpr double p06 = +0x1.A759263F377F2p-7;
			constexpr double p07 = +0x1.094966BE2B531p-5;
			constexpr double p08 = -0x1.09BC0AB7F914Cp-5;
			constexpr double p09 = +0x1F3B7C531AA4Ap-8;
			constexpr double p10 = +0x1.950E69DCDD967p-7;
			constexpr double p11 = -0x1.D88D31ABC3AE5p-7;
			constexpr double p12 = +0x1.10F3E20F6A2E2p-8;

			double y = x - 0x1.4000000000027p-1;

			return ((((((((((((+p12) * y + p11) * y + p10) * y + p09) * y + p08) * y +
				p07) *
				y +
				p06) *
				y +
				p05) *
				y +
				p04) *
				y +
				p03) *
				y +
				p02) *
				y +
				p01) *
				y +
				p00;
			};
		// Return arctangent(x) given that 0x1p-27 < |x| <= 1/2, with the same properties
		// as atan.
		auto atani0 = [](double x) {
			constexpr double p03 = -0x1.555555555551Bp-2;
			constexpr double p05 = +0x1.99999999918D8p-3;
			constexpr double p07 = -0x1.2492492179CA3p-3;
			constexpr double p09 = +0x1.C71C7096C2725p-4;
			constexpr double p11 = -0x1.745CF51795B21p-4;
			constexpr double p13 = +0x1.3B113F18AC049p-4;
			constexpr double p15 = -0x1.10F31279EC05Dp-4;
			constexpr double p17 = +0x1.DFE7B9674AE37p-5;
			constexpr double p19 = -0x1.A38CF590469ECp-5;
			constexpr double p21 = +0x1.56CDB5D887934p-5;
			constexpr double p23 = -0x1.C0EB85F543412p-6;
			constexpr double p25 = +0x1.4A9F5C4724056p-7;

			// Square x.
			double x2 = x * x;

			return ((((((((((((+p25) * x2 + p23) * x2 + p21) * x2 + p19) * x2 + p17) *
				x2 +
				p15) *
				x2 +
				p13) *
				x2 +
				p11) *
				x2 +
				p09) *
				x2 +
				p07) *
				x2 +
				p05) *
				x2 +
				p03) *
				x2 * x +
				x;
			};
		// Return arctangent(x) given that 2 < x, with the same properties as atan.
		auto Tail = [](double x) {
			{
				constexpr double HalfPi = 0x3.243f6a8885a308d313198a2e037ap-1;

				// For large x, generate inexact and return pi/2.
				if (0x1p53 <= x)
					return HalfPi + DBL_EPSILON;
				if (x != x) // isnan
					return x - x;
			}

			constexpr double p03 = -0x1.5555555554A51p-2;
			constexpr double p05 = +0x1.999999989EBCAp-3;
			constexpr double p07 = -0x1.249248E1422E3p-3;
			constexpr double p09 = +0x1.C71C5EDFED480p-4;
			constexpr double p11 = -0x1.745B7F2D72663p-4;
			constexpr double p13 = +0x1.3AFD7A0E6EB75p-4;
			constexpr double p15 = -0x1.104146B1A1AE8p-4;
			constexpr double p17 = +0x1.D78252FA69C1Cp-5;
			constexpr double p19 = -0x1.81D33E401836Dp-5;
			constexpr double p21 = +0x1.007733E06CEB3p-5;
			constexpr double p23 = -0x1.83DAFDA7BD3FDp-7;

			constexpr double p000 = +0x1.921FB54442D18p0;
			constexpr double p001 = +0x1.1A62633145C07p-54;

			double y = 1 / x;

			// Square y.
			double y2 = y * y;

			return p001 -
				((((((((((((+p23) * y2 + p21) * y2 + p19) * y2 + p17) * y2 + p15) *
					y2 +
					p13) *
					y2 +
					p11) *
					y2 +
					p09) *
					y2 +
					p07) *
					y2 +
					p05) *
					y2 +
					p03) *
					y2 * y +
					y) +
				p000;
			};

		if (x < 0)
			if (x < -1)
				if (x < -5 / 3.)
					if (x < -2)
						return -Tail(-x);
					else
						return -atani5(-x);
				else if (x < -4 / 3.)
					return -atani4(-x);
				else
					return -atani3(-x);
			else if (x < -.5)
				if (x < -.75)
					return -atani2(-x);
				else
					return -atani1(-x);
			else if (x < -0x1.d12ed0af1a27fp-27)
				return atani0(x);
			else if (x <= -0x1p-1022)
				// Generate inexact and return x.
				return (DBL_EPSILON + 1) * x;
			else if (x == 0)
				return x;
			else
				// Generate underflow and return x.
				return x * DBL_EPSILON + x;
		else if (x <= +1)
			if (x <= +.5)
				if (x <= +0x1.d12ed0af1a27fp-27)
					if (x < +0x1p-1022)
						if (x == 0)
							return x;
						else
							// Generate underflow and return x.
							return x * DBL_EPSILON + x;
					else
						// Generate inexact and return x.
						return (DBL_EPSILON + 1) * x;
				else
					return atani0(x);
			else if (x <= +.75)
				return +atani1(+x);
			else
				return +atani2(+x);
		else if (x <= +5 / 3.)
			if (x <= +4 / 3.)
				return +atani3(+x);
			else
				return +atani4(+x);
		else if (x <= +2)
			return +atani5(+x);
		else
			return +Tail(+x);
	}


	float my_atan2(float y, float x)
	{
		// https://en.wikipedia.org/wiki/Atan2#Definition (A compact expression with four
		// overlapping half-planes is: ...)
		if (x == 0) {
			if (y > 0.0f)
				return M_PI_2;
			else if (y < 0.0f)
				return -M_PI_2;
			return 0;
		}
		else if (x > 0)
			return my_atan(y / x);
		else if (x < 0)
			return M_PI + my_atan(y / x);
		else if (y > 0)
			return M_PI_2 - my_atan(y / x);
		else if (y < 0)
			return -M_PI_2 - my_atan(y / x);
		return 0;
	}

	float my_asin(float x) { return my_atan2(x, my_sqrt(1.0 - (x * x))); }
	

	float acosf(float x)
	{
		auto non_negative = (x >= 0.f);

		auto pox = fabsf(x);
		auto omx = 1.f - pox;

		if (omx < 0.f)
		{
			omx = 0.f;
		}

		auto root = sqrtf(omx);
		auto result = (((((((-0.0012624911f * pox + 0.0066700901f) * pox - 0.0170881256f) * pox + 0.0308918810f) * pox - 0.0501743046f) * pox + 0.0889789874f) * pox - 0.2145988016f) * pox + 1.5707963050f);

		result *= root;
		return (non_negative ? result : (XM_PI - result));
	}

	float atanf(float x)
	{
		auto x2 = x * x;
		auto root = sqrtf(1.f + x2);
		return asinf(x / root);
	}

	double myAtan(double x) {
		if (x == 0.0) {
			return 0.0;
		}

		double result = 0.0;
		bool isNegative = false;

		// Handle negative values to calculate arctan in the appropriate quadrant
		if (x < 0.0) {
			x = -x;
			isNegative = true;
		}

		if (x > 1.0) {
			// Use arctan formula for values greater than 1 to bring the value within (-PI/2, PI/2)
			result = PI / 2 - myAtan(1 / x);
		}
		else {
			// Use Taylor series approximation for values between -1 and 1
			double term = x;
			double denominator = 1.0;
			double nextTerm;

			for (int i = 1; i <= 1000; i++) { // Limit the number of iterations for accuracy
				denominator += 2.0;
				nextTerm = term * (x * x) / denominator;
				if (i % 2 == 0) {
					result -= nextTerm;
				}
				else {
					result += nextTerm;
				}
				term = nextTerm;
				if (nextTerm == 0.0) {
					break; // Exit loop if the term becomes zero (no significant contribution)
				}
			}
		}

		// Adjust the result based on the quadrant
		if (isNegative) {
			result = -result;
		}

		return result;
	}

	double atan2(double y, double x)
	{
		if (x == 0.0) {
			if (y > 0.0) return PI / 2.0;
			if (y < 0.0) return -PI / 2.0;
			return 0.0; // atan2(0, 0) is undefined, this is just an example implementation.
		}

		double angle = myAtan(y / x);
		if (x < 0.0) {
			angle += PI;
		}
		else if (y < 0.0) {
			angle += TWO_PI;
		}

		return angle;
	}

	float atan2f(float y, float x)
	{
		return static_cast<float>(atan2(static_cast<double>(y), static_cast<double>(x)));
	}
}