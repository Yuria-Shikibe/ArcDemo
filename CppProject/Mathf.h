// ReSharper disable CppIdenticalOperandsInBinaryExpression
// ReSharper disable CppClangTidyClangDiagnosticFloatEqual
// ReSharper disable CppClangTidyClangDiagnosticUnusedFunction
// ReSharper disable IdentifierTypo
#pragma once
#include <iostream>
#include <vector>

#include "Vector2D.h"

namespace Mathf{
    static constexpr int SIGNS[] = { -1, 1 };
    static constexpr int ZERO_ONE[] = { 0, 1 };
    static constexpr bool BOOLEANS[] = { true, false };
    static constexpr float FLOAT_ROUNDING_ERROR = 0.000001f; // 32 bits
    static constexpr float PI = 3.1415927f;
    // ReSharper disable once CppInconsistentNaming
    static constexpr float pi = PI, HALF_PI = PI / 2;
    static constexpr double PI_EXACT = 3.14159265358979323846;
    static constexpr float PI2 = PI * 2;
    static constexpr float E = 2.7182818f;
    static const float SQRT2 = sqrt(2.0f);
    static const float SQRT3 = sqrt(3.0f);
    /** multiply by this to convert from radians to degrees */
    static constexpr float RADIANS_TO_DEGREES = 180.0f / PI;
    static constexpr float RAD_DEG = RADIANS_TO_DEGREES;
    /** multiply by this to convert from degrees to radians */
    static constexpr float DEGREES_TO_RADIANS = PI / 180;
    static constexpr float DEG_RAD = DEGREES_TO_RADIANS;
    static constexpr double DOUBLE_DEG_RAD = 0.017453292519943295;
    static constexpr double DOUBLE_RAD_DEG = 57.29577951308232;

	static constexpr unsigned int SIN_BITS = 16;
    static constexpr unsigned int SIN_MASK = ~(-1 << SIN_BITS);
    static constexpr unsigned int SIN_COUNT = SIN_MASK + 1;
	inline float sinTable[SIN_COUNT];  // NOLINT(clang-diagnostic-vla-extension, clang-diagnostic-gnu-folding-constant)
    static constexpr float RAD_FULL = PI * 2;
    static constexpr float DEG_FULL = 360.0f;
    static constexpr float RAD_TO_INDEX = SIN_COUNT / RAD_FULL;
    static constexpr float DEG_TO_INDEX = SIN_COUNT / DEG_FULL;
    static constexpr int BIG_ENOUGH_INT = 16 * 1024;
    static constexpr double BIG_ENOUGH_FLOOR = BIG_ENOUGH_INT;
    static constexpr double CEIL = 0.9999999;
    static constexpr double BIG_ENOUGH_ROUND = BIG_ENOUGH_INT + 0.5f;

    using Geom::Vector2D;

    static Vector2D v1{}, v2{}, v3{};


	static struct SineTableInitializer {
        SineTableInitializer() {
            for (unsigned int i = 0; i < SIN_COUNT; i++) {
                sinTable[i] = sinf((static_cast<float>(i) + 0.5f) / SIN_COUNT * RAD_FULL);
            }

            for (unsigned int i = 0; i < 360; i += 90){
	            const auto fi = static_cast<float>(i);
                sinTable[static_cast<int>(fi * DEG_TO_INDEX) & SIN_MASK] = sinf(fi * DEGREES_TO_RADIANS);
            }

            sinTable[0                                              ] =  0.0f;
            sinTable[static_cast<int>( 90 * DEG_TO_INDEX) & SIN_MASK] =  1.0f;
            sinTable[static_cast<int>(180 * DEG_TO_INDEX) & SIN_MASK] =  0.0f;
            sinTable[static_cast<int>(270 * DEG_TO_INDEX) & SIN_MASK] = -1.0f;
        }
    } sineTableInitializerInit{};

    // static Rand rand = new Rand();

    /** Returns the sine in radians from a lookup table. */
    static float sin(const float radians) {
        return sinTable[static_cast<int>(radians * RAD_TO_INDEX) & SIN_MASK];
    }

    static float sin(const float radians, const float scl, const float mag) {
        return sin(radians / scl) * mag;
    }

    /** Returns the cosine in radians from a lookup table. */
    static float cos(const float radians) {
        return sinTable[static_cast<int>((radians + PI / 2) * RAD_TO_INDEX) & SIN_MASK];
    }

