#pragma once
#include <glad/glad.h>

namespace Graphic{
	class Blending
	{
	public:
		GLenum src, dst, srcAlpha, dstAlpha;

		Blending(const GLenum src, const GLenum dst, const GLenum srcAlpha, const GLenum dstAlpha);

		Blending(const GLenum src, const GLenum dst) : Blending(src, dst, src, dst) {}

		Blending(const Blending& other);

		Blending(Blending&& other) noexcept;

		Blending& operator=(const Blending& other);

		Blending& operator=(Blending&& other) noexcept;

		~Blending() = default;

		friend bool operator==(const Blending& lhs, const Blending& rhs);

		friend bool operator!=(const Blending& lhs, const Blending& rhs);

		void apply() const;
	};

	namespace Blendings{
		static const Blending NORMAL{ GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
		static const Blending ADDICTIVE{ GL_SRC_ALPHA, GL_ONE, GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
		static const Blending ALPHA_SUSTAIN{ GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
	}
}


