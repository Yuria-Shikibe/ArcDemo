#pragma once

#include <sstream>

#include "Vector2D.h"

// Char

static int charToDigitValue(const char c, const int radix) {
	int digitValue = -1;  

	if (std::isdigit(c)) {
		if (const int numericValue = c - '0'; numericValue < radix) {
			digitValue = numericValue;
		}
	}
	else if (std::isalpha(c)) {
		if (const int numericValue = std::toupper(c) - 'A' + 10; numericValue < radix) {
			digitValue = numericValue;
		}
	}

	return digitValue;
}

// Float Int Converts

static constexpr unsigned long long INT_MASK_BACK = 0x00000000ffffffffL;
static constexpr unsigned long long INT_MASK_FRONT = 0xffffffff00000000L;

static unsigned int floatToUnsignedIntBits(const float f){
	return *reinterpret_cast<const unsigned int*>(&f);  // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
}

static int floatToIntBits(const float f) {
	return *reinterpret_cast<const int*>(&f);  // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
}

static float intBitsToFloat(const int x) {
	return *reinterpret_cast<const float*>(&x);  // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
}


// ReSharper disable once CppInconsistentNaming
static std::stringstream tmpSS;
static const std::string EMPTY;

static std::string uintToHesStr(const unsigned int i, std::stringstream& ss) {
	ss << std::hex << i;

	return ss.str();
}

static std::string uintToHesStr(const unsigned int i){
	tmpSS.str(EMPTY);

	return uintToHesStr(i, tmpSS);
}

static std::string ulongToHesStr(const unsigned long long i, std::stringstream& ss) {
	ss << std::hex << i;

	return ss.str();
}

static std::string ulongToHesStr(const unsigned long long l) {
	tmpSS.str(EMPTY);

	return ulongToHesStr(l, tmpSS);
}

// Double Long Converts

static unsigned long long doubleToUnsignedLongBits(const double d) {
	return *reinterpret_cast<const unsigned long long*>(&d);  // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
}

static long long doubleToLongBits(const double d) {
	return *reinterpret_cast<const long long*>(&d);  // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
}

static double longBitsToDouble(const long long x) {
	return *reinterpret_cast<const double*>(&x);  // NOLINT(clang-diagnostic-undefined-reinterpret-cast)
}




static unsigned long long pack(const float x, const float y){
	return (static_cast<unsigned long long>(floatToUnsignedIntBits(x)) << 32) + floatToUnsignedIntBits(y);
}

static int unpackX(const unsigned long long hash) {
	return static_cast<int>(hash & INT_MASK_BACK);
}

static int unpackY(const unsigned long long hash) {
	return static_cast<int>((hash & INT_MASK_FRONT) >> 32);
}

static float unpackX_Float(const unsigned long long hash) {
	return intBitsToFloat(static_cast<int>(hash & INT_MASK_BACK));
}

static float unpackY_Float(const unsigned long long hash) {
	return intBitsToFloat(static_cast<int>((hash & INT_MASK_FRONT) >> 32));
}

// static Geom::Vector2D unpack(const unsigned long long hash) {
// 	return ;
// }