    /** Returns the sine in radians from a lookup table. */
    static float sinDeg(const float degrees) {
        return sinTable[static_cast<int>(degrees * DEG_TO_INDEX) & SIN_MASK];
    }

    /** Returns the cosine in radians from a lookup table. */
    static float cosDeg(const float degrees) {
        return sinTable[static_cast<int>((degrees + 90) * DEG_TO_INDEX) & SIN_MASK];
    }

    static float absin(const float in, const float scl, const float mag) {
        return (sin(in, scl * 2.0f, mag) + mag) / 2.0f;
    }

    static float tan(const float radians, const float scl, const float mag) {
        return (sin(radians / scl)) / (cos(radians / scl)) * mag;
    }

    static float cos(const float radians, const float scl, const float mag) {
        return cos(radians / scl) * mag;
    }

    static float angle(const float x, const float y) {
        float result = atan2(x, y) * RAD_DEG;
        if (result < 0) result += DEG_FULL;
        return result;
    }

    static float angleExact(const float x, const float y) {
        float result = (float)atan2(y, x) * RAD_DEG;
        if (result < 0) result += DEG_FULL;
        return result;
    }

    /** Wraps the given angle to the range [-PI, PI]
     * @param a the angle in radians
     * @return the given angle wrapped to the range [-PI, PI] */
    static float wrapAngleAroundZero(const float a) {
        if (a >= 0) {
            float rotation = fmod(a, PI2);
            if (rotation > PI) rotation -= PI2;
            return rotation;
        }
        else {
            float rotation = fmod(-a, PI2);
            if (rotation > PI) rotation -= PI2;
            return -rotation;
        }
    }

    /** A variant on atan that does not tolerate infinite inputs for speed reasons, and because infinite inputs
     * should never occur where this is used (only in {@link atan2(float, float)}).
     * @param i any finite float
     * @return an output from the inverse tangent function, from PI/-2.0 to PI/2.0 inclusive */
    static float atn(const double i) {
        // We use double precision internally, because some constants need double precision.
        const double n = abs(i);
        // c uses the "equally-good" formulation that permits n to be from 0 to almost infinity.
        const double c = (n - 1.0) / (n + 1.0);
        // The approximation needs 6 odd powers of c.
        const double c2 = c * c, c3 = c * c2, c5 = c3 * c2, c7 = c5 * c2, c9 = c7 * c2, c11 = c9 * c2;
        return static_cast<float>
        (std::copysign((PI_EXACT * 0.25)
            + (0.99997726 * c - 0.33262347 * c3 + 0.19354346 * c5 - 0.11643287 * c7 + 0.05265332 * c9 - 0.0117212 * c11), i));
    }

    /** Close approximation of the frequently-used trigonometric method atan2, with higher precision than libGDX's atan2
     * approximation. Average error is 1.057E-6 radians; maximum error is 1.922E-6. Takes y and x (in that unusual order) as
     * floats, and returns the angle from the origin to that point in radians. It is about 4 times faster than
     * {@link atan2(double, double)} (roughly 15 ns instead of roughly 60 ns for Math, on Java 8 HotSpot). <br>
     * Credit for this goes to the 1955 research study "Approximations for Digital Computers," by RAND Corporation. This is sheet
     * 11's algorithm, which is the fourth-fastest and fourth-least precise. The algorithms on sheets 8-10 are faster, but only by
     * a very small degree, and are considerably less precise. That study provides an atan method, and that cleanly
     * translates to atan2().
     * @param y y-component of the point to find the angle towards; note the parameter order is unusual by convention
     * @param x x-component of the point to find the angle towards; note the parameter order is unusual by convention
     * @return the angle to the given point, in radians as a float; ranges from -PI to PI */
    static float atan2(float x, const float y) {
        float n = y / x;
        if (n != n) {
            n = (y == x ? 1.0f : -1.0f); // if both y and x are infinite, n would be NaN
        }
        else if (n - n != n - n) {
            x = 0.0f; // if n is infinite, y is infinitely larger than x.
        }

        if (x > 0.0f) {
            return atn(n);
        }
        else if (x < 0.0f) {
            return y >= 0 ? atn(n) + PI : atn(n) - PI;
        }
        else if (y > 0.0f) {
            return x + HALF_PI;
        }
        else if (y < 0.0f) {
            return x - HALF_PI;
        }
        else {
            return x + y; // returns 0 for 0,0 or NaN if either y or x is NaN
        }
    }

