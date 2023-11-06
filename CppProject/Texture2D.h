#pragma once
#include <ostream>
#include <string>
#include <glad/glad.h>

namespace Graphic{
	class Texture2D
	{

	protected:
		unsigned char* localData = nullptr;

	public:
		std::string texName;
		GLuint textureID = 0;
		int width = 0, height = 0;
		int bpp = 0;

	public:
		~Texture2D();

		Texture2D(const int w, const int h);

		explicit Texture2D(const std::string& name);

		friend std::size_t hashCode(const Texture2D& obj);

		friend std::ostream& operator<<(std::ostream& os, const Texture2D& obj);

		friend bool operator==(const Texture2D& lhs, const Texture2D& rhs);

		friend bool operator!=(const Texture2D& lhs, const Texture2D& rhs);

		Texture2D(const Texture2D& other);

		Texture2D(Texture2D&& other) noexcept;

		Texture2D& operator=(const Texture2D& other);

		Texture2D& operator=(Texture2D&& other) noexcept;

		void resize(const int w, const int h);

		void loadFromFile(const std::string& name);

		void setParametersDef() const;

		void setScale(const GLint upScale = GL_LINEAR, const GLint downScale = GL_LINEAR) const;

		void setWrap(const GLint clamp = GL_CLAMP_TO_EDGE) const;

		void bind(const bool active = true, const unsigned char slotOffset = 0) const;

		void bindParam(const GLenum target);

		void unbind() const;
	};

	// static const Texture2D EMPTY_TEXTURE_2D{ 0, 0 };
}


