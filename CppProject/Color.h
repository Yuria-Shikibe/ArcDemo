// ReSharper disable CppInconsistentNaming
// ReSharper disable IdentifierTypo
// ReSharper disable CppClangTidyClangDiagnosticImplicitIntFloatConversion
// ReSharper disable CppClangTidyBugproneNarrowingConversions
// ReSharper disable CppClangTidyClangDiagnosticFloatEqual
// ReSharper disable CppClangTidyClangDiagnosticDoublePromotion

#pragma once
#include <string>
#include <ostream>
#include "Mathf.h"
#include "Vector3D.h"

namespace Graphic{
	class Color{
		// ReSharper disable once CppInconsistentNaming
	public:
		float r = 0, g = 0, b = 0, a = 0;

		using colorBits = unsigned int;

		Color();

		// ReSharper disable once CppPossiblyUninitializedMember
		explicit Color(const colorBits rgba8888V);

		~Color();

		Color(const float tr, const float tg, const float tb, const float ta);

		Color(const float r, const float g, const float b);

		Color(Color&& color) noexcept;

		Color(const Color& other);

		Color& operator=(const Color& other);

		Color& operator=(Color&& other) noexcept;

		std::size_t hash_value(const Color& obj) const;

		friend void swap(Color& lhs, Color& rhs) noexcept;

		friend std::ostream& operator<<(std::ostream& os, const Color& obj);

		friend bool operator==(const Color& lhs, const Color& rhs);

		friend bool operator!=(const Color& lhs, const Color& rhs);

		static Color& valueOf(const std::string& hex);

		static Color& valueOf(Color& color, const std::string& hex);

		static int parseHex(const std::string& string, const int from, const int to);

		static float toFloatBits(const int r, const int g, const int b, const int a);


		static float toFloatBits(const float r, const float g, const float b, const float a);

		static double toDoubleBits(const float r, const float g, const float b, const float a);

		static double toDoubleBits(const int r, const int g, const int b, const int a);

		Color& fromDouble(const double value);

		static colorBits abgr(const int tr, const int tg, const int tb, const int ta);

		static colorBits alpha(const float alpha);

		static colorBits luminanceAlpha(const float luminance, const float alpha);

		static colorBits rgb565(const float r, const float g, const float b);

		static colorBits rgba4444(const float r, const float g, const float b, const float a);

		static colorBits rgb888(const float r, const float g, const float b);

		static colorBits rgba8888(const float r, const float g, const float b, const float a);

		static colorBits argb8888(const float a, const float r, const float g, const float b);

		/** @return 4 0-255 RGBA components packed into an int. */
		static int packRgba(const int r, const int g, const int b, const int a);

		colorBits rgb565() const;

		colorBits rgba4444() const;

		colorBits rgb888() const;

		colorBits rgba8888() const;

		colorBits argb8888() const;

		Color& rgb565(const colorBits value);

		Color& rgba4444(const colorBits value);

		Color& rgb888(const colorBits value);

		Color& rgba8888(const colorBits value);

		Color& argb8888(const colorBits value);

		Color& abgr8888(const float value);

		static Color grays(const float value);

		static Color rgb(const int r, const int g, const int b);

		static unsigned int floatToIntColor(const float value);

		static float intToFloatColor(const int value);

		//  Color rand() {
		//     return set(random(), random(), random(), 1f);
		// }
		//
		//  Color randHue() {
		//     fromHsv(random(360f), 1f, 1f);
		//     a = 1f;
		//     return *this;
		// }

		float diff(const Color& other) const;

		int rgba() const;

		Color& set(const Color& color);

		Color& set(const Geom::Vector3D vec);

		Color& mul(const Color& color);


		Color& mul_rgb(const float value);


		Color& mul_rgba(const float value);


		Color& add(const Color& color);

		Color& sub(const Color& color);

		Color& clamp();

		Color& setForce(const float tr, const float tg, const float tb, const float ta);

		Color& set(const float tr, const float tg, const float tb, const float ta);

		Color& set(const float tr, const float tg, const float tb);

		Color& set(const int rgba);

		float sum() const;

		Color& add(const float tr, const float tg, const float tb, const float ta);

		Color& add(const float tr, const float tg, const float tb);

		Color& sub(const float tr, const float tg, const float tb, const float ta);

		Color& sub(const float tr, const float tg, const float tb);

		Color& inv();

		Color& setR(const float tr);

		Color& setG(const float tg);

		Color& setB(const float tb);

		Color& setA(const float ta);

		Color& mulA(const float ta);

		Color& mul(const float tr, const float tg, const float tb, const float ta);

		Color& lerp(const Color& target, const float t);

		Color& lerp(const float tr, const float tg, const float tb, const float ta, const float t);

		Color& preMultiplyAlpha();

		Color& write(Color& to) const;

		float hue() const;

		float saturation() const;

		float value() const;

		Color& hue(const float amount);

		Color& saturation(const float amount);

		Color& value(const float amount);

		Color& shiftHue(const float amount);

		Color& shiftSaturation(const float amount);

		Color& shiftValue(const float amount);

		bool equals(const Color& o) const;