    static int digits(const int n) {
        return n < 100000 ? n < 100 ? n < 10 ? 1 : 2 : n < 1000 ? 3 : n < 10000 ? 4 : 5 : n < 10000000 ? n < 1000000 ? 6 : 7 : n < 100000000 ? 8 : n < 1000000000 ? 9 : 10;
    }

    static int digits(const long n) {
        return n == 0 ? 1 : static_cast<int>(log10(n) + 1);
    }

    static float sqr(const float x) {
        return x * x;
    }

    static float map(const float value, const float fromA, const float toa, const float fromB, const float tob) {
        return fromB + (value - fromA) * (tob - fromB) / (toa - fromA);
    }

    /** Map value from [0, 1].*/
    static float map(const float value, const float from, const float to) {
        return map(value, 0, 1, from, to);
    }

    /**Returns -1 if f<0, 1 otherwise.*/
    static int sign(const float f) {
        return (f < 0 ? -1 : 1);
    }

    /** Returns 1 if true, -1 if false. */
    static int sign(const bool b) {
        return b ? 1 : -1;
    }

    /**Converts a bool to an integer: 1 if true, 0, if false.*/
    static int num(const bool b) {
        return b ? 1 : 0;
    }

    static float pow_float(const float a, const float b) {
        return pow(a, b);
    }

    static int pow_int(const int a, const int b) {
        return static_cast<int>(ceil(pow(a, b)));
    }

    // static float range(float range) {
    //     return random(-range, range);
    // }
    //
    // static int range(int range) {
    //     return random(-range, range);
    // }
    //
    // static float range(float min, float max) {
    //     if (chance(0.5)) {
    //         return random(min, max);
    //     }
    //     else {
    //         return -random(min, max);
    //     }
    // }

    // static bool chance(double d) {
    //     return d >= 1f || rand.nextFloat() < d;
    // }

    /** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
    // static int random(int range) {
    //     return rand.nextInt(range + 1);
    // }

    /** Returns a random number between start (inclusive) and end (inclusive). */
    // static int random(int start, int end) {
    //     return start + rand.nextInt(end - start + 1);
    // }

    /** Returns a random number between 0 (inclusive) and the specified value (inclusive). */
    // static long random(long range) {
    //     return (long)(rand.nextDouble() * range);
    // }

    /** Returns a random number between start (inclusive) and end (inclusive). */
    // static long random(long start, long end) {
    //     return start + (long)(rand.nextDouble() * (end - start));
    // }

    /** Returns a random bool value. */
    // static bool randombool() {
    //     return rand.nextbool();
    // }

    /** Returns true if a random value between 0 and 1 is less than the specified value. */
    // static bool randombool(float chance) {
    //     return Mathf.random() < chance;
    // }

    /** Returns random number between 0.0 (inclusive) and 1.0 (exclusive). */
    // static float random() {
    //     return rand.nextFloat();
    // }

    /** Returns a random number between 0 (inclusive) and the specified value (exclusive). */
    // static float random(float range) {
    //     return rand.nextFloat() * range;
    // }

    /** Returns a random number between start (inclusive) and end (exclusive). */
    // static float random(float start, float end) {
    //     return start + rand.nextFloat() * (end - start);
    // }

    /** Returns -1 or 1, randomly. */
    // static int randomSign() {
    //     return 1 | (rand.nextInt() >> 31);
    // }

    //TODO these can be optimized to a single function, setting the seed and getting a result may be expensive

    /** Inclusive. */
    // static int randomSeed(long seed, int min, int max) {
    //     seedr.setSeed(seed);
    //     if (isPowerOfTwo(max)) {
    //         seedr.nextInt();
    //     }
    //     return seedr.nextInt(max - min + 1) + min;
    // }
    //
    // /** Inclusive. */
    // static float randomSeed(long seed, float min, float max) {
    //     seedr.setSeed(seed);
    //     return (min + seedr.nextFloat() * (max - min));
    // }
    //
    // static float randomSeed(long seed) {
    //     seedr.setSeed(seed * 99999);
    //     return seedr.nextFloat();
    // }
    //
    // static float randomSeed(long seed, float max) {
    //     seedr.setSeed(seed * 99999);
    //     return seedr.nextFloat() * max;
    // }
    //
    // static float randomSeedRange(long seed, float range) {
    //     seedr.setSeed(seed * 99999);
    //     return range * (seedr.nextFloat() - 0.5f) * 2f;
    // }

    /**
     * Returns a triangularly distributed random number between -1.0 (exclusive) and 1.0 (exclusive), where values around zero are
     * more likely.
     * <p>
     * This is an optimized version of {@link randomTriangular(float, float, float) randomTriangular(-1, 1, 0)}
     */
    // static float randomTriangular() {
    //     return rand.nextFloat() - rand.nextFloat();
    // }

    /**
     * Returns a triangularly distributed random number between {@code -max} (exclusive) and {@code max} (exclusive), where values
     * around zero are more likely.
     * <p>
     * This is an optimized version of {@link randomTriangular(float, float, float) randomTriangular(-max, max, 0)}
     * @param max the upper limit
     */
    // static float randomTriangular(float max) {
    //     return (rand.nextFloat() - rand.nextFloat()) * max;
    // }

    /**
     * Returns a triangularly distributed random number between {@code min} (inclusive) and {@code max} (exclusive), where the
     * {@code mode} argument defaults to the midpoint between the bounds, giving a symmetric distribution.
     * <p>
     * This method is equivalent of {@link #randomTriangular(float, float, float) randomTriangular(min, max, (min + max) * .5f)}
     * @param min the lower limit
     * @param max the upper limit
     */
    // static float randomTriangular(float min, float max) {
    //     return randomTriangular(min, max, (min + max) * 0.5f);
    // }

    /**
     * Returns a triangularly distributed random number between {@code min} (inclusive) and {@code max} (exclusive), where values
     * around {@code mode} are more likely.
     * @param min the lower limit
     * @param max the upper limit
     * @param mode the point around which the values are more likely
     */
    // static float randomTriangular(float min, float max, float mode) {
    //     float u = rand.nextFloat();
    //     float d = max - min;
    //     if (u <= (mode - min) / d) return min + (float)sqrt(u * d * (mode - min));
    //     return max - (float)sqrt((1 - u) * d * (max - mode));
    // }

    /** Returns the next power of two. Returns the specified value if the value is already a power of two. */
    static int nextPowerOfTwo(int value) {
        if (value == 0) return 1;
        value--;
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;
        return value + 1;
    }

    static bool isPowerOfTwo(const int value) {
        return value != 0 && (value & value - 1) == 0;
    }

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

    static int clamp(const int value, const int minv, const int maxv) {
        return max(min(value, maxv), minv);
    }

    static long clamp(const long value, const long minv, const long maxv) {
        return max(min(value, maxv), minv);
    }

    static float clamp(const float value, const float minv, const float maxv) {
        return max(min(value, maxv), minv);
    }

    /** Clamps to [0, 1]. */
    static float clamp(const float value) {
        return clamp(value, 0.0f, 1.0f);
    }

    static double clamp(const double value, const double minv, const double maxv) {
        return max(min(value, maxv), minv);
    }

    static float maxZero(const float val) {
        return max(val, 0.0f);
    }

    /** Approaches a value at linear speed. */
    static float approach(const float from, const float to, const float speed) {
        return from + clamp(to - from, -speed, speed);
    }

    /** Linearly interpolates between fromValue to toValue on progress position. */
    static float lerp(const float fromValue, const float toValue, const float progress) {
        return fromValue + (toValue - fromValue) * progress;
    }

    /**
     * Linearly interpolates between two angles in radians. Takes into account that angles wrap at two pi and always takes the
     * direction with the smallest delta angle.
     * @param fromRadians start angle in radians
     * @param toRadians target angle in radians
     * @param progress interpolation value in the range [0, 1]
     * @return the interpolated angle in the range [0, PI2]
     */
    static float slerpRad(const float fromRadians, const float toRadians, const float progress) {
        const float delta = fmod(toRadians - fromRadians + PI2 + PI, PI2) - PI;
        return fmod((fromRadians + delta * progress + PI2), PI2);
    }