		size_t hashCode() const;

		float toFloatBits() const;

		[[nodiscard]] double toDoubleBits() const;

		colorBits abgr() const;

		std::string toString() const;

		// ReSharper disable once CppParameterMayBeConst
		Color& fromHsv(float h, const float s, const float v);

		Color& fromHsv(float hsv[]);

		// ReSharper disable once CppInconsistentNaming
		static Color HSVtoRGB(const float h, const float s, const float v, const float alpha);

		// ReSharper disable once CppInconsistentNaming
		static Color HSVtoRGB(float h, float s, float v);

		float* toHsv(float hsv[]) const;

		static Color& HSVtoRGB(float h, float s, float v, Color& targetColor);


		// ReSharper disable once IdentifierTypo
		static int clampf(const float value);

		/** @return R value of a RGBA packed color. */
		static colorBits ri(const colorBits rgba);

		/** @return G value of a RGBA packed color. */
		static colorBits gi(const colorBits rgba);

		/** @return B value of a RGBA packed color. */
		static colorBits bi(const colorBits rgba);

		/** @return A value of a RGBA packed color. */
		static colorBits ai(const colorBits rgba);

		/** Multiplies 2 RGBA colors together. */
		static colorBits muli(const colorBits ca, const colorBits cb);

		/** Multiplies a RGBA color by a float. Alpha channels are not multiplied. */
		static colorBits muli(const colorBits rgba, const float value);

		template <int size>
		static Color createLerp(const Color(&arr)[size], const float s) {
			const Color a = arr[Mathf::clamp(static_cast<int>(s * (size - 1)), 0, size - 1)];
			const Color b = arr[Mathf::clamp(static_cast<int>(s * (size - 1) + 1), 0, size - 1)];

			const float n = s * (size - 1) - static_cast<int>(s * (size - 1));
			const float i = 1.0f - n;
			return { a.r * i + b.r * n, a.g * i + b.g * n, a.b * i + b.b * n, a.a * i + b.a * n };
		}

		template <int size>
		Color& lerp(const Color(&arr)[size], const float s) {
			const Color a = arr[Mathf::clamp(static_cast<int>(s * (size - 1)), 0, size - 1)];
			const Color b = arr[Mathf::clamp(static_cast<int>(s * (size - 1) + 1), 0, size - 1)];

			const float n = s * (size - 1) - static_cast<int>(s * (size - 1));
			const float i = 1.0f - n;
			return set(a.r * i + b.r * n, a.g * i + b.g * n, a.b * i + b.b * n, a.a * i + b.a * n);
		}
	};

	namespace Colors {
		static const Color WHITE{ 1, 1, 1, 1 };
		static const Color LIGHT_GRAY{ 0xbfbfbfff };
		static const Color GRAY{ 0x7f7f7fff };
		static const Color DARK_GRAY{ 0x3f3f3fff };
		static const Color BLACK{ 0, 0, 0, 1 };
		static const Color CLEAR{ 0, 0, 0, 0 };

		/** Convenience for frequently used <code>WHITE.toFloatBits()</code> */
		static const float WHITE_FLOAT_BITS = WHITE.toFloatBits();
		static const float CLEAR_FLOAT_BITS = CLEAR.toFloatBits();
		static const float BLACK_FLOAT_BITS = BLACK.toFloatBits();

		static const int WHITE_RGBA = WHITE.rgba();
		static const int CLEAR_RGBA = CLEAR.rgba();
		static const int BLACK_RGBA = BLACK.rgba();

		static const Color BLUE{ 0, 0, 1, 1 };
		static const Color NAVY{ 0, 0, 0.5f, 1 };
		static const Color ROYAL{ 0x4169e1ff };
		static const Color SLATE{ 0x708090ff };
		static const Color SKY{ 0x87ceebff };
		static const Color CYAN{ 0, 1, 1, 1 };
		static const Color TEAL{ 0, 0.5f, 0.5f, 1 };

		static const Color GREEN{ 0x00ff00ff };
		static const Color ACID{ 0x7fff00ff };
		static const Color LIME{ 0x32cd32ff };
		static const Color FOREST{ 0x228b22ff };
		static const Color OLIVE{ 0x6b8e23ff };

		static const Color YELLOW{ 0xffff00ff };
		static const Color GOLD{ 0xffd700ff };
		static const Color GOLDENROD{ 0xdaa520ff };
		static const Color ORANGE{ 0xffa500ff };

		static const Color BROWN{ 0x8b4513ff };
		static const Color TAN{ 0xd2b48cff };
		static const Color BRICK{ 0xb22222ff };

		static const Color RED{ 0xff0000ff };
		static const Color SCARLET{ 0xff341cff };
		static const Color CRIMSON{ 0xdc143cff };
		static const Color CORAL{ 0xff7f50ff };
		static const Color SALMON{ 0xfa8072ff };
		static const Color PINK{ 0xff69b4ff };
		static const Color MAGENTA{ 1, 0, 1, 1 };

		static const Color PURPLE{ 0xa020f0ff };
		static const Color VIOLET{ 0xee82eeff };
		static const Color MAROON{ 0xb03060ff };
	}
}