    /**
     * Linearly interpolates between two angles in degrees. Takes into account that angles wrap at 360 degrees and always takes
     * the direction with the smallest delta angle.
     * @param fromDegrees start angle in degrees
     * @param toDegrees target angle in degrees
     * @param progress interpolation value in the range [0, 1]
     * @return the interpolated angle in the range [0, 360[
     */
    static float slerp(const float fromDegrees, const float toDegrees, const float progress) {
        const float delta = fmod((toDegrees - fromDegrees + DEG_FULL + 180.0f), DEG_FULL) - 180.0f;
        return fmod((fromDegrees + delta * progress + DEG_FULL), DEG_FULL);
    }

    /**
     * Returns the largest integer less than or equal to the specified float. This method will only properly floor floats from
     * -(2^14) to (Float.MAX_VALUE - 2^14).
     */
    static int floor(const float value) {
        return static_cast<int>(value + BIG_ENOUGH_FLOOR) - BIG_ENOUGH_INT;
    }

    /**
     * Returns the largest integer less than or equal to the specified float. This method will only properly floor floats that are
     * positive. Note this method simply casts the float to int.
     */
    static int floorPositive(const float value) {
        return static_cast<int>(value);
    }

    /**
     * Returns the smallest integer greater than or equal to the specified float. This method will only properly ceil floats from
     * -(2^14) to (Float.MAX_VALUE - 2^14).
     */
    static int ceil(const float value) {
        return BIG_ENOUGH_INT - static_cast<int>(BIG_ENOUGH_FLOOR - value);
    }

    /**
     * Returns the smallest integer greater than or equal to the specified float. This method will only properly ceil floats that
     * are positive.
     */
    static int ceilPositive(const float value) {
        return static_cast<int>(value + CEIL);
    }

    /**
     * Returns the closest integer to the specified float. This method will only properly round floats from -(2^14) to
     * (Float.MAX_VALUE - 2^14).
     */
    static int round(const float value) {
        return static_cast<int>(value + BIG_ENOUGH_ROUND) - BIG_ENOUGH_INT;
    }

    static int round(const int value, const int step) {
        return (value / step) * step;
    }

    static float round(const float value, const float step) {
        return static_cast<int>(value / step) * step;
    }

    static int round(const float value, const int step) {
        return static_cast<int>(value / static_cast<float>(step)) * step;
    }

    /** Returns the closest integer to the specified float. This method will only properly round floats that are positive. */
    static int roundPositive(const float value) {
        return lround(value + 0.5f);
    }

    /** Returns true if the value is zero (using the default tolerance as upper bound) */
    static bool zero(const float value) {
        return abs(value) <= FLOAT_ROUNDING_ERROR;
    }

    /** Returns true if the value is zero (using the default tolerance as upper bound) */
    static bool zero(const double value) {
        return abs(value) <= FLOAT_ROUNDING_ERROR;
    }

    /**
     * Returns true if the value is zero.
     * @param value N/A
     * @param tolerance represent an upper bound below which the value is considered zero.
     */
    static bool zero(const float value, const float tolerance) {
        return abs(value) <= tolerance;
    }

    /**
     * Returns true if a is nearly equal to b. The function uses the default floating error tolerance.
     * @param a the first value.
     * @param b the second value.
     */
    static bool equal(const float a, const float b) {
        return abs(a - b) <= FLOAT_ROUNDING_ERROR;
    }

    /**
     * Returns true if a is nearly equal to b.
     * @param a the first value.
     * @param b the second value.
     * @param tolerance represent an upper bound below which the two values are considered equal.
     */
    static bool equal(const float a, const float b, const float tolerance) {
        return abs(a - b) <= tolerance;
    }

    // /** @return the logarithm of value with base a */
    // static float log(float a, float value) {
    //     return (float)(log(value) / log(a));
    //     log
    // }
    //
    // /** @return the logarithm of value with base 2 */
    // static float log2(const float value) {
    //     return log(2, value);
    // }
    //
    // /** @return base-2 logarithm of the specified integer */
    // static int log2(int value) {
    //     return value == 0 ? 0 : 31 - Integer.numberOfLeadingZeros(value);
    // }

    /** Mod function that works properly for negative numbers. */
    static float mod(const float f, const float n) {
        return fmod(fmod(f, n) + n , n);
    }

    /** Mod function that works properly for negative numbers. */
    static int mod(const int x, const int n) {
        return ((x % n) + n) % n;
    }

    /** @return a sampled value based on position in an array of float values. */
    static float sample(const std::vector<float>& values, float time) {
        time = clamp(time);
        const auto size = static_cast<float>(values.size());
        const float pos = time * (size - 1.0f);
        const auto cur = static_cast<unsigned long long>(min((time * (size - 1.0f)), size - 1.0f));
        const unsigned long long next = min(values.size() + 1ULL, values.size() - 1ULL);
        const float mod = pos - static_cast<float>(cur);
        return lerp(values[cur], values[next], mod);
    }

    /** @return the input 0-1 value scaled to 0-1-0. */
    static float slope(const float fin) {
        return 1.0f - abs(fin - 0.5f) * 2.0f;
    }

    /**Converts a 0-1 value to 0-1 when it is in [offset, 1].*/
    static float curve(const float f, const float offset) {
        if (f < offset) {
            return 0.0f;
        }
        else {
            return (f - offset) / (1.0f - offset);
        }
    }

    /**Converts a 0-1 value to 0-1 when it is in [offset, to].*/
    static float curve(const float f, const float from, const float to) {
        if (f < from) {
            return 0.0f;
        }
        else if (f > to) {
            return 1.0f;
        }
        else {
            return (f - from) / (to - from);
        }
    }

    /** Transforms a 0-1 value to a value with a 0.5 plateau in the middle. When margin = 0.5, this method doesn't do anything. */
    static float curveMargin(const float f, const float marginLeft, const float marginRight) {
        if (f < marginLeft) return f / marginLeft * 0.5f;
        if (f > 1.0f - marginRight) return (f - 1.0f + marginRight) / marginRight * 0.5f + 0.5f;
        return 0.5f;
    }

    /** Transforms a 0-1 value to a value with a 0.5 plateau in the middle. When margin = 0.5, this method doesn't do anything. */
    static float curveMargin(const float f, const float margin) {
        return curveMargin(f, margin, margin);
    }

    static float len(const float x, const float y) {
        return (float)sqrt(x * x + y * y);
    }

    static float len2(const float x, const float y) {
        return x * x + y * y;
    }

    static float dot(const float x1, const float y1, const float x2, const float y2) {
        return x1 * x2 + y1 * y2;
    }

    static float dst(const float x1, const float y1) {
        return (float)sqrt(x1 * x1 + y1 * y1);
    }

    static float dst2(const float x1, const float y1) {
        return (x1 * x1 + y1 * y1);
    }

    static float dst(const float x1, const float y1, const float x2, const float y2) {
        const float xd = x2 - x1;
        const float yd = y2 - y1;
        return sqrt(xd * xd + yd * yd);
    }

    static float dst2(const float x1, const float y1, const float x2, const float y2) {
        const float xd = x2 - x1;
        const float yd = y2 - y1;
        return xd * xd + yd * yd;
    }

    /** Manhattan distance. */
    static float dst_mht(const float x1, const float y1, const float x2, const float y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }

    // static Geom::Vector2D arrive(const float x, const float y, const float destX, const float destY, const Geom::Vector2D& curVel, const float radius, const float tolerance, const float speed, const float accel) {
    //     Geom::Vector2D toTarget = v1.set(destX, destY).sub(x, y);
    //     const float distance = toTarget.length();
    //
    //     if (distance <= tolerance) return v3.setZero();
    //     float targetSpeed = speed;
    //     if (distance <= radius) targetSpeed *= distance / radius;
    //
    //     return toTarget.sub(curVel.x / accel, curVel.y / accel).limit(targetSpeed);
    // }
    //
    //
    // static Geom::Vector2D arrive(const Geom::Position& pos, const Geom::Position& target, const Geom::Vector2D& curVel, const float radius, const float tolerance, const float speed, const float smoothTime) {
    //     return arrive(pos.getX(), pos.getY(), target.getX(), target.getY(), curVel, radius, tolerance, speed, smoothTime);
    // }

    
    /** @return whether dst(x1, y1, x2, y2) < dst */
    static bool within(const float x1, const float y1, const float x2, const float y2, const float dst) {
        return dst2(x1, y1, x2, y2) < dst * dst;
    }

    /** @return whether dst(x, y, 0, 0) < dst */
    static bool within(const float x1, const float y1, const float dst) {
        return (x1 * x1 + y1 * y1) < dst * dst;
    }
}
